#include<iostream>
using namespace std;

struct emptyStruct {};

class emptyClass {};

int main() {
    // 1. 空类和空结构体的大小
    // 在C++，对于结构体和空类，它们的大小是1字节，在C语言下空结构体大小为0(当然这是编译器相关的)。这里的空类和空结构体是指类或结构体中没有任何成员。C中的空结构体大小为0
    cout << sizeof(emptyStruct) << endl;
    cout << sizeof(emptyClass) << endl;
    // 2. 为什么C++中的大小会是1？
    // C++标准中规定，任何不同的对象不能拥有相同的内存地址。 如果空类大小为0，当我们声明一个这个类的对象数组，那么数组中的每个对象都拥有了相同的地址，这显然是违背标准的。

    // 3. 因为空类可以被实例化，为了区分不同的实例,要给实例不同的地址。
    emptyClass a;
    emptyClass b;
    cout << &a << endl;
    cout << &b << endl;

    return 0;
}