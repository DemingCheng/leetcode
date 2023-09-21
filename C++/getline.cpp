#include <iostream>
#include <sstream>
#include <vector>
// getline
// https://blog.csdn.net/u011630575/article/details/79721024

using namespace std;

// string stream 切分字符串到一个一个词，统计有几个词
int count(string str) {
    stringstream ss(str);
    int cnt = 0;
    string word;  // 存一个一个词
    while(ss >> word) {
        cnt++;
    }
    return cnt;
}

// leetcode 验证ip需要拆分ipv4 ipv6字符串
void split(string ip, vector<string>& ipList, char delim) {
    stringstream ss(ip);
    string str;
    while(getline(ss, str, delim)) {
        ipList.push_back(str);
    }
    if(ip.size() > 0 && ip.back() == delim)
        ipList.push_back({""}); // 如果不加，会漏掉最后一个：后面的部分":::::::"
    return; 
}


int main() {
    // getline用法
    // 1. cin输入
    string str1;
    getline(cin, str1, 'e');
    cout << str1 << endl;  //输入abcdefg 返回abcd

    // string stream str()string转ss， clear(abced)清除ss
    // 2. string stream输入
    stringstream ss("abcdef");
    ss.str("bbbbc");
    string str2;
    getline(ss, str2, 'c');
    cout << str2 << endl;

    // string stream 切分字符串
    cout << count("Breaking input into word") << endl; // 4

    // 拆分字符串
    vector<string> ipv4List;
    string ipv4 = "192.168.0.1";
    split(ipv4, ipv4List, '.');
    for(const auto ip:ipv4List) {
        cout << ip << " ";
    }
    cout << endl;

    vector<string> ipv6List;
    string ipv6_1 = "2001:db8::1234:5678"; // (表示中间 4 个区段为零） 
    string ipv6_2 = "::1234:5678:";
    string ipv6_3 = ":::::::";
    split(ipv6_3, ipv6List, ':');
    for(const auto ip:ipv6List) {
        cout << ip << " ";
    }
    cout << ipv6List.size() << endl;
    return 0;
}
// 下列是有效的 IPv6（标准）位址范例：
// 2001:db8:3333:4444:5555:6666:7777:8888 
// 2001:db8:3333:4444:CCCC:DDDD:EEEE:FFFF ::（表示全部 8 个区段均为零） 
// 2001:db8::（表示最后 6 个区段为零） 
// ::1234:5678（表示前 6 个区段为零） 
// 2001:db8::1234:5678（表示中间 4 个区段为零） 
// 2001:0db8:0001:0000:0000:0ab9:C0A8:0102（可以压缩以删除前导零，如下所示：2001:db8:1::ab9:C0A8:102）
