 /**
 -- (C) Copyright 2013 King Abdullah University of Science and Technology
  Authors:
  Ahmad Abdelfattah (ahmad.ahmad@kaust.edu.sa)
  David Keyes (david.keyes@kaust.edu.sa)
  Hatem Ltaief (hatem.ltaief@kaust.edu.sa)

  Redistribution  and  use  in  source and binary forms, with or without
  modification,  are  permitted  provided  that the following conditions
  are met:

  * Redistributions  of  source  code  must  retain  the above copyright
    notice,  this  list  of  conditions  and  the  following  disclaimer.
  * Redistributions  in  binary  form must reproduce the above copyright
    notice,  this list of conditions and the following disclaimer in the
    documentation  and/or other materials provided with the distribution.
  * Neither  the  name of the King Abdullah University of Science and
    Technology nor the names of its contributors may be used to endorse 
    or promote products derived from this software without specific prior 
    written permission.

  THIS  SOFTWARE  IS  PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  ``AS IS''  AND  ANY  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
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
#ifndef _KBLAS_H_
#define _KBLAS_H_

#include "defs.h"

#ifdef __cplusplus
extern "C" {
#endif
  
// scal
int kblas_cscal(int n, cuFloatComplex alpha, cuFloatComplex *x, int incx);
int kblas_dscal(int n, double alpha, double *x, int incx);
int kblas_sscal(int n, float alpha, float *x, int incx);
int kblas_zscal(int n, cuDoubleComplex alpha, cuDoubleComplex *x, int incx);

int kblas_cscal_async(int n, cuFloatComplex alpha, cuFloatComplex *x, int incx, cudaStream_t stream);
int kblas_dscal_async(int n, double alpha, double *x, int incx, cudaStream_t stream);
int kblas_sscal_async(int n, float alpha, float *x, int incx, cudaStream_t stream);
int kblas_zscal_async(int n, cuDoubleComplex alpha, cuDoubleComplex *x, int incx, cudaStream_t stream);

// kblas SYMV/HEMV
int kblas_ssymv( char uplo, int m, float alpha, float *dA, int lda, float *dX, int incx, float  beta, float *dY, int incy);
int kblas_dsymv( char uplo, int m, double alpha, double *dA, int lda, double *dX, int incx, double  beta, double *dY, int incy);
int kblas_chemv( char uplo, int m, cuFloatComplex alpha, cuFloatComplex *dA, int lda, cuFloatComplex *dX, int incx, cuFloatComplex  beta, cuFloatComplex *dY, int incy);
int kblas_zhemv( char uplo, int m, cuDoubleComplex alpha, cuDoubleComplex *dA, int lda, cuDoubleComplex *dX, int incx, cuDoubleComplex  beta, cuDoubleComplex *dY, int incy);

int kblas_ssymv_async( char uplo, int m, float alpha, float *dA, int lda, float *dX, int incx, float  beta, float *dY, int incy, cudaStream_t stream);
int kblas_dsymv_async( char uplo, int m, double alpha, double *dA, int lda, double *dX, int incx, double  beta, double *dY, int incy, cudaStream_t stream);
int kblas_chemv_async( char uplo, int m, cuFloatComplex alpha, cuFloatComplex *dA, int lda, cuFloatComplex *dX, int incx, cuFloatComplex  beta, cuFloatComplex *dY, int incy, cudaStream_t stream);
int kblas_zhemv_async( char uplo, int m, cuDoubleComplex alpha, cuDoubleComplex *dA, int lda, cuDoubleComplex *dX, int incx, cuDoubleComplex  beta, cuDoubleComplex *dY, int incy, cudaStream_t stream);

// kblas GEMV
int kblas_sgemv( char trans, int rows, int cols, float alpha, float *dA, int lda, float *dX, int incx, float  beta, float *dY, int incy);
int kblas_dgemv( char trans, int rows, int cols, double alpha, double *dA, int lda, double *dX, int incx, double  beta, double *dY, int incy);
int kblas_cgemv( char trans, int rows, int cols, cuFloatComplex alpha, cuFloatComplex *dA, int lda, cuFloatComplex *dX, int incx, cuFloatComplex  beta, cuFloatComplex *dY, int incy);
int kblas_zgemv( char trans, int rows, int cols, cuDoubleComplex alpha, cuDoubleComplex *dA, int lda, cuDoubleComplex *dX, int incx, cuDoubleComplex  beta, cuDoubleComplex *dY, int incy);

int kblas_sgemv_async( char trans, int rows, int cols, float alpha, float *dA, int lda, float *dX, int incx, float  beta, float *dY, int incy, cudaStream_t stream);
int kblas_dgemv_async( char trans, int rows, int cols, double alpha, double *dA, int lda, double *dX, int incx, double  beta, double *dY, int incy, cudaStream_t stream);
int kblas_cgemv_async( char trans, int rows, int cols, cuFloatComplex alpha, cuFloatComplex *dA, int lda, cuFloatComplex *dX, int incx, cuFloatComplex  beta, cuFloatComplex *dY, int incy, cudaStream_t stream);
int kblas_zgemv_async( char trans, int rows, int cols, cuDoubleComplex alpha, cuDoubleComplex *dA, int lda, cuDoubleComplex *dX, int incx, cuDoubleComplex  beta, cuDoubleComplex *dY, int incy, cudaStream_t stream);

// kblas GEMV2
int kblas_sgemv2(char trans, int rows, int cols, float alpha, float *dA, int lda, float *dX, int incx, float  beta, float *dY, int incy);
int kblas_dgemv2(char trans, int rows, int cols, double alpha, double *dA, int lda, double *dX, int incx, double  beta, double *dY, int incy);
int kblas_cgemv2(char trans, int rows, int cols, cuFloatComplex alpha, cuFloatComplex *dA, int lda, cuFloatComplex *dX, int incx, cuFloatComplex  beta, cuFloatComplex *dY, int incy);
int kblas_zgemv2(char trans, int rows, int cols, cuDoubleComplex alpha, cuDoubleComplex *dA, int lda, cuDoubleComplex *dX, int incx, cuDoubleComplex  beta, cuDoubleComplex *dY, int incy);
				
int kblas_sgemv2_async(	char trans, int rows, int cols, float alpha, float *dA, int lda, float *dX, int incx, float  beta, float *dY, int incy, cudaStream_t stream);
int kblas_dgemv2_async(	char trans, int rows, int cols, double alpha, double *dA, int lda, double *dX, int incx, double  beta, double *dY, int incy, cudaStream_t stream);
int kblas_cgemv2_async(	char trans, int rows, int cols, cuFloatComplex alpha, cuFloatComplex *dA, int lda, cuFloatComplex *dX, int incx, cuFloatComplex  beta, cuFloatComplex *dY, int incy, cudaStream_t stream);
int kblas_zgemv2_async(	char trans, int rows, int cols, cuDoubleComplex alpha, cuDoubleComplex *dA, int lda, cuDoubleComplex *dX, int incx, cuDoubleComplex  beta, cuDoubleComplex *dY, int incy, cudaStream_t stream);

// GEMV offset
int kblas_sgemv_offset( char trans, int rows, int cols, float alpha, float *dA, int lda, float *dX, int incx, float beta, float *dY, int incy, int offset_r, int offset_c);
int kblas_dgemv_offset( char trans, int rows, int cols, double alpha, double *dA, int lda, double *dX, int incx, double beta, double *dY, int incy, int offset_r, int offset_c);
int kblas_cgemv_offset( char trans, int rows, int cols, cuFloatComplex alpha, cuFloatComplex *dA, int lda, cuFloatComplex *dX, int incx, cuFloatComplex beta, cuFloatComplex *dY, int incy, int offset_r, int offset_c);
int kblas_zgemv_offset( char trans, int rows, int cols, cuDoubleComplex alpha, cuDoubleComplex *dA, int lda, cuDoubleComplex *dX, int incx, cuDoubleComplex beta, cuDoubleComplex *dY, int incy, int offset_r, int offset_c);

int kblas_sgemv_offset_async( char trans, int rows, int cols, float alpha, float *dA, int lda, float *dX, int incx, float  beta, float *dY, int incy, int offset_r, int offset_c, cudaStream_t stream);
int kblas_dgemv_offset_async( char trans, int rows, int cols, double alpha, double *dA, int lda, double *dX, int incx, double  beta, double *dY, int incy, int offset_r, int offset_c, cudaStream_t stream);
int kblas_cgemv_offset_async( char trans, int rows, int cols, cuFloatComplex alpha, cuFloatComplex *dA, int lda, cuFloatComplex *dX, int incx, cuFloatComplex  beta, cuFloatComplex *dY, int incy, int offset_r, int offset_c, cudaStream_t stream);
int kblas_zgemv_offset_async( char trans, int rows, int cols, cuDoubleComplex alpha, cuDoubleComplex *dA, int lda, cuDoubleComplex *dX, int incx, cuDoubleComplex  beta, cuDoubleComplex *dY, int incy, int offset_r, int offset_c, cudaStream_t stream);

int kblas_sgemv2_offset( char trans, int rows, int cols, float alpha, float *dA, int lda, float *dX, int incx, float beta, float *dY, int incy, int offset_r, int offset_c);
int kblas_dgemv2_offset( char trans, int rows, int cols, double alpha, double *dA, int lda, double *dX, int incx, double beta, double *dY, int incy, int offset_r, int offset_c);
int kblas_cgemv2_offset( char trans, int rows, int cols, cuFloatComplex alpha, cuFloatComplex *dA, int lda, cuFloatComplex *dX, int incx, cuFloatComplex beta, cuFloatComplex *dY, int incy, int offset_r, int offset_c);
int kblas_zgemv2_offset( char trans, int rows, int cols, cuDoubleComplex alpha, cuDoubleComplex *dA, int lda, cuDoubleComplex *dX, int incx, cuDoubleComplex beta, cuDoubleComplex *dY, int incy, int offset_r, int offset_c);

int kblas_sgemv2_offset_async( char trans, int rows, int cols, float alpha, float *dA, int lda, float *dX, int incx, float  beta, float *dY, int incy, int offset_r, int offset_c, cudaStream_t stream);
int kblas_dgemv2_offset_async( char trans, int rows, int cols, double alpha, double *dA, int lda, double *dX, int incx, double  beta, double *dY, int incy, int offset_r, int offset_c, cudaStream_t stream);
int kblas_cgemv2_offset_async( char trans, int rows, int cols, cuFloatComplex alpha, cuFloatComplex *dA, int lda, cuFloatComplex *dX, int incx, cuFloatComplex  beta, cuFloatComplex *dY, int incy, int offset_r, int offset_c, cudaStream_t stream);
int kblas_zgemv2_offset_async( char trans, int rows, int cols, cuDoubleComplex alpha, cuDoubleComplex *dA, int lda, cuDoubleComplex *dX, int incx, cuDoubleComplex  beta, cuDoubleComplex *dY, int incy, int offset_r, int offset_c, cudaStream_t stream);

// SYHEMV offset
int kblas_ssymv_offset( char uplo, int m, float alpha, float *dA, int lda, float *dX, int incx, float beta, float *dY, int incy, int offset);
int kblas_dsymv_offset( char uplo, int m, double alpha, double *dA, int lda, double *dX, int incx, double beta, double *dY, int incy, int offset);
int kblas_chemv_offset( char uplo, int m, cuFloatComplex alpha, cuFloatComplex *dA, int lda, cuFloatComplex *dX, int incx, cuFloatComplex beta, cuFloatComplex *dY, int incy, int offset);
int kblas_zhemv_offset( char uplo, int m, cuDoubleComplex alpha, cuDoubleComplex *dA, int lda, cuDoubleComplex *dX, int incx, cuDoubleComplex beta, cuDoubleComplex *dY, int incy, int offset);

int kblas_ssymv_offset_async( char uplo, int m, float alpha, float *dA, int lda, float *dX, int incx, float  beta, float *dY, int incy, int offset, cudaStream_t stream);
int kblas_dsymv_offset_async( char uplo, int m, double alpha, double *dA, int lda, double *dX, int incx, double  beta, double *dY, int incy, int offset, cudaStream_t stream);
int kblas_chemv_offset_async( char uplo, int m, cuFloatComplex alpha, cuFloatComplex *dA, int lda, cuFloatComplex *dX, int incx, cuFloatComplex  beta, cuFloatComplex *dY, int incy, int offset, cudaStream_t stream);

int kblas_zhemv_offset_async( char uplo, int m, cuDoubleComplex alpha, cuDoubleComplex *dA, int lda, cuDoubleComplex *dX, int incx, cuDoubleComplex  beta, cuDoubleComplex *dY, int incy, int offset, cudaStream_t stream);

// multi gpu symv
//sync
int kblas_ssymv_mgpu( char uplo, int m,
                      float alpha, float **dA, int lda,
                      float **dX, int incx,
                      float  beta, float **dY, int incy,
                      int ngpus,
                      int offset);

int kblas_dsymv_mgpu( char uplo, int m,
                      double alpha, double **dA, int lda,
                      double **dX, int incx,
                      double  beta, double **dY, int incy,
                      int ngpus,
                      int offset);

int kblas_chemv_mgpu( char uplo, int m,
                      cuFloatComplex alpha, cuFloatComplex **dA, int lda,
                      cuFloatComplex **dX, int incx,
                      cuFloatComplex  beta, cuFloatComplex **dY, int incy,
                      int ngpus,
                      int offset);

int kblas_zhemv_mgpu( char uplo, int m,
                      cuDoubleComplex alpha, cuDoubleComplex **dA, int lda,
                      cuDoubleComplex **dX, int incx,
                      cuDoubleComplex  beta, cuDoubleComplex **dY, int incy,
                      int ngpus,
                      int offset);
// async
int kblas_ssymv_mgpu_async( char uplo, int m, 
                            float alpha, float **dA, int lda,
                            float **dX, int incx,
                            float  beta, float **dY, int incy,
                            int ngpus,
                            int offset,
                            cudaStream_t stream[MAX_NGPUS][MAX_STREAMS]);

int kblas_dsymv_mgpu_async( char uplo, int m, 
                            double alpha, double **dA, int lda,
                            double **dX, int incx,
                            double  beta, double **dY, int incy,
                            int ngpus,
                            int offset,
                            cudaStream_t stream[MAX_NGPUS][MAX_STREAMS]);

int kblas_chemv_mgpu_async( char uplo, int m, 
                            cuFloatComplex alpha, cuFloatComplex **dA, int lda,
                            cuFloatComplex **dX, int incx,
                            cuFloatComplex  beta, cuFloatComplex **dY, int incy,
                            int ngpus,
                            int offset,
                            cudaStream_t stream[MAX_NGPUS][MAX_STREAMS]);

int kblas_zhemv_mgpu_async( char uplo, int m, 
                            cuDoubleComplex alpha, cuDoubleComplex **dA, int lda,
                            cuDoubleComplex **dX, int incx,
                            cuDoubleComplex  beta, cuDoubleComplex **dY, int incy,
                            int ngpus,
                            int offset,
                            cudaStream_t stream[MAX_NGPUS][MAX_STREAMS]);


// multi gpu gemv
// sync
int kblas_sgemv_mgpu( char trans, int rows, int cols,
                      float alpha, float **dA, int lda,
                      float **dX, int incx,
                      float  beta, float **dY, int incy,
                      int ngpus,
                      int offset_r, int offset_c);

int kblas_dgemv_mgpu( char trans, int rows, int cols,
                      double alpha, double **dA, int lda,
                      double **dX, int incx,
                      double  beta, double **dY, int incy,
                      int ngpus,
                      int offset_r, int offset_c);

int kblas_cgemv_mgpu( char trans, int rows, int cols,
                      cuFloatComplex alpha, cuFloatComplex **dA, int lda,
                      cuFloatComplex **dX, int incx,
                      cuFloatComplex  beta, cuFloatComplex **dY, int incy,
                      int ngpus,
                      int offset_r, int offset_c);

int kblas_zgemv_mgpu( char trans, int rows, int cols,
                      cuDoubleComplex alpha, cuDoubleComplex **dA, int lda,
                      cuDoubleComplex **dX, int incx,
                      cuDoubleComplex  beta, cuDoubleComplex **dY, int incy,
                      int ngpus,
                      int offset_r, int offset_c);

// async
int kblas_sgemv_mgpu_async( char trans, int rows, int cols,
                            float alpha, float **dA, int lda,
                            float **dX, int incx,
                            float  beta, float **dY, int incy,
                            int ngpus,
                            int offset_r, int offset_c,
                            cudaStream_t stream[MAX_NGPUS][MAX_STREAMS]);

int kblas_dgemv_mgpu_async( char trans, int rows, int cols,
                            double alpha, double **dA, int lda,
                            double **dX, int incx,
                            double  beta, double **dY, int incy,
                            int ngpus,
                            int offset_r, int offset_c,
                            cudaStream_t stream[MAX_NGPUS][MAX_STREAMS]);

int kblas_cgemv_mgpu_async( char trans, int rows, int cols,
                            cuFloatComplex alpha, cuFloatComplex **dA, int lda,
                            cuFloatComplex **dX, int incx,
                            cuFloatComplex  beta, cuFloatComplex **dY, int incy,
                            int ngpus,
                            int offset_r, int offset_c,
                            cudaStream_t stream[MAX_NGPUS][MAX_STREAMS]);

int kblas_zgemv_mgpu_async( char trans, int rows, int cols,
                            cuDoubleComplex alpha, cuDoubleComplex **dA, int lda,
                            cuDoubleComplex **dX, int incx,
                            cuDoubleComplex  beta, cuDoubleComplex **dY, int incy,
                            int ngpus,
                            int offset_r, int offset_c,
                            cudaStream_t stream[MAX_NGPUS][MAX_STREAMS]);

// gemm_mgpu (out of core)
void kblas_sgemm_mgpu(char transa, char transb, long m, long n, long k,
                      float alpha, const float* A, long lda,
                      const float* B, long ldb,
                      float beta, float* C, long ldc,
                      long ngpus, long* gpu_id,
                      long *tile);
void kblas_dgemm_mgpu(char transa, char transb, long m, long n, long k,
                      double alpha, const double* A, long lda,
                      const double* B, long ldb,
                      double beta, double* C, long ldc,
                      long ngpus, long* gpu_id,
                      long *tile);
void kblas_cgemm_mgpu(char transa, char transb, long m, long n, long k,
                      cuFloatComplex alpha, const cuFloatComplex* A, long lda,
                      const cuFloatComplex* B, long ldb,
                      cuFloatComplex beta, cuFloatComplex* C, long ldc,
                      long ngpus, long* gpu_id,
                      long *tile);
void kblas_zgemm_mgpu(char transa, char transb, long m, long n, long k,
                      cuDoubleComplex alpha, const cuDoubleComplex* A, long lda,
                      const cuDoubleComplex* B, long ldb,
                      cuDoubleComplex beta, cuDoubleComplex* C, long ldc,
                      long ngpus, long* gpu_id,
                      long *tile);					

// auxiliary mgpu control functions
void kblas_smalloc_mgpu_1D(	int rows, int cols, float** dA, int ngpus, int ldb, int block_size);
void kblas_dmalloc_mgpu_1D(	int rows, int cols, double** dA, int ngpus, int ldb, int block_size);
void kblas_cmalloc_mgpu_1D(	int rows, int cols, cuFloatComplex** dA, int ngpus, int ldb, int block_size);
void kblas_zmalloc_mgpu_1D(	int rows, int cols, cuDoubleComplex** dA, int ngpus, int ldb, int block_size);

void kblas_ssetmatrix_mgpu_1D(int rows, int cols, float* A, int LDA, float** dA, int LDB, int ngpus, int block_size);
void kblas_dsetmatrix_mgpu_1D(int rows, int cols, double* A, int LDA, double** dA, int LDB, int ngpus, int block_size);
void kblas_csetmatrix_mgpu_1D(int rows, int cols, cuFloatComplex* A, int LDA, cuFloatComplex** dA, int LDB, int ngpus, int block_size);
void kblas_zsetmatrix_mgpu_1D(int rows, int cols, cuDoubleComplex* A, int LDA, cuDoubleComplex** dA, int LDB, int ngpus, int block_size);

void kblas_ssetvector_mgpu_1D(int n, float* Y, float** dY, int ngpus, int block_size);
void kblas_dsetvector_mgpu_1D(int n, double* Y, double** dY, int ngpus, int block_size);
void kblas_csetvector_mgpu_1D(int n, cuFloatComplex* Y, cuFloatComplex** dY, int ngpus, int block_size);
void kblas_zsetvector_mgpu_1D(int n, cuDoubleComplex* Y, cuDoubleComplex** dY, int ngpus, int block_size);

int get_ssymv_mgpu_bs(char uplo);
int get_dsymv_mgpu_bs(char uplo);
int get_chemv_mgpu_bs(char uplo);
int get_zhemv_mgpu_bs(char uplo);

int get_sgemv_mgpu_bs(char trans);
int get_dgemv_mgpu_bs(char trans);
int get_cgemv_mgpu_bs(char trans);
int get_zgemv_mgpu_bs(char trans);

//============================================================================
//BLAS3 routines
//============================================================================
#define KBLAS_Lower 'L'
#define KBLAS_Upper 'U'
#define KBLAS_Left 'L'
#define KBLAS_Right 'R'
#define KBLAS_Trans 'T'
#define KBLAS_NoTrans 'N'
#define KBLAS_Unit 'U'
#define KBLAS_NonUnit 'N'

/*/CPU API
#if defined(KBLAS_CPU_API)

