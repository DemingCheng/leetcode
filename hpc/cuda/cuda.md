CUDA 笔记
https://zhuanlan.zhihu.com/p/454319729

# 01

## 一个CUDA的程序主要流程如下：

1、分配GPU内存。
2、将数据从CPU复制到GPU中。
3、调用CUDA核执行相关数据。
4、将结果从GPU复制到CPU中。
5、释放GPU内存。

```CPP
#include <iostream>

__global__ void fun() {
    printf("hello world from GPU\n");
}

int main() {
    printf("hello world from CPU\n");

    // fun<<< m,n >>>()：代表一个kernel被调用的固定格式。m,n分别代表块和线程数。后续文章会进行介绍。
    fun<<<2, 3>>>();
    cudaDeviceSynchronize();
}
```

## 1. __global__

__global__:声明一个函数作为kernel
1、在设备上执行
2、仅在主机上调用

## 2. cudaDeviceSynchronize

使CPU进程等待GPU上的进程执行完毕。
注：在host code中执行device code，CPU会在执行一个kernel后，立刻执行后续操作，相当于形成两个分支，而不会等待GPU上的进程是否完成。

## 3. fun<<< m,n >>>()

代表一个kernel被调用的固定格式。m,n分别代表块和线程数。

# 02

## kernel 函数

kernel是CUDA程序的重要组件，表示在GPU设备中运行的代码（它是程序，是代码，不是代表芯片上的物理核心！）。
当一个kernel启动后，控制权会立刻返回至host上，即当程序执行到一个kernel代码后，主程序会继续向下执行，与kernel函数此时是否执行完毕无关。

一个kernel --> 一个grid --> 多个block --> 多个thread；
一个kernel ----> 一个grid ----> 多个处理器并行执行多个块 ----> 一个处理器执行一个块 ----> 并行执行一个块内的多个线程。

并发线程数量=并发块数x每块的线程数。

块的执行次序是未知的，如果是读取操作可同步执行，如果对共享内存空间的同一位置进行写入，则是按按时间随机执行。

不同block中的thread不能通信（不能越级！！）。

dim3 grid(**3, **2**)**;
dim3 block(**5, **3**)**;

![CUDA](../images/cuda/kernel.png "kernel对应grid")

每个线程由线程ID定位（给thread上户口），以下两者都是dim3类型：

1、blockIdx（所在块在grid中的id）:blockIdx.x, blockIdx.y, blockIdx.z，

2、threadIdx（线程在块中的id）:threadIdx.x, threadIdx.y, threadIdx.z

计算方式：ID = x+yDx+zDxDy

根据不同坐标将不同数据分给不同线程处理。

block和thread共有三个维度（x,y,z）。当你在初始创建时,未使用的字段初始化为1。

gridDim（gridDim.x, gridDimg.y, gridDim.z）：对应一个grid中有多少个block----->对应于blockIdx的上界。

blockDim（blockDim.x, blockDim.y, blockDim.z）:对应一个block中有多少个thread----->对应于threadIdx的上界。

* blockDim（block尺寸，以thread为单位）

  * blockDim.x, blockDim.y, blockDim.z
* gridDim（grid尺寸，以block为单位）

# 内存管理

CUDA编程模型将GPU的内存架构抽象为两个主要的层次：
1、global memory：类似CPU的系统内存
2、shared memory：类似CPU的缓存
![CUDA](../images/cuda/cuda_memory.png "cuda memory")

| CPU    | GPU        |
| ------ | ---------- |
| malloc | cudaMalloc |
| free   | cudaFree   |
| memcpy | cudaMemcpy |
| memset | cudaMemset |

![CUDA](../images/cuda/cuda_function.png "cuda function")
cudaMemcpy函数会引起CPU程序阻塞，即只有当这个操作完成后，CPU才可以执行后续代码。
