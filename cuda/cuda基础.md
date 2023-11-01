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




Warp divergence & Bank conflict
1、warp、bank概念
        warp是并行计算时最小的并发结构，通常由连续32个thread组成。bank是对SM中共享内存的划分，划分个数与对应硬件warp中所含thread数一致。对应使用的计算能力3.x版本的显卡，一个warp含有32个thread，因此划分的bank数也为32，并且每个bank的宽度大小为4bytes，对应于一个int型或float型变量。

2、warp divergence
        对于同一个warp中的所有thread是完全并行的，且必须要执行相同的指令，当同一warp中的thread分配了不同的指令时，会发生warp divergence，增加了程序的运行时间。为了有效地解决上述divergence问题，在分配任务时，尽量的使用索引号连续的thread，使活跃的thread全部集中到某些warp中，避免同一warp中同时存在活跃和不活跃两种状态的thread。

3、bank conflict
        一个SM中，共享内存会被分成多个bank，共享内存中以每4*32bytes为单位，顺序的存储在bank0~bank31中，当两个不同的thread同时访问同一bank内的值时，会发生bank conflict，也会增加程序运行的时间。这通常会发生在同一warp中，因为只有同一warp中的thread才是完全的同时执行。有效解决bank conflict的方法：遇到具体问题需要具体的实现实施方案，所要解决的根本问题是同一warp内的thread不要同时访问相同的bank。以归约算法计算向量和为例，每个活跃的thread中所执行的任务都是对两个数进行相加，这就需要确保每个thread中的两个数都和其余thread中的数不在同一个bank中，具体做法为设置相加的两个数之间的offect为32的倍数，使同一warp中每个thread访问的两个值在同一bank中，且不同thread访问的值不在同一bank中，即可有效避免bank conflict。