#include "cblas.h"
void kblas_strmm(const enum CBLAS_ORDER Order,
                 const enum CBLAS_SIDE Side, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int M, const int N,
                 const float alpha, const float *A, const int lda,
                                          float *B, const int ldb);
void kblas_dtrmm(const enum CBLAS_ORDER Order,
                 const enum CBLAS_SIDE Side, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int M, const int N,
                 const double alpha, const double *A, const int lda,
                                           double *B, const int ldb);
void kblas_ctrmm(const enum CBLAS_ORDER Order,
                 const enum CBLAS_SIDE Side, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int M, const int N,
                 const void *alpha, const void *A, const int lda,
                                          void *B, const int ldb);
void kblas_ztrmm(const enum CBLAS_ORDER Order,
                 const enum CBLAS_SIDE Side, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int M, const int N,
                 const void *alpha, const void *A, const int lda,
                                          void *B, const int ldb);
#endif*/


/*
int kblas_strsm(
  char side, char uplo, char trans, char diag,
  int m, int n,
  float alpha, const float *A, int incA,
                      float *B, int incB);

int kblas_dtrsm(
  char side, char uplo, char trans, char diag,
  int m, int n,
  double alpha, const double *A, int incA,
                        double *B, int incB);

int kblas_ctrsm(
  char side, char uplo, char trans, char diag,
  int m, int n,
  cuComplex alpha, const cuComplex *A, int incA,
                          cuComplex *B, int incB);

int kblas_ztrsm(
  char side, char uplo, char trans, char diag,
  int m, int n,
  cuDoubleComplex alpha, const cuDoubleComplex *A, int incA,
                                cuDoubleComplex *B, int incB);

int kblas_strsm_async(
  char side, char uplo, char trans, char diag,
  int m, int n,
  float alpha, const float *A, int incA,
                      float *B, int incB,
  cudaStream_t    stream);

int kblas_dtrsm_async(
  char side, char uplo, char trans, char diag,
  int m, int n,
  double alpha, const double *A, int incA,
                        double *B, int incB,
  cudaStream_t    stream);

int kblas_ctrsm_async(
  char side, char uplo, char trans, char diag,
  int m, int n,
  cuComplex alpha, const cuComplex *A, int incA,
                          cuComplex *B, int incB,
  cudaStream_t    stream);

int kblas_ztrsm_async(
  char side, char uplo, char trans, char diag,
  int m, int n,
  cuDoubleComplex alpha, const cuDoubleComplex *A, int incA,
                                cuDoubleComplex *B, int incB,
  cudaStream_t    stream);*/



