#include <iostream>
using namespace std;
class A {
public:
    A() {
        cout << "A()" << endl;
    }

    A(string str) {
        str_ = str;
        cout << "A(string str)" << endl;
    }

    ~A() {
        cout << "~A()" << endl;
    }

    virtual void vfunc() {
        cout << "vfunc()" << endl;
    }

private:
    string str_;
};

class B {

};

int main() {


    return 0;
}