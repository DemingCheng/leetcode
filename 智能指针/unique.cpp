#include <iostream>
#include <string>
// 通过get来获取裸指针

// ->箭头函数来调用成员
// * 星号函数调用解引用
class Cat {
public:
    Cat() = default;
    Cat(std::string name);
    ~Cat();

    void cat_info() const{
        std::cout << "cat info: " << name << std::endl;
    }

    std::string get_name() const{
        return name;
    }
    
    void set_name(const std::string &name){
        this->name = name;
    }

private:
    std::string name("Mimi");

};

int main() {



}