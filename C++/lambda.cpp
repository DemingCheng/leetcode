#include<iostream>

int main() {
    auto func1 = [](){
        return 1+2;
    };
    std::cout << func1() << std::endl;
    
// lambda表达式声明
// [capture list] (params list) mutable exception-> return type { function body }
// 含义说明
// capture list：捕获外部变量列表
// params list：形参列表
// mutable指示符：用来说用是否可以修改捕获的变量
// exception：异常设定
// return type：返回类型
// function body：函数体

    int a = 123;
    auto func2 = [a]()mutable{
        a = 321;
        std::cout << a << std::endl;
    };
    std::cout << a << std::endl;

// 例3 值捕获
// 值捕获和参数传递中的值传递类似，被捕获的变量的值在Lambda表达式创建时通过值拷贝的方式传入，因此随后对该变量的修改不会影响影响Lambda表达式中的值。
    int b = 123;
    auto func3 = [b]() {
        // b = 321; 没有mutable会报错 expression must be a modifiable lvalue
        std::cout << "b1:" << b << std::endl; 
    };
    func3();

    auto func4 = [](int b) {
        b = 321;
        std::cout << "b2:" << b << std::endl; 
    };
    func4(b);
    std::cout << "b:" << b << std::endl; 

    auto func3_1 = [b]()mutable {
        b = 321; // 没有mutable会报错
        std::cout << "b1_1:" << b << std::endl; 
    };
    func3_1();
    std::cout << "b:" << b << std::endl; 

// 例4 引用捕获
// 使用引用捕获一个外部变量，只需要在捕获列表变量前面加上一个引用说明符&
    int c = 123;
    auto func5 = [&c](){
        c = 321;
        std::cout << "c1:" << c << std::endl;
    };
    func5();
    std::cout << "c:" << c << std::endl;

    auto func6 = [](int& c){
        c = 456;
        std::cout << "c2:" << c << std::endl;
    };
    func6(c);
// 例5 隐式捕获
// 让编译器根据函数体中的代码来推断需要捕获哪些变量，这种方式称之为隐式捕获。隐式捕获有两种方式，分别是[=]和[&]。[=]表示以值捕获的方式捕获外部变量，[&]表示以引用捕获的方式捕获外部变量。
// 隐式值捕获
    int d = 123;
    auto func7 = [=]() {
        std::cout << "d1:" << d << std::endl;
    };
    func7();
    auto func8 = [&]() {
        d = 321;
        std::cout << "d2:" << d << std::endl;
    };
    std::cout << "d:" << d << std::endl;
    func8();

    return 0;
}