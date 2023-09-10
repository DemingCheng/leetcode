C和C++区别

1. C是面向过程的编程语言
C++包含四部分：面向过程的编程语言，面向对象的编程语言，STL，元编程。
元编程比如泛型，模板

2. C++和C有些不同
- 编译器对类型大小设定不同：比如对于空结构体和空类。C中的空结构体大小是0，C++中空结构体和空类大小是1。
- C++增加了命名空间，避免了命名冲突


C++ Char*, std:string, and Char[]?

来自 <https://www.scaler.com/topics/cpp-char/> 

Char*		     The char* in C++ is a pointer used to point to the first character of the character array.	
std::string  The std::string is a standard library that includes support for strings in C++.	
Char[]       The char[] is a character array that stores all the characters in the string.
