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