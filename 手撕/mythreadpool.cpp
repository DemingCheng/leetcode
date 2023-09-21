#include <iostream>           // 标准输入输出
#include <functional>         // 函数对象
#include <condition_variable> // 条件变量 用于线程同步
#include <mutex>              // 互斥锁
#include <thread>             // 线程
#include <queue>              // 队列容器
#include <vector>             // 向量容器

class myThreadPool {
public:
    // 构造函数
    myThreadPool(int num_threads) {
        for(int i = 0; i < num_threads; i++) {
            addThread();
        }
    }

    // 析构函数, 销毁线程池
    // 设置stop标志位为真，并
    ~myThreadPool() {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            stop_ = true;
        }
        
    }

    // 拷贝构造函数

    // 移动构造函数

    // 赋值运算符

private:
    vector<thread> pool_;            // 线程池
    queue<function<void()>> task_;   // 任务队列
    mutex mutex_;                    // 互斥锁
    condition_variable cv_;          // 条件变量
    bool stop_ = false;              // 停止标志位


};

int main() {


    return 0;
}


