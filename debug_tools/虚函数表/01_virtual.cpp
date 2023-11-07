// 必读 对象内存 配图 https://blog.csdn.net/qq_38872537/article/details/112907006 
// https://blog.csdn.net/imred/article/details/80717756
#include<iostream>
using namespace std;


struct Base1 {
    virtual void v() {}
    virtual void v1() {}
};

struct Base2 {
    virtual void v() {}
    virtual void v2() {}
};

struct Derived : Base1, Base2 {
    void v() override {}
    void v3() {}
};


// Vtable for Base1
// Base1::_ZTV5Base1: 4 entries
// 0     (int (*)(...))0
// 8     (int (*)(...))(& _ZTI5Base1)
// 16    (int (*)(...))Base1::v
// 24    (int (*)(...))Base1::v1

// Class Base1
//    size=8 align=8
//    base size=8 base align=8
// Base1 (0x0x7f106c295f60) 0 nearly-empty
//     vptr=((& Base1::_ZTV5Base1) + 16)

// Vtable for Base2
// Base2::_ZTV5Base2: 4 entries
// 0     (int (*)(...))0
// 8     (int (*)(...))(& _ZTI5Base2)
// 16    (int (*)(...))Base2::v
// 24    (int (*)(...))Base2::v2

// Class Base2
//    size=8 align=8
//    base size=8 base align=8
// Base2 (0x0x7f106beef0c0) 0 nearly-empty
//     vptr=((& Base2::_ZTV5Base2) + 16)

// Vtable for Derived
// Derived::_ZTV7Derived: 8 entries
// 0     (int (*)(...))0
// 8     (int (*)(...))(& _ZTI7Derived)
// 16    (int (*)(...))Derived::v
// 24    (int (*)(...))Base1::v1
// 32    (int (*)(...))-8
// 40    (int (*)(...))(& _ZTI7Derived)
// 48    (int (*)(...))Derived::_ZThn8_N7Derived1vEv
// 56    (int (*)(...))Base2::v2

// Class Derived
//    size=16 align=8
//    base size=16 base align=8
// Derived (0x0x7f106c37baf0) 0
//     vptr=((& Derived::_ZTV7Derived) + 16)
//   Base1 (0x0x7f106beef1e0) 0 nearly-empty
//       primary-for Derived (0x0x7f106c37baf0)
//   Base2 (0x0x7f106beef240) 8 nearly-empty
//       vptr=((& Derived::_ZTV7Derived) + 48)