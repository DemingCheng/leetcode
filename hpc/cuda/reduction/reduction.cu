#include <stdio.h>

const int N = 32*1024*1024;           // 输入矩阵的大小input size 32M的global memory
const int thread_per_block = 256;    // 每个block的thread数  2^8个
const int block_num = N / thread_per_block;                  

// __global__ void reduce3(float* d_in, float* d_out) {
//     __shared__ float cache[block_num];
//     unsigned int tid = threadIdx.x;
//     unsigned int i = threadIdx.x + blockIdx.x * (blockDim.x * 2);

//     cache[tid] = d_in[] + ; 


// }

// warp是并行计算时最小的并发结构，通常由连续32个thread组成。
// 同一个warp中的所有thread是完全并行的，且必须要执行相同的指令，当同一warp中的thread分配了不同的指令时，会发生warp divergence
// 若一个warp（32个线程）里不同线程因为分支条件执行了不同指令，效率会极低。同时 % 取余运算的效率也很低

// 没写错，这里临时变量就是为了找起始下标，线程是连着编号的，但是每个线程操作的元素第一个下标需要计算
// 图没错，每个S的取值代表纵轴一个step。 每个tid的取值代表横轴的一个thread
__global__ void reduce1(float* d_in, float* d_out) {

    __shared__ float cache[thread_per_block];

    unsigned int tid = threadIdx.x;
    unsigned int i = threadIdx.x + blockDim.x * blockIdx.x;
    cache[tid] = d_in[i];
    __syncthreads();
    
    for(unsigned int s = 1; s < blockDim.x; s *= 2) {
        int index = 2 * s * tid;
        if(index < blockDim.x) {
            cache[index] += cache[index + s];
        }
        __syncthreads();
    }

    if(tid ==0) {
        d_out[blockIdx.x] = cache[tid];
    }
}

__global__ void reduce1_1(float* d_in, float* d_out) {
    __shared__ float cache[thread_per_block];

    unsigned int tid = threadIdx.x;
    unsigned int i = threadIdx.x + blockDim.x * blockIdx.x;
    cache[tid] = d_in[i];
    __syncthreads();
    
    for(unsigned int stride = blockDim.x / 2; stride > 0; stride >>= 1) {
        if(tid < stride) {
            cache[tid] += cache[tid + stride];
        }
        __syncthreads();
    }

    if(tid ==0) {
        d_out[blockIdx.x] = cache[tid];
    }
}

// 最基础reduction
__global__ void reduce_0(float* d_in, float* d_out) {
    // 分配shared memory ，将数据global load到shared memory
    __shared__ float sdata[thread_per_block];

    unsigned int i = threadIdx.x + blockIdx.x * blockDim.x;
    unsigned int tid = threadIdx.x;  // 块内index

    // each thread load one element form global to shared mem
    sdata[tid] = d_in[i];
    __syncthreads();

    // do reduction in each block
    for(unsigned int stride = 1; stride < blockDim.x; stride *= 2) { // or stride < thread_per_block
        if(tid % (2 * stride) == 0) {
            sdata[tid] += sdata[tid + stride];
        }
        __syncthreads();
    }

    if(tid == 0) {
        d_out[blockIdx.x] = sdata[tid]; 
    }
}

__global__ void reduce0(float* d_in,float* d_out){
    __shared__ float sdata[thread_per_block];

    //each thread loads one element from global memory to shared mem
    unsigned int i=blockIdx.x*blockDim.x+threadIdx.x;
    unsigned int tid=threadIdx.x;
    sdata[tid]=d_in[i];
    __syncthreads();

    // do reduction in shared mem
    for(unsigned int s=1; s<blockDim.x; s*=2){
        if(tid%(2*s) == 0){
            sdata[tid]+=sdata[tid+s];
        }
        __syncthreads();
    }
    
    // write result for this block to global mem
    if(tid==0) {
        d_out[blockIdx.x]=sdata[tid];
        printf("blockIdx.x: %lf", d_out[blockIdx.x]);
    }
}

bool check(float* res_h, float* ans) {
    for(int i = 0; i < block_num; i++) {
        if(res_h[i] != ans[i]) {
            printf("Wrong Answer\n");
            return false;
        }
    }
    printf("Right Answer\n");
    return true;
}

int main() {
    float *h_in, *h_out;
    float *d_in, *d_out;
    // cpu上分配内存
    h_in = (float*)malloc(N * sizeof(float));
    h_out = (float*)malloc(block_num * sizeof(float)); // 这里是只算第一级block输出的，不算第二级的了
    for(int i = 0; i < N; i++) {
        h_in[i] = 1;
    }

    // gpu上分配内存
    cudaMalloc((void**)&d_in, N * sizeof(float));
    cudaMalloc((void**)&d_out, block_num * sizeof(float));

    // 拷贝数据从cpu到gpu
    cudaMemcpy(d_in, h_in, N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_out, h_out, N * sizeof(float), cudaMemcpyHostToDevice);


    dim3 Grid(block_num, 1);           // 一个grid里多少个block
    dim3 Block(thread_per_block, 1);   // 一个block里多少个thread
    // reduce0<<<Grid, Block>>>(d_in, d_out);
    reduce0<<<Grid, Block>>>(d_in, d_out);

    cudaError_t err = cudaGetLastError();
    if(err != cudaSuccess) {
        printf("Failed: Cuda error %s:%d '%s'\n", __FILE__,__LINE__,cudaGetErrorString(err));
    }
    

    cudaMemcpy(h_out, d_out, block_num * sizeof(float), cudaMemcpyDeviceToHost);

    float* ans = (float*)malloc(block_num * sizeof(float));
    for(int i = 0; i < block_num; i++) {
        float curr = 0;
        for(int j = 0; j < thread_per_block; j++) {
            curr += h_in[i * thread_per_block + j];
        }
        ans[i] = curr;
    }

    // if(check(h_out, ans) == false) {
    //     for(int i = 0; i < 1024; i++) {
    //         if(h_out[i] != ans[i]) {
    //             printf("%d, %lf\n", i, h_out[i]);
    //         }
    //         // printf("%lf", h_out[i]);
    //     }
    //     printf("\n");
    // }
    
    printf("check(h_out, ans): %s\n", check(h_out, ans) ? "true": "false");
    printf("block_num: %d\n", block_num);

    cudaFree(d_in);
    cudaFree(d_out);
    free(h_in);
    free(h_out);

    return 0;


}
