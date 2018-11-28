./rocblas-bench -f gemm -r s --transposeA T --transposeB N -m 1024 -n 2048 -k 49 --alpha 1 --lda 49 --ldb 49 --beta 1 --ldc 1024 >> gemm.txt
./rocblas-bench -f gemm -r s --transposeA T --transposeB N -m 1024 -n 256 -k 196 --alpha 1 --lda 196 --ldb 196 --beta 1 --ldc 1024 >> gemm.txt
./rocblas-bench -f gemm -r s --transposeA T --transposeB N -m 1024 -n 512 -k 49 --alpha 1 --lda 49 --ldb 49 --beta 1 --ldc 1024 >> gemm.txt
./rocblas-bench -f gemm -r s --transposeA T --transposeB N -m 1152 -n 128 -k 784 --alpha 1 --lda 784 --ldb 784 --beta 1 --ldc 1152 >> gemm.txt
./rocblas-bench -f gemm -r s --transposeA T --transposeB N -m 128 -n 512 -k 784 --alpha 1 --lda 784 --ldb 784 --beta 1 --ldc 128 >> gemm.txt
./rocblas-bench -f gemm -r s --transposeA T --transposeB N -m 147 -n 64 -k 12544 --alpha 1 --lda 12544 --ldb 12544 --beta 1 --ldc 147 >> gemm.txt
./rocblas-bench -f gemm -r s --transposeA T --transposeB N -m 2048 -n 512 -k 49 --alpha 1 --lda 49 --ldb 49 --beta 1 --ldc 2048 >> gemm.txt
./rocblas-bench -f gemm -r s --transposeA T --transposeB N -m 2304 -n 256 -k 196 --alpha 1 --lda 196 --ldb 196 --beta 1 --ldc 2304 >> gemm.txt
./rocblas-bench -f gemm -r s --transposeA T --transposeB N -m 256 -n 1024 -k 196 --alpha 1 --lda 196 --ldb 196 --beta 1 --ldc 256 >> gemm.txt
./rocblas-bench -f gemm -r s --transposeA T --transposeB N -m 256 -n 128 -k 784 --alpha 1 --lda 784 --ldb 784 --beta 1 --ldc 256 >> gemm.txt
./rocblas-bench -f gemm -r s --transposeA T --transposeB N -m 256 -n 512 -k 784 --alpha 1 --lda 784 --ldb 784 --beta 1 --ldc 256 >> gemm.txt
./rocblas-bench -f gemm -r s --transposeA T --transposeB N -m 256 -n 64 -k 3025 --alpha 1 --lda 3025 --ldb 3025 --beta 1 --ldc 256 >> gemm.txt
./rocblas-bench -f gemm -r s --transposeA T --transposeB N -m 256 -n 64 -k 3136 --alpha 1 --lda 3136 --ldb 3136 --beta 1 --ldc 256 >> gemm.txt
./rocblas-bench -f gemm -r s --transposeA T --transposeB N -m 4608 -n 512 -k 49 --alpha 1 --lda 49 --ldb 49 --beta 1 --ldc 4608 >> gemm.txt
./rocblas-bench -f gemm -r s --transposeA T --transposeB N -m 512 -n 1024 -k 196 --alpha 1 --lda 196 --ldb 196 --beta 1 --ldc 512 >> gemm.txt
./rocblas-bench -f gemm -r s --transposeA T --transposeB N -m 512 -n 128 -k 784 --alpha 1 --lda 784 --ldb 784 --beta 1 --ldc 512 >> gemm.txt
./rocblas-bench -f gemm -r s --transposeA T --transposeB N -m 512 -n 2048 -k 49 --alpha 1 --lda 49 --ldb 49 --beta 1 --ldc 512 >> gemm.txt
./rocblas-bench -f gemm -r s --transposeA T --transposeB N -m 512 -n 256 -k 196 --alpha 1 --lda 196 --ldb 196 --beta 1 --ldc 512 >> gemm.txt
./rocblas-bench -f gemm -r s --transposeA T --transposeB N -m 576 -n 64 -k 3025 --alpha 1 --lda 3025 --ldb 3025 --beta 1 --ldc 576 >> gemm.txt
./rocblas-bench -f gemm -r s --transposeA T --transposeB N -m 576 -n 64 -k 3136 --alpha 1 --lda 3136 --ldb 3136 --beta 1 --ldc 576 >> gemm.txt
./rocblas-bench -f gemm -r s --transposeA T --transposeB N -m 64 -n 256 -k 3025 --alpha 1 --lda 3025 --ldb 3025 --beta 1 --ldc 64 >> gemm.txt
./rocblas-bench -f gemm -r s --transposeA T --transposeB N -m 64 -n 256 -k 3136 --alpha 1 --lda 3136 --ldb 3136 --beta 1 --ldc 64 >> gemm.txt
./rocblas-bench -f gemm -r s --transposeA T --transposeB N -m 64 -n 64 -k 3025 --alpha 1 --lda 3025 --ldb 3025 --beta 1 --ldc 64 >> gemm.txt
./rocblas-bench -f gemm -r s --transposeA T --transposeB N -m 64 -n 64 -k 3136 --alpha 1 --lda 3136 --ldb 3136 --beta 1 --ldc 64 >> gemm.txt
