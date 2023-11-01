#include <stdio.h>

#define min(a, b) (a<b?a:b)

const int N = 3000;
const int threadsPerBlock = 1024;
const int blocksPerGrid = 1;// min(32, (N+threadsPerBlock-1)/threadsPerBlock);

// 若涉及线程频读写，将数据常驻shared memory，提高运行效率。同一block的thread可以共享该shared memory
// cuda中使用__shared__关键字，这里使用__syncthreads()控制线程同步。多个thread对shared memory访问，需要对线程进行同步操作，避免竞争

__global__ void dot(float* a, float* b, float* c){
    // 分配shared memory
	__shared__ float cache[threadsPerBlock];
	int tid = threadIdx.x + blockIdx.x * blockDim.x;
	int cacheIndex = threadIdx.x;

    // 
	float temp = 0;
	while(tid < N){
		temp += a[tid] + b[tid];
		tid += blockDim.x * gridDim.x;
	}

	cache[cacheIndex] = temp;

	//对线程块中的线程进行同步
	__syncthreads();

	int i = blockDim.x/2;

	while(i != 0){
		if(cacheIndex < i){
			cache[cacheIndex] += cache[cacheIndex + i];
		}
		__syncthreads();
		i /= 2;
	}

	if (cacheIndex == 0){
		c[blockIdx.x] = cache[0];
		//printf("%f\n", c[blockIdx.x]);
	}
}

int main(){

	float *a, *b, c, *partial_c;
	float *dev_a, *dev_b, *dev_partial_c;

	//在CPU上面分配内存
	a = (float*)malloc(N*sizeof(float));
	b = (float*)malloc(N*sizeof(float));
	partial_c = (float*)malloc(blocksPerGrid*sizeof(float));

	//在GPU上分配内存
	cudaMalloc((void**)&dev_a, N*sizeof(float));
	cudaMalloc((void**)&dev_b, N*sizeof(float));
	cudaMalloc((void**)&dev_partial_c, blocksPerGrid*sizeof(float));

	//填充主机内存
	for(int i = 0; i < N; i++){
		a[i] = 1;
		b[i] = 0;
	}

	//将 数组a 和 数组b 复制到GPU
	cudaMemcpy(dev_a, a, N*sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, b, N*sizeof(float), cudaMemcpyHostToDevice);

	dot<<<blocksPerGrid, threadsPerBlock>>>(dev_a, dev_b, dev_partial_c);

	//将数组 dev_partial_c 从 GPU 复制到 CPU
	cudaMemcpy(partial_c, dev_partial_c, blocksPerGrid * sizeof(float), cudaMemcpyDeviceToHost);

	//在CPU上完成最终的求和运算
	c = 0.0;
	for(int i = 0; i < blocksPerGrid; i++){
		c += partial_c[i];
	}

	printf("%s\n", "======================================");
	// for(int i = 0; i < N; i++){
	// 	printf("%f  %f \n", a[i], b[i]);
	// }

	printf("c = %f \n", c);
	printf("blocksPerGrid %d \n", blocksPerGrid);

	// 释放 GPU 上的内存
	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_partial_c);

	// 释放 CPU 上的内存
	free(a);
	free(b);
	free(partial_c);

	return 0;
}
