#include <iostream>

__global__ void fun() {
    int tid = threadIdx.x;
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    printf("hello world from GPU, tid: %d, i: %d\n", tid, i);
}

__global__ void checkIndex(void)
{
  printf("threadIdx:(%d,%d,%d) blockIdx:(%d,%d,%d) blockDim:(%d,%d,%d)\
  gridDim(%d,%d,%d)\n",threadIdx.x,threadIdx.y,threadIdx.z,
  blockIdx.x,blockIdx.y,blockIdx.z,blockDim.x,blockDim.y,blockDim.z,
  gridDim.x,gridDim.y,gridDim.z);
}

int main() {
    printf("hello world from CPU\n");

    // fun<<< m,n >>>()：代表一个kernel被调用的固定格式。m,n分别代表块和线程数。后续文章会进行介绍。
    // fun<<<2, 3>>>();

    int nElem=6;
    dim3 block(3);
    dim3 grid((nElem + block.x - 1) / block.x);
    printf("grid.x %d grid.y %d grid.z %d\n",grid.x,grid.y,grid.z);
    printf("block.x %d block.y %d block.z %d\n",block.x,block.y,block.z);
    checkIndex<<<grid,block>>>();   
    
    cudaDeviceSynchronize();
}

