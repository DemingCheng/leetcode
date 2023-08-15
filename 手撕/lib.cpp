#include <assert.h>
#include <iostream>
#include <cstring>
using namespace std;

// 1. strcpy
// 实现strcpy或strcpy函数 这个函数写出来没啥难度，但是除了边界条件需要检查以外，还有一个容易被忽视的地方即其返回值一定要是目标内存地址，以支持所谓的链式拷贝。即：
// strcpy(dest3, strcpy(dest2, strcpy(dest1, src1)));
char *mystrcpy(char *dst, const char *src) { // 1. 源字符串不能变，需要加const保证
    assert(dst != NULL || src != NULL);      // 2. 保证指针有效
    char *pdst = dst;          // 3. 涉及到指针移动，保留dst的头指针用于返回
    while((*pdst++ = *src++) != '\0');     // 4.末尾的'\0'也要复制过来, 上面先执行 *pdst++ = *src++ ，再判断 *src 是否等于'\0',所以保证了'\0'先复制后判断
    return dst;
}

// 2. strncpy
char* mystrncpy(char *dst, const char *src, size_t n) {
    assert(dst != NULL && src != NULL);  // return if dest and src is NULL
    char* pdst = dst;                    
    while(n-- && (*pdst++ = *src++) != '\0');
    *pdst = '\0';   // 手动添加终结符
    return dst;
}

// 3. strlen
size_t mystrlen(const char* src) {
    assert(src != NULL);
    size_t len = 0;
    while(*src != '\0') {
        ++src;
        ++len;
    }
    
    return len;
}

// 4. strcat
// 把src所指字符串添加到dest结尾处(覆盖dest结尾处的’\0’)。
char* mystrcat(char* dst, const char* src) {
    assert(dst != NULL && src != NULL);
    char* pdst = dst;
    while(*pdst != '\0') {  //自增放在循环里，才可以覆盖'\0'
        ++pdst;
    }
    while((*pdst++ = *src++) != '\0');
    return dst;
}



// 5. strcmp
// 比较两个字符串。
// 若相等，则*str1 - *str2 = '\0' - '\0' = 0，返回零；
// 否则，*str1 - *str2 != 0;因为前面的位都相等，所以只需要比较当前位来确定返回值，则返回正数；

/*不可用while(*str1++==*str2++)来比较，当不相等时仍会执行一次++，return返回的比较值实际上是下一个字符。应将++放到循环体中进行。*/

int mystrcmp(const char* s1, const char* s2) {
    assert(s1 != NULL && s2 != NULL);
    while(s1 && s2 && *s1 == *s2) {           
        ++s1;
        ++s2;
    }
    return *s1 - *s2;
}



// 6. memset 
/*
函数解释：将s中前n个字节 （typedef unsigned int size_t ）用 ch 替换并返回 s 。 
memset：作用是在一段内存块中填充某个给定的值，它是对较大的结构体或数组进行清零操作的一种最快方法。

注意，memset是以【字节】为单位进行赋值的，因此下面用法将导致错误：
int arr[5];
memset(array,1,sizeof(arr));

arr指向5个字节的空间，每个都用ASCII为1的字符去填充，转为二进制后，1就是00000001,占一个字节。一个INT元素是4字节，合一起就是00000001000000010000000100000001，就等于16843009，就完成了对一个INT元素的赋值了。所以上面结果不是1而是16843009！
*/
// void* memset(void* src, int ch, size_t n) {   //1. s指针类型未知,另外，n为字节数！
//     assert(src != NULL);
//     void* psrc = src;   
//     while(n--) {
//         *(char* psrc) = (char)ch;   //2. 转化为字符（1字节）
//         psrc = (char*)psrc + 1;     //3. 不能自增，因为不知道指针类型
//     }
//     return src;
// }

