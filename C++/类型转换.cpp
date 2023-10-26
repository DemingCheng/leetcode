#include <iostream>
#include <exception>
using namespace std;

class Base {
    virtual void func() {}
};
class Derived:public Base {
    int a;
};

int main() {
    try{
        // 上行
        Base* base = new Derived();
        Derived* p1 = static_cast<Derived*>(base);
        Derived* p2 = dynamic_cast<Derived*>(base);
        
        // 下行
        Base* base1 = new Base();     // 
        Base* base2 = new Derived();  //

        Derived* p3 = dynamic_cast<Derived*>(base1);
        Derived* p4 = dynamic_cast<Derived*>(base2);
        if (p3==0) cout << "p3无法转换，返回空指针.\n";
        if (p4==0) cout << "p4无法转换，返回空指针.\n";

        // 尽管base1和base2都是Base指针类型，但其指向的对象却分别是Derived 和 Base。而由于Base相比Derived少了int a的定义，因此p3无法完整的由Base转到Derived。


    } catch (exception& e) {
        cout << "Exception: " << e.what();
    }
    

    return 0;
}

// #include <iostream>
// #include <exception>
// using namespace std;

// class Base { virtual void dummy() {} };
// class Derived: public Base { int a; };

// int main () {
//   try {
//     Base * pba = new Derived;
//     Base * pbb = new Base;
//     Derived * pd;

//     pd = dynamic_cast<Derived*>(pba);
//     if (pd==0) cout << "Null pointer on first type-cast.\n";

//     pd = dynamic_cast<Derived*>(pbb);
//     if (pd==0) cout << "Null pointer on second type-cast.\n";

//   } catch (exception& e) {cout << "Exception: " << e.what();}
//   return 0;
// }