//cuBLAS_v2 API
#if defined(CUBLAS_V2_H_)
  //TRMM {
    //GPU API, data resides on Device memory {
      cublasStatus_t kblasStrmm(cublasHandle_t handle,
                                cublasSideMode_t side, cublasFillMode_t uplo,
                                cublasOperation_t trans, cublasDiagType_t diag,
                                int m, int n,
                                const float *alpha,
                                const float *A, int lda,
                                      float *B, int ldb);
      cublasStatus_t kblasDtrmm(cublasHandle_t handle,
                                cublasSideMode_t side, cublasFillMode_t uplo,
                                cublasOperation_t trans, cublasDiagType_t diag,
                                int m, int n,
                                const double *alpha,
                                const double *A, int lda,
                                      double *B, int ldb);
      cublasStatus_t kblasCtrmm(cublasHandle_t handle,
                                cublasSideMode_t side, cublasFillMode_t uplo,
                                cublasOperation_t trans, cublasDiagType_t diag,
                                int m, int n,
                                const cuComplex *alpha,
                                const cuComplex *A, int lda,
                                      cuComplex *B, int ldb);
      cublasStatus_t kblasZtrmm(cublasHandle_t handle,
                                cublasSideMode_t side, cublasFillMode_t uplo,
                                cublasOperation_t trans, cublasDiagType_t diag,
                                int m, int n,
                                const cuDoubleComplex *alpha,
                                const cuDoubleComplex *A, int lda,
                                      cuDoubleComplex *B, int ldb);
    //}
    //CPU API, data resides on Host memory {
      cublasStatus_t kblas_strmm(cublasHandle_t handle,
                                cublasSideMode_t side, cublasFillMode_t uplo,
                                cublasOperation_t trans, cublasDiagType_t diag,
                                int m, int n,
                                const float *alpha,
                                const float *A, int lda,
                                      float *B, int ldb);
      cublasStatus_t kblas_dtrmm(cublasHandle_t handle,
                                cublasSideMode_t side, cublasFillMode_t uplo,
                                cublasOperation_t trans, cublasDiagType_t diag,
                                int m, int n,
                                const double *alpha,
                                const double *A, int lda,
                                      double *B, int ldb);
      cublasStatus_t kblas_ctrmm(cublasHandle_t handle,
                                cublasSideMode_t side, cublasFillMode_t uplo,
                                cublasOperation_t trans, cublasDiagType_t diag,
                                int m, int n,
                                const cuComplex *alpha,
                                const cuComplex *A, int lda,
                                      cuComplex *B, int ldb);
      cublasStatus_t kblas_ztrmm(cublasHandle_t handle,
                                cublasSideMode_t side, cublasFillMode_t uplo,
                                cublasOperation_t trans, cublasDiagType_t diag,
                                int m, int n,
                                const cuDoubleComplex *alpha,
                                const cuDoubleComplex *A, int lda,
                                      cuDoubleComplex *B, int ldb);
    //}
  //}
  //TRSM {
    //GPU API, data resides on Device memory {
      cublasStatus_t kblasStrsm(cublasHandle_t handle,
                                cublasSideMode_t side, cublasFillMode_t uplo,
                                cublasOperation_t trans, cublasDiagType_t diag,
                                int m, int n,
                                const float *alpha,
                                const float *A, int lda,
                                      float *B, int ldb);
      cublasStatus_t kblasDtrsm(cublasHandle_t handle,
                                cublasSideMode_t side, cublasFillMode_t uplo,
                                cublasOperation_t trans, cublasDiagType_t diag,
                                int m, int n,
                                const double *alpha,
                                const double *A, int lda,
                                      double *B, int ldb);
      cublasStatus_t kblasCtrsm(cublasHandle_t handle,
                                cublasSideMode_t side, cublasFillMode_t uplo,
                                cublasOperation_t trans, cublasDiagType_t diag,
                                int m, int n,
                                const cuComplex *alpha,
                                const cuComplex *A, int lda,
                                      cuComplex *B, int ldb);
      cublasStatus_t kblasZtrsm(cublasHandle_t handle,
                                cublasSideMode_t side, cublasFillMode_t uplo,
                                cublasOperation_t trans, cublasDiagType_t diag,
                                int m, int n,
                                const cuDoubleComplex *alpha,
                                const cuDoubleComplex *A, int lda,
                                      cuDoubleComplex *B, int ldb);
    //}
    //CPU API, data resides on Host memory {
      cublasStatus_t kblas_strsm(cublasHandle_t handle,
                                cublasSideMode_t side, cublasFillMode_t uplo,
                                cublasOperation_t trans, cublasDiagType_t diag,
                                int m, int n,
                                const float *alpha,
                                const float *A, int lda,
                                      float *B, int ldb);
      cublasStatus_t kblas_dtrsm(cublasHandle_t handle,
                                cublasSideMode_t side, cublasFillMode_t uplo,
                                cublasOperation_t trans, cublasDiagType_t diag,
                                int m, int n,
                                const double *alpha,
                                const double *A, int lda,
                                      double *B, int ldb);
      cublasStatus_t kblas_ctrsm(cublasHandle_t handle,
                                cublasSideMode_t side, cublasFillMode_t uplo,
                                cublasOperation_t trans, cublasDiagType_t diag,
                                int m, int n,
                                const cuComplex *alpha,
                                const cuComplex *A, int lda,
                                      cuComplex *B, int ldb);
      cublasStatus_t kblas_ztrsm(cublasHandle_t handle,
                                cublasSideMode_t side, cublasFillMode_t uplo,
                                cublasOperation_t trans, cublasDiagType_t diag,
                                int m, int n,
                                const cuDoubleComplex *alpha,
                                const cuDoubleComplex *A, int lda,
                                      cuDoubleComplex *B, int ldb);
    //}
  //}
