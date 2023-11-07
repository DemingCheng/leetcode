#include <cuda_runtime.h>
#include <stdio.h>
#include "cuda_start.h"

// CPU 对照组，对比加速比
void sumMatrix2DonCPU(float* MatA, float* MatB, float* MatC, int nx, int ny) {
    float* a = MatA;
    float* b = MatB;
    float* c = MatC;


}   

__global__ void sumMatrix(float* MatA, float* MatB, float* MatC, int nx, int ny) {

}

int main() {
    //设备初始化
    printf("strating...\n");
    initDevice(0);

    // 二维矩阵大小 4096*4096 单精度浮点型
    int nx = 1<<12; // 4096 2^12 位运算-移位
    int ny = 1<<12; // 4096 
    int nBytes = nx * ny * sizeof(float);

    // Malloc 开辟主机内存
    float* A_host = (float*)malloc(nBytes);
    float* B_host = (float*)malloc(nBytes);
    float* C_host = (float*)malloc(nBytes);  
    float* C_from_gpu = (float*)malloc(nBytes);
    initialData(A_host, nx*ny);
    initialData(B_host, nx*ny);

    // cudaMalloc 开辟device内存
    float* A_dev = NULL;
    float* B_dev = NULL;
    float* C_dev = NULL;  
    CHECK(cudaMalloc((void**)&A_dev), nBytes);
    CHECK(cudaMalloc((void**)&B_dev), nBytes);
    CHECK(cudaMalloc((void**)&C_dev), nBytes);

    // 输入数据从host内存拷贝到device内存
    CHECK(cudaMemcpy(A_dev, A_host, nBytes, cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(A_dev, A_host, nBytes, cudaMemcpyHostToDevice));

    // 二维线程块 32*32
    dim3 block(32, 32);
    // 二维线程网络 128*128
    dim3 grid((nx - 1) / block.x + 1, (ny - 1) / block.y + 1);



}