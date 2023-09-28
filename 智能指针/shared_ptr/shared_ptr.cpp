#include <iostream>
#include <memory>
namespace cdm {

class ref_count {
public:
    ref_count(): count_(1) {}

    void increase() {
        count_++;
    }

    long decrease() {
        return --count_;
    }

    long get_count() {
        return count_;
    }

private:
    long count_;
};

template<typename T>
class shared_ptr {
public:
    shared_ptr(T* ptr = nullptr):ptr_(ptr) {
        if(ptr) {
            ref_count_ = new ref_count();
        }
    } 
    ~shared_ptr() {
        if(ptr_ && ref_count_->decrease() == 0) {
            delete ptr_;
            delete ref_count_;
            ptr_ = nullptr;
            ref_count_ = nullptr;
        }
    }
    shared_ptr(const shared_ptr& other) {
        this->ptr_ = other.ptr_;
        if(this->ptr_) {
            other.ref_count_->increase();
            this->ref_count_ = other.ref_count_;
        }
    }
    // 赋值操作时，会执行operator=操作，当return *this的时候，返回的是调用该赋值操作对象的本身。this是对象的指针。a=b，调用的是对象a的赋值构造函数，赋值结束后，肯定要返回对象a。例如int a = 1; 赋值结束后，肯定返回的是a。总结：赋值构造函数为了实现赋值操作完成后，可以作为左值接受其他对象的赋值。因此必须返回一个reference to *this，如果返回位值类型，且如果作为左值，则其其对象得不到想要的赋值结果，因为作为左值的是值类型的临时对象。返回引用reference to *this时，赋值操作作为左值，可得到正确的赋值结果。
    shared_ptr& operator=(const shared_ptr& other) {
        this->ptr_ = other.ptr_;
        if(this->ptr_) {
            other.ref_count_->increase();
            this->ref_count_ = other.ref_count_;
        }
        return *this;
    }
    // "移动赋值运算符"
    shared_ptr& operator=(shared_ptr&& other) {
        // cout << "移动赋值运算符" << endl;
        ptr_ = other.ptr_;
        if(ptr_) {
            ref_count_ = other.ref_count_;
            other.ptr_ = nullptr;
            other.ref_count_ = nullptr;
        }
        return *this;
    }

    int use_count() {
        if(ptr_) {
            return ref_count_->get_count();
        }
        else {
            return 0;
        }
    }

private:
    T* ptr_;
    ref_count* ref_count_;
};

}


int main() {
    cdm::shared_ptr<int> p;
    // std::shared_ptr<int> p1 = std::make_shared<int>(1);  // make_shared
    std::shared_ptr<int> p = std::make_shared<int> (1);
    
    cdm::shared_ptr<int> p1(new int(1));
    cdm::shared_ptr<int> p2(p1);                         // 拷贝构造
    cdm::shared_ptr<int> p3 = p1;                        // 拷贝赋值运算符
    std::cout << "shared_ptr p1 count: " << p1.use_count() << std::endl;

    return 0;
}