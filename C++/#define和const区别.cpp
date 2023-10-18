// #define和const的区别
// 1. 宏是在预处理语句，在预处理阶段就进行了替换，const在编译和运行时起作用。
// 2. 宏没有类型检查,只是简单替换

// 3. 宏占用更多内存空间
// 4. 宏不能编译

// 看后面两位是什么
// 数组指针 函数指针 常量指针
// 指针数组 指针函数 指针常量
#include <iostream>
using namespace std;
int main() {
    int a = 10;
    int tmp = 20;
    // 常量指针，指向的内容不能变(指针所指空间的值) 下面两种效果一样
    const int* p1 = &a;
    int const * p2 = &a;

    p1 = &tmp;
    // *p1 = 20; // error

    // 指针常量，指针的指向不能变
    int* const p3 = &a;
    *p3 = 20;
    // p3 = &tmp; // error


    cout << "那个在前面那个不能变" << endl;
    return 0;
}

