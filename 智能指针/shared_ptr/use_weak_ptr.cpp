// weak_ptr 设计的目的是为配合 shared_ptr 而引入的一种智能指针来协助 shared_ptr 工作, 它只可以从一个 shared_ptr 或另一个 weak_ptr 对象构造, 它的构造和析构不会引起引用记数的增加或减少。 同时weak_ptr 没有重载*和->但可以使用 lock 获得一个可用的 shared_ptr 对象。

// 弱指针的使用；

// weak_ptr wpGirl_1; // 定义空的弱指针

// weak_ptr wpGirl_2(spGirl); // 使用共享指针构造

// wpGirl_1 = spGirl; // 允许共享指针赋值给弱指针

// 弱指针也可以获得引用计数；

// wpGirl_1.use_count()

// 弱指针不支持 * 和 -> 对指针的访问；

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
    shared_ptr<A> sp_a = make_shared<A>();
    shared_ptr<B> sp_b = make_shared<B>(); 

    // 弱指针的使用
    weak_ptr<A> wp_a(sp_a);	    // 使用共享指针/或弱指针构造

    weak_ptr<B> wp_b;			// 定义空的弱指针
    wp_b = sp_b;			    // 允许共享指针赋值给弱指针
   
    cout << "sp_a \t use_count = " << sp_a.use_count() << endl;
    cout << "sp_b \t use_count = " << sp_b.use_count() << endl;

	
    // 弱指针不支持 * 和 -> 对指针的访问
    // wp_a->use_B(b);
    // (*wp_a).use_B(b);

    // 在必要的使用可以转换成共享指针
    shared_ptr<B> sp_b2;
    sp_b2 = wp_b.lock();

    cout << sp_b2.use_count() << endl;
    // 使用完之后，再将共享指针置NULL即可
    sp_b2 = NULL;

    return 0;
}