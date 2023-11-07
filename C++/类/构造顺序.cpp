#include<iostream>
#include<string>
using namespace std;


// 参考这篇
// https://www.cnblogs.com/linuxAndMcu/p/10284638.html
class A {
	string a;
public:
	A() {
		cout << "A()" << endl;
	}
	A(string aa) {
		cout << "A(string aa) :" << aa << endl;
		a = aa;
	}
	virtual ~A() {
		cout << "~A() :" << a << endl;
	}
	virtual void  vt() {
		cout << "vt A()" << endl;
	}
};
class B : public A{
	A a1;
	string b;
public:
	B() : a1("default") {
		cout << "B()" << endl;
		b = "default";
	}
	B(string bb) : A(bb),a1(bb + "1") {
		cout << "B(string bb):" << bb << endl;
		b = bb;
	}
	void vt() {
		cout << "vt B()" << endl;  
		A::vt();
	}
	~B() {
		cout << "~B():" << b << endl;
	}
};

int main(void) {
    cout << "-----子类对象构造顺序-----" << endl;
	B b("bb");
// A(string aa) :bb
// A(string aa) :bb1
// B(string bb):bb
    cout << "-----父类对象构造顺序-----" << endl;
    // 1、只是声明一个对象指针，没有定义，所以不会分配内存，也不会调用构造函数。
    // A* a1 = nullptr;
    // 2、声明一个基类指针，分配一个派生类对象空间，构造与直接声明派生类一样。
    // 析构的话若基类的析构函数没有声明为虚函数，只调用基类的析构函数，而不会调用派生类的析构函数。因为基类的析构函数未声明为虚函数。
    // 若基类的析构函数声明为虚函数，调用当前类的析构函数，与子类的析构函数
	A *a1 = new B;
// A()
// A(string aa) :default
// B()
    cout << "-----调用虚函数-----" << endl;
	a1 -> vt();
    cout << "-----析构-----" << endl;
	delete a1;
// ~B():default
// ~A() :default
// ~A() :
// 若父类析构函数不是虚函数
// ~A() :
	cout << endl;
	return 0;
}