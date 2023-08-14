

#include <iostream>
struct Foo
{
    char c;
    int i;
    double d;
};
struct Goo
{
    char c;
    double d;
    int i;
};

int main(int argc, char const *argv[])
{
    std::cout << sizeof(Foo) << std::endl; // 16
    std::cout << sizeof(Goo) << std::endl; // 24
}