void* mymemset(void* src, int ch, size_t n) {   //1. s指针类型未知,另外，n为字节数！
    assert(src != NULL);
    char* psrc = (char*)src;   
    while(n--) {
        *psrc++ = (char)ch;
    }
    return src;
}

// 7. memcopy
// 内存拷贝函数，memcpy函数的功能是从源src所指的内存地址的起始位置开始拷贝n个字节到目标dest所指的内存地址的起始位置中。
void* mymemcpy(void* dst, const void* src, size_t n) {
    assert(dst != NULL && src != NULL);
    void* pdst = dst;
    for(int i = 0; i < n; ++i) {
        *((char*)pdst + i) = *((char*)src + i);
    }
    return dst;
}

// 8. memmove
// 实现一个 memmov 函数
// 这个题目考查点在于 memmov 函数与 memcpy 函数的区别，这两者对于源地址与目标地址内存有重叠的这一情况的处理方式是不一样的。
void* mymemmove1(void* dst, const void* src, size_t n) {
    char* pdst = new char[n];
    for(int i = 0; i < n; ++i) {
        pdst[i] = ((char*)src)[i];
    }
    for(int i = 0; i < n; ++i) {
        ((char*)dst)[i] = pdst[i];
    }
    delete [] pdst;
    return dst;
}

//换方向
void* mymemmove2(void* dst, const void* src, size_t n) {
    char* pdst = (char*)dst;
    char* psrc = (char*)src;
    if(psrc < pdst && psrc + n > pdst) {  // src dst src+n
        psrc += n;
        pdst += n;
        while(n-- > 0) {
            *--pdst = *--psrc;
        }
    }
    else {
        while(n-- > 0) {
            *pdst++ = *psrc++;
        }
    }
    return dst;
}
//https://stackoverflow.com/questions/65804091/implementing-memmove-without-copying-the-source-data

// memmove 和 memcpy的不同
// memmove可以处理source 和 destination重合的情况； memcpy不可以
// 这是因为mommove用了一个临时内存来避免重叠的风险，memcpy直接从source拷贝到destination
// char[] str = "foo-bar";
// memcpy(&str[3], &str[4], 4); // might blow up
// memmove(&str[3], &str[4], 4); // fine



// 8. atoi leetcode 8



int main() {
    // char* , char src[], string
    char src[] = "GeeksforGeeks"; // 13
    char src1[] = "helloworld"; // 10
    
    char dst[20];

    mystrcpy(dst, src);
    cout << "char* strcpy(char *dst, const char* src): " << dst << endl;

    mystrncpy(dst, src1, 5);
    cout << "char* strncpy(char* dst, const char* src, size_t n): " << dst << endl;

    cout << "size_t strlen(const char* src): " << mystrlen(src) << endl;

    mymemset(src, 'a', 5);
    cout << "void* memset(char* src, int ch, size_t n): " << src << endl;

    mymemcpy(dst, src, 5);
    cout << "void* memcpy(char* dst, const char* src, size_t n): " << dst << endl;

    char src2[] = "helloworld"; // 10
    // mymemmove1(src2+1, src2, 5);
    mymemmove2(src2, src2+1, 5);
    cout << "void* memmove1(void* dst, const void* src, size_t n): " << src2 << endl;
    cout << "void* memmove2(void* dst, const void* src, size_t n): " << src2 << endl;
    

    return 0;
}



// #include <assert.h>
// #include <iostream>
// #include <cstring>
// using namespace std;

// char *mystrcpy(char *dst, const char *src) {
//     assert(dst != NULL || src != NULL);     
//     char *pdst = dst;                       
//     while((*pdst++ = *src++) != '\0');    
//     return dst;
// }

// int main() {
//     char src[] = "abcde"; // 5
//     char dst[] = "";
//     mystrcpy(dst, src);
//     cout << "dst: " << dst << endl; // 输出 abcde
//     cout << "src长度: " << strlen(src) << endl; //输出 5
//     cout << "src[0]: " << src[0] << endl;  // 输出b
//     return 0;
// }