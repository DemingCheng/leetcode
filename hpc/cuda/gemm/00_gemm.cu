// https://zhuanlan.zhihu.com/p/98654665
#include <stdlib.h>
#include <stdio.h>

#define N 1024
#define thread_per_block 256
#define block_num 32

// const int N =1024;


__global__ void gemm_0(float* d_A, float* d_B, float* d_C, int n) {
    int row = threadIdx.y + blockIdx.y * blockDim.y;
    int col = threadIdx.x + blockIdx.x * blockDim.x;

    float sum = 0.0;

    for(int k = 0; k < n; k++) {
        sum += d_A[row * n + k] * d_B[k * n + col];
    }

    d_C[row * n + col] = sum;
    printf(d_C[row * n + col]);
}

// __global__ void gemm_0(float* d_A, float* d_B, float* d_C, int N) {
// }

void prinfMatrix(float* mat, int row, int col) {
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            printf("%lf ", mat[i * row + j]);
        }
        printf("/n");
    }
}

int main() {
    float *h_A, *h_B, *h_C;
    float *d_A, *d_B, *d_C;

    h_A = (float*)malloc(N * N * sizeof(float));
    h_B = (float*)malloc(N * N * sizeof(float));
    h_C = (float*)malloc(N * N * sizeof(float));

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            h_A[i * N + j] = 1;
            h_B[i * N + j] = 2;
        }
    }

    cudaMalloc((void**)&d_A, N * N * sizeof(float));
    cudaMalloc((void**)&d_B, N * N * sizeof(float));
    cudaMalloc((void**)&d_C, N * N * sizeof(float));

    cudaMemcpy(d_A, h_A, N * N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, N * N * sizeof(float), cudaMemcpyHostToDevice);

    dim3 block(thread_per_block, 1);
    dim3 grid(block_num, 1);

    gemm_0<<<grid, block>>>(d_A, d_B, d_C, N);

    cudaMemcpy(h_C, d_C, N * N * sizeof(float), cudaMemcpyDeviceToHost);
    // prinfMatrix(h_C, N, N);


    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}