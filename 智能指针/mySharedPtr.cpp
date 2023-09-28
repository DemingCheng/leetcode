
#include <iostream>
#include <atomic>
namespace sptr{
    // 默认删除器
    template<typename T>
    class default_deleter{
        public:
            void operator[](T *ptr_){
                delete ptr_;
            }
    };
    template<typename T, typename deleter = default_deleter<T>>
    class shared_ptr{
        public:
            // 默认构造
            shared_ptr() = default;
            // 裸指针构造
            shared_ptr(T* ptr_);
            // 拷贝构造
            shared_ptr(const shared_ptr& sptr);
            // 拷贝赋值运算符
            // 移动构造
            // 移动赋值运算符
            // 析构函数

            // get 获取指针
            // use_count
            // reset
            // unique是不是一个在用

        private:
            T *ptr = nullptr;
            // 计数器、内存块对每个shared——ptr共享，存了强引用版本弱引用版本
            // 用指针，在拷贝时可以在同一个内存地址上更新，原子操作
            std::atomic<int>* count = nullptr;
    }


}