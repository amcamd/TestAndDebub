#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <math.h>
#include "rocblas.h"
#include <hip/hip_runtime.h>
#include <complex>

using namespace std;

int main()
{
    rocblas_int N = 10240;
    float alpha = 10.0;
    const complex<float> c_alpha = {1.0, 0.0};

    vector<float> hx(N);
    vector<float> hz(N);
    vector<complex<float>> c_hx(N);
    complex<float>* c_dx;
    float* dx;
    float tolerance = 0, error;

    rocblas_handle handle;
    rocblas_create_handle(&handle);

    // allocate memory on device
    hipMalloc(&dx, N * sizeof(float));
    hipMalloc(&c_dx, N * sizeof(complex<float>));

    // Initial Data on CPU,
    srand(1);
    for( int i = 0; i < N; ++i )
    {
        hx[i] = rand() % 10 + 1;  //generate a integer number between [1, 10]
        c_hx[i] = {static_cast<float>(rand() % 10 + 1), static_cast<float>(rand() % 10 + 1)};
    }

    // save a copy in hz 
    hz = hx;

    hipMemcpy(dx, hx.data(), sizeof(float) * N, hipMemcpyHostToDevice);
    hipMemcpy(c_dx, c_hx.data(), sizeof(complex<float>) * N, hipMemcpyHostToDevice);

    rocblas_sscal(handle, N, &alpha, dx, 1);
    rocblas_cscal(handle, N, (rocblas_float_complex*) &c_alpha, (rocblas_float_complex*) c_dx, 1);

    // copy output from device memory to host memory
    hipMemcpy(hx.data(), dx, sizeof(float) * N, hipMemcpyDeviceToHost);

    // verify rocblas_scal result
    for(rocblas_int i=0;i<N;i++)
    {
        error = fabs(hz[i] * alpha - hx[i]);
        if(error > tolerance)
        {
          printf("error in element %d: CPU=%f, GPU=%f ", i, hz[i] * alpha, hx[i]);
          break;
        }
    }

    if(error > tolerance)
    {
        printf("SCAL Failed !\n");
    }
    else
    {
        printf("SCAL Success !\n");
    }

    hipFree(dx);
    rocblas_destroy_handle(handle);
    return 0;
}
