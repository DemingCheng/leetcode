#include <iostream>
using namespace std;

class Empty {

};
// Class Empty
//    size=1 align=1
//    base size=0 base align=1
// Empty (0x0x7fcb606fff60) 0 empty    

class Base {
public:
    virtual void v1() {
        cout << "v1" << endl;
    }
};

class A: public Base {
public:
    virtual void v1() {
        cout << "A::v1" << endl;
    }
};

class B: public Base {
public:
    virtual void v1() {
        cout << "B::v1" << endl;
    }
    virtual void v2() {
        cout << "B::v2" << endl;
    }
};

class C: public A, public B {
public:
    virtual void v1() {
        cout << "C::v1" << endl;
    }

};

class D: public A, public B {
public:
    virtual void v1() {
        cout << "C::v1" << endl;
    }
    int size;
};


int main() {
    return 0;
}

// Vtable for Base
// Base::_ZTV4Base: 3 entries
// 0     (int (*)(...))0
// 8     (int (*)(...))(& _ZTI4Base)
// 16    (int (*)(...))Base::v1

// Class Base
//    size=8 align=8
//    base size=8 base align=8
// Base (0x0x7f13230f3f60) 0 nearly-empty
//     vptr=((& Base::_ZTV4Base) + 16)

// Vtable for A
// A::_ZTV1A: 3 entries
// 0     (int (*)(...))0
// 8     (int (*)(...))(& _ZTI1A)
// 16    (int (*)(...))A::v1

// Class A
//    size=8 align=8
//    base size=8 base align=8
// A (0x0x7f1322d4a4e0) 0 nearly-empty
//     vptr=((& A::_ZTV1A) + 16)
//   Base (0x0x7f1322d503c0) 0 nearly-empty
//       primary-for A (0x0x7f1322d4a4e0)

// Vtable for B
// B::_ZTV1B: 4 entries
// 0     (int (*)(...))0
// 8     (int (*)(...))(& _ZTI1B)
// 16    (int (*)(...))B::v1
// 24    (int (*)(...))B::v2

// Class B
//    size=8 align=8
//    base size=8 base align=8
// B (0x0x7f1322d4a618) 0 nearly-empty
//     vptr=((& B::_ZTV1B) + 16)
//   Base (0x0x7f1322d50540) 0 nearly-empty
//       primary-for B (0x0x7f1322d4a618)

// Vtable for C
// C::_ZTV1C: 7 entries
// 0     (int (*)(...))0
// 8     (int (*)(...))(& _ZTI1C)
// 16    (int (*)(...))C::v1
// 24    (int (*)(...))-8
// 32    (int (*)(...))(& _ZTI1C)
// 40    (int (*)(...))C::_ZThn8_N1C2v1Ev
// 48    (int (*)(...))B::v2

// Class C
//    size=16 align=8
//    base size=16 base align=8
// C (0x0x7f13231daaf0) 0
//     vptr=((& C::_ZTV1C) + 16)
//   A (0x0x7f1322d4a680) 0 nearly-empty
//       primary-for C (0x0x7f13231daaf0)
//     Base (0x0x7f1322d50660) 0 nearly-empty
//         primary-for A (0x0x7f1322d4a680)
//   B (0x0x7f1322d4a6e8) 8 nearly-empty
//       vptr=((& C::_ZTV1C) + 40)
//     Base (0x0x7f1322d506c0) 8 nearly-empty
//         primary-for B (0x0x7f1322d4a6e8)

// Vtable for D
// D::_ZTV1D: 7 entries
// 0     (int (*)(...))0
// 8     (int (*)(...))(& _ZTI1D)
// 16    (int (*)(...))D::v1
// 24    (int (*)(...))-8
// 32    (int (*)(...))(& _ZTI1D)
// 40    (int (*)(...))D::_ZThn8_N1D2v1Ev
// 48    (int (*)(...))B::v2

// Class D
//    size=24 align=8
//    base size=20 base align=8
// D (0x0x7f528d48eb60) 0
//     vptr=((& D::_ZTV1D) + 16)
//   A (0x0x7f528cffe7b8) 0 nearly-empty
//       primary-for D (0x0x7f528d48eb60)
//     Base (0x0x7f528d004780) 0 nearly-empty
//         primary-for A (0x0x7f528cffe7b8)
//   B (0x0x7f528cffe820) 8 nearly-empty
//       vptr=((& D::_ZTV1D) + 40)
//     Base (0x0x7f528d0047e0) 8 nearly-empty
//         primary-for B (0x0x7f528cffe820)
