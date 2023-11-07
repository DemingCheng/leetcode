// g++ -c -fdump-lang-class gdb_test.cpp
// https://blog.csdn.net/imred/article/details/80717756
#include <stdint.h>
#include <string.h>

class Empty {

};

class Base1
{
public:
    Base1() { memset(&Base1Data, 0x11, sizeof(Base1Data)); }
    virtual void A() {};
    virtual void B() {};
    uint64_t Base1Data;
};

class Base2
{
public:
    Base2() { memset(&Base2Data, 0x22, sizeof(Base2Data)); }
    virtual void C() {};
    virtual void D() {};
    uint64_t Base2Data;
};

class Derived : public Base1, public Base2
{
public:
    Derived() { memset(&DerivedData, 0x33, sizeof(DerivedData)); }
    virtual void A() {};
    virtual void C() {};
    uint64_t DerivedData;
};

int main()
{
    Base1 *x = new Derived;
    x->A();
    x->B();

    Base2 *y = new Derived;
    y->C();
    y->D();

    Derived *z = new Derived;
    z->A();
    z->B();
    z->C();
    z->D();

    return 0;
}