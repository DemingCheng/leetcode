// weak_ptr 弱指针， 是为了配合shared_ptr解决shared_ptr的循环引用问题。
// 可以通过shared_ptr或者weak_ptr构造，但是weak_ptr的构造和析构不改变引用计数。
// 同时weak_ptr 没有重载*和->但可以使用 lock 获得一个可用的 shared_ptr 对象。

// https://zhuanlan.zhihu.com/p/526147194
#include <iostream>
#include <memory>
using namespace std;

// ! 在类中使用弱指针接管共享指针，在需要使用时就转换成共享指针去使用即可！

class B; // 类的前置声明

class A {
public:
    A() {cout << "A()" << endl;}

    ~A() {cout << "~A()" << endl;}

    void use_B(shared_ptr<B> b) {
        this->_b = b;
    }

private:
    weak_ptr<B> _b;
};


class B {
public:
    B() {cout << "B()" << endl;}

    ~B() {cout << "~B()" << endl;}

    void use_A(shared_ptr<A> a) {
        this->_a = a;
    }

private:
    weak_ptr<A> _a;

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