#else//CUBLAS_V2_H_
//cuBLAS Legacy API
//assumes cuBLAS default stream (NULL)
//GPU API, data resides on Device memory {
  void kblasStrmm(char side, char uplo, char trans, char diag,
                  int m, int n,
                  float alpha, const float *A, int lda,
                                    float *B, int ldb);
  void kblasDtrmm(char side, char uplo, char trans, char diag,
                  int m, int n,
                  double alpha, const double *A, int lda,
                                      double *B, int ldb);
  void kblasCtrmm(char side, char uplo, char trans, char diag,
                  int m, int n,
                  cuComplex alpha, const cuComplex *A, int lda,
                                        cuComplex *B, int ldb);
  void kblasZtrmm(char side, char uplo, char trans, char diag,
                  int m, int n,
                  cuDoubleComplex alpha, const cuDoubleComplex *A, int lda,
                  cuDoubleComplex *B, int ldb);
//}
/*/CPU API, data resides on Host memory {
  void kblas_strmm(char side, char uplo, char trans, char diag,
                  int m, int n,
                  float alpha, const float *A, int lda,
                                    float *B, int ldb);
  void kblas_dtrmm(char side, char uplo, char trans, char diag,
                  int m, int n,
                  double alpha, const double *A, int lda,
                                      double *B, int ldb);
  void kblas_ctrmm(char side, char uplo, char trans, char diag,
                  int m, int n,
                  cuComplex alpha, const cuComplex *A, int lda,
                                        cuComplex *B, int ldb);
  void kblas_ztrmm(char side, char uplo, char trans, char diag,
                  int m, int n,
                  cuDoubleComplex alpha, const cuDoubleComplex *A, int lda,
                                              cuDoubleComplex *B, int ldb);
//}*/
void kblasStrsm(char side, char uplo, char trans, char diag,
                int m, int n,
                float alpha, const float *A, int lda,
                                   float *B, int ldb);
