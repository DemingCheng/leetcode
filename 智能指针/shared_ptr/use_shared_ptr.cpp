#include <iostream>
#include <memory>
// https://zhuanlan.zhihu.com/p/526147194

void foo(std::shared_ptr<int> i) {
    (*i)++;
}

int main() {
    // 初始化方法
    // 1. 传参构造
    std::shared_ptr<int> p1(new int(1));   
    // 2. 拷贝构造
    std::shared_ptr<int> p2 = p1;
    // 3. 通过reset传入指针参数，来替换掉智能指针对象管理的指针。
    std::shared_ptr<int> p3;
    p3.reset(new int(1));
    // 4. make_shared方法
    std::shared_ptr<int> p4 = std::make_shared<int> (3);

    if(p3 == nullptr) {
        std::cout << "p3 is nullptr" << std::endl;
    }
    else {
        std::cout << "p3 is not nullptr" << std::endl;
    }
    
    // 通过get方法获取原始指针
    std::shared_ptr<int> p5 = std::make_shared<int> (3);
    int* rawp5 = p5.get();
    std::cout << "通过get方法获取原始指针*" << rawp5 << std::endl;

    // 指定删除器
    void deleteIntPoint(int* ptr) {
        delete ptr;
        ptr = nullptr;
    }
    std::shared_ptr<int> p6(new int, deleteIntPoint);
    // https://www.cnblogs.com/fortunely/p/15815741.html#:~:text=%E6%8C%87%E5%AE%9A%E5%88%A0%E9%99%A4%E5%99%A8%E6%99%BA%E8%83%BD%E6%8C%87%E9%92%88,%E6%8C%87%E5%AE%9A%E8%87%AA%E5%AE%9A%E4%B9%89%E5%88%A0%E9%99%A4%E5%99%A8%E3%80%82&text=%E5%BD%93p%E7%9A%84%E5%BC%95%E7%94%A8%E8%AE%A1%E6%95%B0,%E7%94%9A%E8%87%B3%E4%BB%BB%E6%84%8F%E5%8F%AF%E8%B0%83%E7%94%A8%E5%AF%B9%E8%B1%A1%E3%80%82

    std::shared_ptr<int> sptr = std::make_shared<int>(10);
    foo(sptr);
    printf("%d\n", *sptr);

    // 可以通过赋值运算符
    std::shared_ptr<int> ptr1 = std::make_shared<int>(1);
    auto ptr2 = ptr1; // 引用计数+1
    auto ptr3 = ptr1; // 引用计数+1
    std::cout << ptr1.use_count() << std::endl; // 3

    return 0;
}