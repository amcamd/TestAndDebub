/*
    -- KBLAS (version 1.0) --
       Ahmad Abdelfattah, Center of Extreme Computing
	   Hatem Ltaief, Supercomputing Laboratory
	   David Keyes, Center of Extreme Computing
	   King Abdullah University of Science and Technology (KAUST)
       June 2013
	   KBLAS is a subset of BLAS routines highly optimized for NVIDIA GPUs 
*/
/**
	-- Center of Extreme Computing and Supercomputing Laboratory
	-- Division of Applied Mathematics and Computational Science
	-- King Abdullah University of Science and Technology
	-- (C) Copyright 2013

	Redistribution  and  use  in  source and binary forms, with or without
	modification,  are  permitted  provided  that the following conditions
	are met:

	*	Redistributions  of  source  code  must  retain  the above copyright
		notice,  this  list  of  conditions  and  the  following  disclaimer.
	* 	Redistributions  in  binary  form must reproduce the above copyright
		notice,  this list of conditions and the following disclaimer in the
		documentation  and/or other materials provided with the distribution.
	* 	Neither  the  name of the University of Tennessee, Knoxville nor the
		names of its contributors may be used to endorse or promote products
		derived from this software without specific prior written permission.

	THIS  SOFTWARE  IS  PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	''AS IS''  AND  ANY  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	LIMITED  TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	A  PARTICULAR  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL,  EXEMPLARY,  OR  CONSEQUENTIAL  DAMAGES  (INCLUDING,  BUT NOT
	LIMITED  TO,  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA,  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY  OF  LIABILITY,  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF  THIS  SOFTWARE,  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/

#include <stdio.h>
#include <cuda.h>
#include <cuda_runtime_api.h>
#include <cublas.h>
#include "gemv_offset_core.cuh"

#if(SM >= 30)

#define sgemvn_offset_bs		(64)
#define sgemvn_offset_ty		(16)
#define sgemvn_offset_by		(4)

#define sgemvt_offset_bs		(64)
#define sgemvt_offset_ty		(8)
#define sgemvt_offset_by		(4)

#else

#define sgemvn_offset_bs		(32)
#define sgemvn_offset_ty		(8)
#define sgemvn_offset_by		(1)

#define sgemvt_offset_bs		(32)
#define sgemvt_offset_ty		(8)
#define sgemvt_offset_by		(1)
#endif


extern "C"
int kblas_sscal_async(int n, float alpha, float *x, int incx, cudaStream_t stream);

int kblas_sgemv_offset_driver( char trans, int rows, int cols,
						        float alpha, float *dA, int lda, 
						        float *dX, int incx, 
						        float  beta, float *dY, int incy,
						        int offset_r, int offset_c, 
						        cudaStream_t stream = 0)
{
	if(trans == 'n' || trans == 'N')
	{
		
		//**** Config parameters
		const int thread_x = sgemvn_offset_bs;
		const int thread_y = sgemvn_offset_ty; 
		const int elements_per_thread = thread_x/(2*thread_y);
		const int grid_y_n = sgemvn_offset_by;
		//*************************
		
		/** offset necessary calculation **/
		int offset_r_ = offset_r % sgemvn_offset_bs;
		int offset_c_ = offset_c % sgemvn_offset_bs;
		int total_blocks_skipped_r = offset_r / sgemvn_offset_bs; 
		int total_blocks_skipped_c = offset_c / sgemvn_offset_bs; 
		int my_skipped_blocks_r = total_blocks_skipped_r;
		int my_skipped_blocks_c = total_blocks_skipped_c/ngpus; 
		if(gpu_gid < (total_blocks_skipped_c%ngpus)) my_skipped_blocks_c += 1;
		int ref_gpu = total_blocks_skipped_c%ngpus; 
		int new_gpu_gid = (gpu_gid - ref_gpu + ngpus) % ngpus;
		// Advance pointers accordingly
		dA += my_skipped_blocks_c * sgemvn_offset_bs * lda;
		dA += my_skipped_blocks_r * sgemvn_offset_bs; 
		dX += my_skipped_blocks_c * sgemvn_offset_bs * incx;
		dY += my_skipped_blocks_r * sgemvn_offset_bs * incy;
		rows -= my_skipped_blocks_r * sgemvn_offset_bs;
		cols -= my_skipped_blocks_c * sgemvn_offset_bs;
		/** end offset necessary calculation **/
		
		int nstripes = (cols/sgemvn_offset_bs) + ((cols%sgemvn_offset_bs) != 0);
		
		// scaling with beta
		//if(gpu_gid == 0)cublasSscal(rows-offset_, beta, dY+(offset_*incy), incy);
		if(gpu_gid == 0)kblas_sscal_async(rows-offset_r_, beta, dY+(offset_r_*incy), incy, stream);
		
		int cols_ = sgemvn_offset_bs * ( (cols/sgemvn_offset_bs)/ngpus );
		if(new_gpu_gid < (cols/sgemvn_offset_bs)%ngpus) cols_ += sgemvn_offset_bs;
		if(new_gpu_gid == (cols/sgemvn_offset_bs)%ngpus) cols_ += cols%sgemvn_offset_bs;
		
		int mod_r = rows % sgemvn_offset_bs;
		int mod_c = cols_ % sgemvn_offset_bs;
		
		if(mod_r == 0 && mod_c == 0)
		{
			// special case
			int blocks = rows/sgemvn_offset_bs;
			dim3 dimBlock(thread_x, thread_y);
			dim3 dimGrid(blocks, grid_y_n);
			if(blocks == 0) return 0;
			gemvn_special_offset<float, sgemvn_offset_bs, sgemvn_offset_bs, sgemvn_offset_ty, elements_per_thread>
									<<<dimGrid, dimBlock, 0, stream>>>
									(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, nstripes, offset_r_, offset_c_);
		}
		else
		{
			// generic case for columns only
			const int irregular_cols = mod_c % elements_per_thread;
			
			int blocks = (rows/sgemvn_offset_bs) + (mod_r != 0);
			if(mod_r == 0)blocks += 1;	// dummy thread block, will return immediately if mod_r == 0
			
			dim3 dimBlock(thread_x, thread_y);
			dim3 dimGrid(blocks, grid_y_n);
			if(blocks == 0) return 0;
			
			switch(irregular_cols)
			{
				/**
				 * The kernel for irregular dimensions has an extra template parameter.
				 * This parameter must be among the values listed in the switch-case statement below.
				 * The possible values are in the range 0 - (elements_per_thread-1)
				 * Make sure these values are updated whenever you change the configuration parameters.  
				**/	
				case  0: gemvn_generic_offset<float, sgemvn_offset_bs, sgemvn_offset_bs, sgemvn_offset_ty, elements_per_thread,  0><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_); break;
				case  1: gemvn_generic_offset<float, sgemvn_offset_bs, sgemvn_offset_bs, sgemvn_offset_ty, elements_per_thread,  1><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_); break;
				case  2: gemvn_generic_offset<float, sgemvn_offset_bs, sgemvn_offset_bs, sgemvn_offset_ty, elements_per_thread,  2><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_); break;
				case  3: gemvn_generic_offset<float, sgemvn_offset_bs, sgemvn_offset_bs, sgemvn_offset_ty, elements_per_thread,  3><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_); break;
				case  4: gemvn_generic_offset<float, sgemvn_offset_bs, sgemvn_offset_bs, sgemvn_offset_ty, elements_per_thread,  4><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_); break;
				case  5: gemvn_generic_offset<float, sgemvn_offset_bs, sgemvn_offset_bs, sgemvn_offset_ty, elements_per_thread,  5><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_); break;
				case  6: gemvn_generic_offset<float, sgemvn_offset_bs, sgemvn_offset_bs, sgemvn_offset_ty, elements_per_thread,  6><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_); break;
				case  7: gemvn_generic_offset<float, sgemvn_offset_bs, sgemvn_offset_bs, sgemvn_offset_ty, elements_per_thread,  7><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_); break;
				case  8: gemvn_generic_offset<float, sgemvn_offset_bs, sgemvn_offset_bs, sgemvn_offset_ty, elements_per_thread,  8><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_); break;
				case  9: gemvn_generic_offset<float, sgemvn_offset_bs, sgemvn_offset_bs, sgemvn_offset_ty, elements_per_thread,  9><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_); break;
				case 10: gemvn_generic_offset<float, sgemvn_offset_bs, sgemvn_offset_bs, sgemvn_offset_ty, elements_per_thread, 10><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_); break;
				case 11: gemvn_generic_offset<float, sgemvn_offset_bs, sgemvn_offset_bs, sgemvn_offset_ty, elements_per_thread, 11><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_); break;
				case 12: gemvn_generic_offset<float, sgemvn_offset_bs, sgemvn_offset_bs, sgemvn_offset_ty, elements_per_thread, 12><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_); break;
				case 13: gemvn_generic_offset<float, sgemvn_offset_bs, sgemvn_offset_bs, sgemvn_offset_ty, elements_per_thread, 13><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_); break;
				case 14: gemvn_generic_offset<float, sgemvn_offset_bs, sgemvn_offset_bs, sgemvn_offset_ty, elements_per_thread, 14><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_); break;
				case 15: gemvn_generic_offset<float, sgemvn_offset_bs, sgemvn_offset_bs, sgemvn_offset_ty, elements_per_thread, 15><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_); break;
				default: printf("SGEMV-N error: improper template parameter. Please read the inline documentation for this function. \n"); return -1;	
			}
		}
	}	// end of non-transpose case
	else if (trans == 't' || trans == 'T' || trans == 'c' || trans == 'C')
	{
		int conj;
		if(trans == 'c' || trans == 'C') conj = 1;
		else conj = 0;
		//**** Config parameters
		const int thread_x = sgemvt_offset_bs;
		const int thread_y = sgemvt_offset_ty; 
		const int elements_per_thread = thread_x/(2*thread_y);
		const int grid_y_t = sgemvt_offset_by;
		//*************************
		
		/** offset necessary calculation **/
		int offset_r_ = offset_r % sgemvt_offset_bs;
		int offset_c_ = offset_c % sgemvt_offset_bs;
		int total_blocks_skipped_r = offset_r / sgemvt_offset_bs; 
		int total_blocks_skipped_c = offset_c / sgemvt_offset_bs; 
		int my_skipped_blocks_r = total_blocks_skipped_r; 
		int my_skipped_blocks_c = total_blocks_skipped_c/ngpus; 
		if(gpu_gid < (total_blocks_skipped_c%ngpus)) my_skipped_blocks_c += 1;
		int ref_gpu = total_blocks_skipped_c%ngpus; 
		int new_gpu_gid = (gpu_gid - ref_gpu + ngpus) % ngpus;
		
		//if(new_gpu_gid != 3){return 0;}
		// Advance pointers accordingly
		dA += my_skipped_blocks_c * sgemvt_offset_bs * lda;
		dA += my_skipped_blocks_r * sgemvt_offset_bs; 
		dX += my_skipped_blocks_r * sgemvt_offset_bs * incx;
		dY += my_skipped_blocks_c * sgemvt_offset_bs * incy;
		rows -= my_skipped_blocks_r * sgemvt_offset_bs;
		cols -= my_skipped_blocks_c * sgemvt_offset_bs;
		/** end offset necessary calculation **/
		
		int nstripes = (cols/sgemvt_offset_bs) + ((cols%sgemvt_offset_bs) != 0);
		
		// scaling with beta
		//if(gpu_gid == 0)cublasSscal(cols-offset_, beta, dY+(offset_*incy), incy);
		if(gpu_gid == 0)kblas_sscal_async(cols-offset_c_, beta, dY+(offset_c_*incy), incy, stream);
		
		int cols_ = sgemvt_offset_bs * ( (cols/sgemvt_offset_bs)/ngpus );
		if(new_gpu_gid < (cols/sgemvt_offset_bs)%ngpus) cols_ += sgemvt_offset_bs;
		if(new_gpu_gid == (cols/sgemvt_offset_bs)%ngpus) cols_ += cols%sgemvt_offset_bs;
		
		int mod_r = rows % sgemvt_offset_bs;
		int mod_c = cols_ % sgemvt_offset_bs;
		
		if(mod_r == 0 && mod_c == 0)
		{	
			int blocks = cols_/sgemvt_offset_bs;
			dim3 dimBlock(thread_x, thread_y);
			dim3 dimGrid(blocks, grid_y_t);
			if(blocks == 0) return 0;
			gemvt_special_offset<float, sgemvt_offset_bs, thread_x, thread_y, elements_per_thread><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, nstripes, offset_r_, offset_c_, conj); 
			
		}
		else
		{
			const int irregular_cols = mod_c % elements_per_thread;
			int blocks = cols_/sgemvt_offset_bs + (mod_c != 0);
			int gpu_last = (nstripes+ngpus-1)%ngpus;
			if(mod_c == 0 && new_gpu_gid == gpu_last) blocks += 1; // dummy thread block, will return if mod_c == 0
			dim3 dimBlock(thread_x, thread_y);
			dim3 dimGrid(blocks, grid_y_t);
			if(blocks == 0) return 0;
			
			switch(irregular_cols)
			{
				/**
				  * The kernel for irregular dimensions has an extra template parameter.
				  * This parameter must be among the values listed in the switch-case statement below.
				  * The possible values are in the range 0 - (elements_per_thread-1)
				  * Make sure these values are updated whenever you change the configuration parameters.  
				**/	
				case  0: gemvt_generic_offset<float, sgemvt_offset_bs, thread_x, thread_y, elements_per_thread,  0><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_, conj); break;
				case  1: gemvt_generic_offset<float, sgemvt_offset_bs, thread_x, thread_y, elements_per_thread,  1><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_, conj); break;
				case  2: gemvt_generic_offset<float, sgemvt_offset_bs, thread_x, thread_y, elements_per_thread,  2><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_, conj); break;
				case  3: gemvt_generic_offset<float, sgemvt_offset_bs, thread_x, thread_y, elements_per_thread,  3><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_, conj); break;
				case  4: gemvt_generic_offset<float, sgemvt_offset_bs, thread_x, thread_y, elements_per_thread,  4><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_, conj); break;
				case  5: gemvt_generic_offset<float, sgemvt_offset_bs, thread_x, thread_y, elements_per_thread,  5><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_, conj); break;
				case  6: gemvt_generic_offset<float, sgemvt_offset_bs, thread_x, thread_y, elements_per_thread,  6><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_, conj); break;
				case  7: gemvt_generic_offset<float, sgemvt_offset_bs, thread_x, thread_y, elements_per_thread,  7><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_, conj); break;
				case  8: gemvt_generic_offset<float, sgemvt_offset_bs, thread_x, thread_y, elements_per_thread,  8><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_, conj); break;
				case  9: gemvt_generic_offset<float, sgemvt_offset_bs, thread_x, thread_y, elements_per_thread,  9><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_, conj); break;
				case 10: gemvt_generic_offset<float, sgemvt_offset_bs, thread_x, thread_y, elements_per_thread, 10><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_, conj); break;
				case 11: gemvt_generic_offset<float, sgemvt_offset_bs, thread_x, thread_y, elements_per_thread, 11><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_, conj); break;
				case 12: gemvt_generic_offset<float, sgemvt_offset_bs, thread_x, thread_y, elements_per_thread, 12><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_, conj); break;
				case 13: gemvt_generic_offset<float, sgemvt_offset_bs, thread_x, thread_y, elements_per_thread, 13><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_, conj); break;
				case 14: gemvt_generic_offset<float, sgemvt_offset_bs, thread_x, thread_y, elements_per_thread, 14><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_, conj); break;
				case 15: gemvt_generic_offset<float, sgemvt_offset_bs, thread_x, thread_y, elements_per_thread, 15><<<dimGrid, dimBlock, 0, stream>>>(rows, cols_, alpha, dA, lda, dX, incx, beta, dY, incy, mod_r, mod_c, nstripes, offset_r_, offset_c_, conj); break;
				default: printf("SGEMV-T error: improper template parameter. Please read the inline documentation for this function. \n"); return -1;
			}
		}
	}
	else 
	{
		printf("SGEMV error: Unrecognized transpose mode %c \n", trans);
		return -1;
	}
	
	return 0;
}
/***********************************************************************************/
extern "C"
int kblas_sgemv_offset( char trans, int rows, int cols,
						float alpha, float *dA, int lda, 
						float *dX, int incx, 
						float beta, float *dY, int incy, 
						int offset_r, int offset_c)
{
	return kblas_sgemv_offset_driver( trans, rows, cols, 
	                                alpha, dA, lda, 
	                                dX, incx, 
	                                beta, dY, incy, 
	                                offset_r, offset_c);
}

/*************************************************************************************/
extern "C"
int kblas_sgemv_offset_async( char trans, int rows, int cols,
							float alpha, float *dA, int lda, 
							float *dX, int incx, 
							float  beta, float *dY, int incy, 
							int offset_r, int offset_c, 
							cudaStream_t stream)
{
	return kblas_sgemv_offset_driver(  trans, rows, cols, 
	                            alpha, dA, lda, 
	                            dX, incx, 
	                            beta, dY, incy, offset_r, offset_c, 
	                            stream);
}
/*************************************************************************************/
