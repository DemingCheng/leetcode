#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    // 1.无参构造函数
    Student() {
        m_age = 18;
        m_name = "1.无参构造函数";
        cout << "1. 无参构造函数" << endl;
    }
    ~Student() {
        delete[] data;
    }

    // 2. 一般构造函数
    // 两种初始化列表方式
    Student(int age, string name): m_age(age), m_name(name) {
        cout << "2. 一般构造函数" << endl;
    }

    // Student(int age, string name) {
    //     m_age = age;
    //     m_name = name;
    // }
    // 3. 拷贝构造函数
    Student(const Student& other) {
        m_age = other.m_age;
        m_name = other.m_name;
        cout << "3. 拷贝构造函数" << endl;
    }
    // 4. 拷贝赋值运算符
    // 需要考虑自赋值和异常处理
    Student& operator=(const Student& other) {

    }

    // 5. 移动构造函数
    Student(Student&& other) {
        data = nullptr;
        data = other.data;
        other.data = nullptr;
    }

    // 6. 移动赋值运算符
// 移动赋值运算符和复制构造函数类似，但是在占用源对象资源之前，会先释放自身的资源。移动复制运算符函数的执行逻辑如下：
// 释放当前*this的资源
// 占用other的资源
// 设置other为默认构造状态
// 返回*this
    Student& operator=(Student&& other) {
        if(&other != this) {   // 自赋值检测 Self-assignment detection
            delete[] data;     // 释放所有持有的资源 Release any resource we're holding
            data = other.data; // 拷贝资源
            other.data = nullptr;
        }
        return *this;
    }

private:
    int m_age;
    string m_name;
    char* data;
};

int main() {
    Student s1;                              // 调用无参构造函数
    Student s2(18, "2. 一般构造函数");        // 调用一般构造函数
    Student s3 = s2;                         // 调用拷贝构造函数 默认的拷贝构造函数实现的是浅拷贝

    return 0;
}

// https://learncppcn.github.io/15-move-semantics-and-smart-pointers/15.3-move-constructors-and-move-assignment/
// https://cloud.tencent.com/developer/article/2306422
// #include <iostream>
// class MyString {
// public:
//     char* data;
//     MyString(const char* str) {
//         int length = strlen(str);
//         data = new char[length + 1];
//         strcpy(data, str);
//     }

//     ~MyString() {
//         delete[] data;
//     }

//     // 移动赋值运算符
//     MyString& operator=(MyString&& other) noexcept {
//         if (this != &other) {
//             delete[] data;
//             data = other.data;
//             other.data = nullptr;
//         }
//         return *this;
//     }
// };

// int main() {
//     MyString str1("Hello");
//     MyString str2("World");

//     str2 = std::move(str1);  // 调用移动赋值运算符

//     std::cout << str2.data << std::endl;  // 输出 "Hello"

//     return 0;
// }



class Person
{
public:
    const char*  name_;
    Person(const char* name):name_(name) {};

    Person(const Person& person)
    {
        name_ = person.name_;
        std::cout << "拷贝构造函数" << std::endl;
    }

    Person(Person&& person)
    {
        name_ = person.name_;
        std::cout << "移动构造函数"<< std::endl;
    }

    Person& operator=(const Person& person)
    {

        name_ = person.name_;
        std::cout << "拷贝赋值运算符" << std::endl;
        return *this;
    }


    Person& operator=(Person&& person)
    {
        if (this != &person) {
            name_ = person.name_;
            std::cout << "移动赋值运算符" << std::endl;
        }
        return *this;
    }
};
 

 
Person getPerson()
{
    Person person("person in func");
    return person;
}

int main(void)
{
    Person person1("xiaohong");
    Person person2("xiaoming");
    Person person3(getPerson());//移动构造函数
    Person person4(std::move(person1));//移动构造函数
    Person person5(person2);//拷贝构造函数

    Person person6("xiaolan");
    person6 = std::move(person3);//移动赋值运算
    Person person7("xiaoqi");
    person7 = Person("xiaoqi");//移动赋值运算
    Person person8("xiaoba");
    person8 = person1;//拷贝赋值运算符
    system("pause");
    return 0;
}