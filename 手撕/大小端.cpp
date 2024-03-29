#include <iostream>
using namespace std;

bool is_little_endian() {
    int i = 1;
    cout << *(char*)&i << endl;
    if(*(char*)&i == 1) {
        return true;
    }
}

bool is_little_endian2() {
    union {
        int i,
        char c,
    }un;

    int i = 1;
    return un.c == 1;
}

int main() {
    cout << is_little_endian() << endl;
    cout << is_little_endian2() << endl;
    return 0;
}

// If it is little endian, the x in the memory will be something like:
//        higher memory
//           ----->
//     +----+----+----+----+
//     |0x01|0x00|0x00|0x00|
//     +----+----+----+----+
//     A
//     |
//    &x
// so (char*)(&x) == 1
// If it is big endian, it will be:
//     +----+----+----+----+
//     |0x00|0x00|0x00|0x01|
//     +----+----+----+----+
//     A
//     |
//    &x
// so this one will be '0'.