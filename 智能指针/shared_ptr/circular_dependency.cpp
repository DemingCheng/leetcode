// 循环引用
// 交叉互相持有对方的管理对象
// 循环引用指两个对象交叉持有对方的shared_ptr,并且指向对方，造成循环引用，导致引用计数器错误，不会析构智能指针，造成内存泄漏。
// 解决方法 weak_ptr
#include <iostream>
#include <memory>
using namespace std;

class B; // 类的前置声明

class A {
public:
    A() {cout << "A()" << endl;}

    ~A() {cout << "~A()" << endl;}

    void use_B(shared_ptr<B> b) {
        this->_b = b;
    }

private:
    shared_ptr<B> _b;
};


class B {
public:
    B() {cout << "B()" << endl;}

    ~B() {cout << "~B()" << endl;}

    void use_A(shared_ptr<A> a) {
        this->_a = a;
    }

private:
    shared_ptr<A> _a;

};


int main() {
    shared_ptr<A> a = make_shared<A>();
    shared_ptr<B> b = make_shared<B>();

    cout << "a.use_count(): " << a.use_count() << endl;
    cout << "b.use_count(): " << b.use_count() << endl;

    a->use_B(b);
    b->use_A(a);

    cout << "a.use_count(): " << a.use_count() << endl;
    cout << "b.use_count(): " << b.use_count() << endl; 
    // 没有析构了

    return 0;
}



// 另一种写法
// #include <iostream>
// #include <memory>
// using namespace std;

// class B;

// class A {
// public:
//     ~A() {
//         cout << "~A()" << endl;
//     }

//     shared_ptr<B> _b;
// };

// class B {
// public:
//     ~B() {
//         cout << "~B()" << endl;
//     }

//     shared_ptr<A> _a;
// };



// int main() {
//     shared_ptr<A> a(new A());
//     shared_ptr<B> b(new B());

//     // 循环引用
//     a->_b = b;
//     b->_a = a;

//     return 0;
// }