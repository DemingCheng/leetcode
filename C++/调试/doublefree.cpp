#include <iostream>
#include <queue>
#include <cstring>
#include <memory>
using namespace std;

class Test1 {
public:
    Test1(){
        data = new int[10];
    }

    ~Test1(){
        cout << "~Test()" << data << endl;
        delete[] data;
    }

private:
    int* data;

};



class Test2 {
public:
    Test2() {
        data = new int[10];
    }

    ~Test2() {
        cout << "~Test()" << data << endl;
        delete[] data;
    }

    Test2(const Test2& other) {
        data = new int[10];
        memcpy(data, other.data, 10);
    }

    Test2 operator=(const Test2& other) {
        // 处理自赋值
        if(this == &other) {
            return *this;
        }
        int* tmp = new int[10];
        delete[] data;
        data = tmp;
        memcpy(data, other.data, 10);
        return *this;
    }

private:
    int* data;
};

class Test3 {
public:
    Test3() {
        shared_ptr<int> sptr(new int[10], default_delete<int[]>());
        data = sptr.get();
        cout << "data addr " << data << endl;
    }

// C++ shared_ptr使用动态数组（std::shared_ptr and std::weak_ptr with array support）
// // (1) C++ 17
// std::shared_ptr<int[]> p(new int[10]);

// // (2) or lambda expression 
// std::shared_ptr<int> sp(new int[10], [](int *p) { delete[] p; });

// // (3) or use default_delete
// std::shared_ptr<int> sp(new int[10], std::default_delete<int[]>());



private:
    int* data;
};

int main() {
    // queue<Test1> que;
    // Test1 T1;
    // que.push(T1);
// 报错
// ~Test1()
// ~Test1()
// free(): double free detected in tcache 2

// 出现这个问题的根本原因是 q.push(t), 当我们查看std::queue::push方法时，我们看到添加到队列的元素"初始化为 x 的副本"。它实际上是一个全新的对象，它使用复制构造函数复制原始对象的每个成员来制作一个新的 Test。默认情况下C++编译器会生成一个复制构造函数：当把所有变量值从旧对象复制到新对象时，就会有两个指针指向内存中的同一个数组。这本质上并不坏，但析构函数将尝试删除同一个数组两次，因此出现"double free detected"运行时错误。

// 解决方法一：添加copy constructor和copy-assignment operator
// 第一步是实现一个copy constructor，它可以安全地将数据从一个对象复制到另一个对象。它可能看起来像这样：

// 现在在复制 Test 对象时，将为新对象分配一个新数组，并且也会复制数组的值。但是把Test对象赋值给另外一个对象时，编译器可能会导致类似的问题，所以我们要同样实现一个copy-assignment operator，看起来像是这样：
    // queue<Test2> que2;
    // Test2 T2;
    // que2.push(T2);

// 智能指针是存储指向动态分配（堆）对象指针的类。除了能够在适当的时间自动删除指向的对象外，他们的工作机制很像C++的内置指针。智能指针在面对异常的时候格外有用，因为他们能够确保正确的销毁动态分配的对象。他们也可以用于跟踪被多用户共享的动态分配对象。
    queue<Test3> que3;
    Test3 T3;
    que3.push(T3);


    return 0;
}