void kblasDtrsm(char side, char uplo, char trans, char diag,
                int m, int n,
                double alpha, const double *A, int lda,
                                    double *B, int ldb);
void kblasCtrsm(char side, char uplo, char trans, char diag,
                int m, int n,
                cuComplex alpha, const cuComplex *A, int lda,
                                       cuComplex *B, int ldb);
void kblasZtrsm(char side, char uplo, char trans, char diag,
                int m, int n,
                cuDoubleComplex alpha, const cuDoubleComplex *A, int lda,
                                             cuDoubleComplex *B, int ldb);


//Asynchronous version, takes streamID as parameter
void kblasStrmm_async(char side, char uplo, char trans, char diag,
                      int m, int n,
                      float alpha, const float *A, int lda,
                                         float *B, int ldb,
                      cudaStream_t stream);
void kblasDtrmm_async(char side, char uplo, char trans, char diag,
                      int m, int n,
                      double alpha, const double *A, int lda,
                                          double *B, int ldb,
                      cudaStream_t stream);
void kblasCtrmm_async(char side, char uplo, char trans, char diag,
                      int m, int n,
                      cuComplex alpha, const cuComplex *A, int lda,
                                             cuComplex *B, int ldb,
                      cudaStream_t stream);
void kblasZtrmm_async(char side, char uplo, char trans, char diag,
                      int m, int n,
                      cuDoubleComplex alpha, const cuDoubleComplex *A, int lda,
                                                   cuDoubleComplex *B, int ldb,
                      cudaStream_t stream);

void kblasStrsm_async(char side, char uplo, char trans, char diag,
                      int m, int n,
                      float alpha, const float *A, int lda,
                                         float *B, int ldb,
                      cudaStream_t stream);
void kblasDtrsm_async(char side, char uplo, char trans, char diag,
                      int m, int n,
                      double alpha, const double *A, int lda,
                                          double *B, int ldb,
                      cudaStream_t stream);
void kblasCtrsm_async(char side, char uplo, char trans, char diag,
                      int m, int n,
                      cuComplex alpha, const cuComplex *A, int lda,
                                             cuComplex *B, int ldb,
                      cudaStream_t stream);
void kblasZtrsm_async(char side, char uplo, char trans, char diag,
                      int m, int n,
                      cuDoubleComplex alpha, const cuDoubleComplex *A, int lda,
                                                   cuDoubleComplex *B, int ldb,
                      cudaStream_t stream);
#endif//CUBLAS_V2_H_


#ifdef __cplusplus
}
#endif

#endif // _KBLAS_H_