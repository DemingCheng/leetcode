#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main() {
    string s = "abcdef";
    string s2(s.rbegin(), s.rend());
    cout << s2 << endl;
    return 0;
}