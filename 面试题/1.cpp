// 1. 两个int（32位）整数a和b的二进制表达中，有多少个位(bit)不同
#include <iostream>

using namespace std;


int main() {
    int a, b;
    cin >> a;
    cin >> b;
    int ans = 0;
    int num = a ^ b;
    while(num) {
        ans++;
        num = num & (num - 1);
    }
    
    cout << ans << endl;
    return 0;
}