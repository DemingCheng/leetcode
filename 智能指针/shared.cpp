#include <iostream>
#include <memory>

void foo(std::shared_ptr<int> i) {
    (*i)++;
}

int main() {
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