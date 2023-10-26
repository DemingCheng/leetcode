费米

包含512个cuda core，分为16个SM，每个SM包含32个cuda core，每个cuda core包含alu（算数运算单元）和fpu（浮点运算单元）。

整个GPU是包含4个GPC（图像处理集群），每个GPC包含4个SM，还有warp scheduler，

[!image](https://pic2.zhimg.com/80/v2-5aaf90a4f9cb41af90833a978d735c89_720w.webp)

* 橙色部分：2 个 Warp Scheduler/Dispatch Unit
* 绿色部分：32 个 CUDA 内核，分在两条 lane 上，每条分别是 16 个
* 浅蓝色部分：register file-寄存器文件和 L1 cache
* 16 个 Load/Store units (LD/ST Unit)
* 4 个 Special Function Units (SFU)



GPU内存分为片上内存和板载内存

板载内存：慢 全局内存

片上内存：快 共享内存，L1 cache


shared memroy的bank conflict


线程层次

Thread

int i = blockIdx.x * blockDim.x + threadIdx.x

int j = blockIdx
