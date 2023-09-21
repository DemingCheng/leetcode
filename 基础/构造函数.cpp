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
    Student(Student& s) {
        m_age = s.m_age;
        m_name = s.m_name;
        cout << "3. 拷贝构造函数" << endl;
    }

private:
    int m_age;
    string m_name;
};

int main() {
    Student s1;                              // 调用无参构造函数
    Student s2(18, "2. 一般构造函数");        // 调用一般构造函数
    Student s3 = s2;                         // 调用拷贝构造函数 默认的拷贝构造函数实现的是浅拷贝

    return 0;
}