// https://zhuanlan.zhihu.com/p/455652400
#include <cuda_runtime.h>
#include <stdio.h>

#include "learnCuda.h"

void sumArrayonHost(float* A, float* B, float* C, const int N) {
    for(int idx = 0; idx < N; idx++) {
        C[idx] = A[idx] + B[idx];
    }
}

// __global__ void printThreadIndex(int* A, const int nx, const int ny) {
//     //1、先定位线程坐标
//     int ix = threadIdx.x + blockIdx.x * blockDim.x;
//     int iy = threadIdx.y + blockIdx.y * blockDim.y;

//     //2、然后定位对应数据的内存坐标（因为内存是线性排列，所以是  x + y*nx
//     // thread Id, block Id, 矩阵元素的坐标, global memory的偏移量, 即内存线性空间的坐标, 元素值
//     unsigned int idx = iy * nx + ix;
//     printf("thread_id (%d, %d) block_id (%d, %d) coordinate (%d, %d) "
//            "global index %2d ival %2d\n", threadIdx.x, threadIdx.y, blockIdx.x, blockIdx.y, ix, iy, idx, A[idx]);
// }

int main(int arc, char** argv) {
    printf("%s Starting...\n", argv[0]);
    // set up device
    int dev = 0;
    cudaDeviceProp deviceProp;
    CHECK(cudaGetDeviceProperties(&deviceProp, dev));
    printf("Using Device %d: %s\n", dev, deviceProp.name);
    CHECK(cudaSetDevice(dev));

    // set matrix dimension
    int nx = 8;
    int ny = 6;
    int nxy = nx * ny;

    size_t nBytes = nxy * sizeof(float);

    // malloc host memory
    int* h_A = (int*)malloc(nBytes);
    initialInt(h_A, nxy);
    printMatrix(h_A, nx, ny);

    // malloc device memory
    int* d_A;
    cudaMalloc((void**)&d_A, nBytes);

    // transfer data from host to device
    cudaMemcpy(d_A, h_A, nBytes, cudaMemcpyHostToDevice);
    
    // set up execution configration
    dim3 block(4,2);
    dim3 grid((nx + block.x - 1) / block.x, (ny + block.y - 1) / block.y);

    // invoke the kernel
    printThreadIndex<<<grid, block>>>(d_A, nx, ny);
    cudaDeviceSynchronize();

    // free host and device memory
    cudaFree(d_A);
    free(h_A);
    cudaDeviceReset();
    return 0;
}