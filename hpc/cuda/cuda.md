CUDA 笔记
https://zhuanlan.zhihu.com/p/454319729

# 通识

NVIDIA目前的计算平台（不是架构）有，根据应用场景分类的几种平台。：

Tegra， Geforce， Quadro， Tesla
每个平太针对不同的应用场景，比如Tegra用于嵌入式，Geforce是我们平时打游戏用到，Tesla是我们昨天租的那台腾讯云的，主要用于计算。

衡量GPU计算能力的主要靠下面两种容量特征：CUDA核心数量（越多越好）， 内存大小（越大越好）
相应的也有计算能力的性能指标：峰值计算能力， 内存带宽
nvidia自己有一套描述GPU计算能力的代码，其名字就是“计算能力”，主要区分不同的架构，早其架构的计算能力不一定比新架构的计算能力强

延迟是指操作从开始到结束所需要的时间，一般用微秒计算，延迟越低越好。
带宽是单位时间内处理的数据量，一般用MB/s或者GB/s表示。
吞吐量是单位时间内成功处理的运算数量，一般用gflops来表示（十亿次浮点计算），吞吐量和延迟有一定关系，都是反应计算速度的，一个是时间除以运算次数，得到的是单位次数用的时间–延迟，一个是运算次数除以时间，得到的是单位时间执行次数–吞吐量。


计算能力	架构名
1.x	Tesla
2.x	Fermi
3.x	Kepler
4.x	Maxwell
5.x	Pascal
6.x	Volta

工具
Nvidia Nsight集成开发环境
CUDA-GDB 命令行调试器
性能分析可视化工具
CUDA-MEMCHECK工具
GPU设备管理工具

GPU 设备信息
https://face2ai.com/CUDA-F-2-4-%E8%AE%BE%E5%A4%87%E4%BF%A1%E6%81%AF/

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

# 理论界限最大化
如果我们使用完整的nvprof路径加上sudo执行
![CUDA](https://face2ai.com/CUDA-F-2-2-%E6%A0%B8%E5%87%BD%E6%95%B0%E8%AE%A1%E6%97%B6/nvprof_sudo.png "nvprof")
工具不仅给出了kernel执行的时间，比例，还有其他cuda函数的执行时间，可以看出核函数执行时间只有4%左右，其他内存分配，内存拷贝占了大部分事件，nvprof给出的核函数执行时间2.1011ms，上面cpuSecond计时结果是2.282ms
可见，nvprof可能更接近真实值。
nvprof这个强大的工具给了我们优化的目标，分析数据可以得出我们重点工作要集中在哪部分。

得到了实际操作值，我们需要知道的是我们能优化的极限值是多少，也就是机器的理论计算极限，这个极限我们永远也达不到，但是我们必须明确的知道，比如理论极限是2秒，我们已经从10秒优化到2.01秒了，基本就没有必要再继续花大量时间优化速度了，而应该考虑买更多的机器或者更新的设备。
各个设备的理论极限可以通过其芯片说明计算得到，比如说：

Tesla K10 单精度峰值浮点数计算次数：745MHz核心频率 x 2GPU/芯片 x（8个多处理器 x 192个浮点计算单元 x 32 核心/多处理器） x 2 OPS/周期 =4.58 TFLOPS
Tesla K10 内存带宽峰值： 2GPU/芯片 x 256 位 x 2500 MHz内存时钟 x 2 DDR/8位/字节 = 320 GB/s
指令比：字节 4.58 TFLOPS/320 GB/s =13.6 个指令： 1个字节


# 错误处理

错误处理
所有编程都需要对错误进行处理，早起的编码错误，编译器会帮我们搞定，内存错误也能观察出来，但是有些逻辑错误很难发现，甚至到了上线运行时才会被发现，而且有些厉害的bug复现会很难，不总出现，但是很致命，而且CUDA基本都是异步执行的，当错误出现的时候，不一定是哪一条指令触发的，这一点非常头疼；这时候我们就需要对错误进行防御性处理了，例如我们代码库头文件里面的这个宏：

```cpp
#define CHECK(call)\
{\
  const cudaError_t error=call;\
  if(error!=cudaSuccess)\
  {\
      printf("ERROR: %s:%d,",__FILE__,__LINE__);\
      printf("code:%d,reason:%s\n",error,cudaGetErrorString(error));\
      exit(1);\
  }\
}
```

就是获得每个函数执行后的返回结果，然后对不成功的信息加以处理，CUDA C 的API每个调用都会返回一个错误代码，这个代码我们就可以好好利用了，当然在release版本中可以去除这部分，但是开发的时候一定要有的。
