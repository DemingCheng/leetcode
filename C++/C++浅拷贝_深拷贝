浅拷贝

深拷贝 是拷贝对象时，如果被拷贝对象内部还有指针，引用指向其他资源，需要重新开辟内存空间存储资源，不是简单的赋值。

如果拷贝对象内部有指针，分配了堆内存
浅拷贝只是拷贝了相同的指针，指针指向同一块内存，新旧对象共享同一块内存
深拷贝还对指向的内容进行了拷贝。深拷贝后的指针指向的是不同地址。


class A {
public:
    A(int size) : size_(size) {
        data_ = new int[size];
    }
    A(){}
    A(const A& a) {
        size_ = a.size_;
        data_ = a.data_;
        cout << "copy " << endl;
    }
    ~A() {
        delete[] data_;
    }
    int *data_;
    int size_;
};
int main() {
    A a(10);
    A b = a;
    cout << "b " << b.data_ << endl;
    cout << "a " << a.data_ << endl;
    return 0;
}








