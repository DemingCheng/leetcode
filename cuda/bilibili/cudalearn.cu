#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda_runtime.h>
#include <time.h>

#define TILE_WIDTH 16

__global__ void MatrixMul(float* M_d, float* N_d, float* P_d, const int WIDTH) {   // Q:为什么这里是一维指针，而cudaMalloc里是二维指针 cudaError_t cudaMalloc(void** devPtr, size_t size); 在设备上分配size字节的线性内存，并返回分配内存的指针*devPtr。
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    for(int k = 0; k < WIDTH; k++) {
        P_d[row * WIDTH + col] += M_d[row * WIDTH + k] * N_d[k * WIDTH + col]; 
    }
}

int main() {
    const int WIDTH = 512;
    // 定义CPU矩阵
    float M_h[WIDTH][WIDTH], N_h[WIDTH][WIDTH], P_h[WIDTH][WIDTH];
    // 定义GPU矩阵
    float* M_d, *N_d, *P_d;
    // 初始化host上的矩阵
    for(int i = 0; i < WIDTH; i++) {
        for(int j = 0; j < WIDTH; j++) {
            M_h[i][j] = 1;
            N_h[i][j] = 2;
        }
    }
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    float elaspedTime;

    // 在GPU上分配空间
    int size = WIDTH*WIDTH*sizeof(int);
    cudaMalloc((void**)&M_d, size);
    cudaMalloc((void**)&N_d, size);
    cudaMalloc((void**)&P_d, size); 

    // 将CPU上的数据传输到GPU的显存中 Q:显存？
    cudaMemcpy(M_d, M_h, size, cudaMemcpyHostToDevice);
    cudaMemcpy(N_d, N_h, size, cudaMemcpyHostToDevice);

    // 设置kernel的执行设置
    dim3 dimBlock(TILE_WIDTH, TILE_WIDTH, 1);
    dim3 dimGrid(WIDTH/TILE_WIDTH, WIDTH/TILE_WIDTH, 1);

    // 执行kernel函数
    MatrixMul<<<dimGrid, dimBlock>>>(M_d, N_d, P_d, WIDTH);

    // 释放device上空间
    cudaFree(M_d);
    cudaFree(N_d);
    cudaFree(P_d);
    return 0;
}