   
template <typename T>
    void syrkx_batched_solution(rocblas_operation trans_a,
                               rocblas_operation trans_b,
                               rocblas_int       m,
                               rocblas_int       n,
                               rocblas_int       k,
                               T                 alpha,
                               T*                dA_array,
                               rocblas_int       lda,
                               rocblas_stride    stride_a,
                               T*                dB_array,
                               rocblas_int       ldb,
                               rocblas_stride    stride_b,
                               T                 beta,
                               T*                dC_array,
                               rocblas_int       ldc,
                               rocblas_stride    stride_c,
                               rocblas_int       batch_count,
                               hipStream_t       stream);
