// 时间复杂度O(nlogn), 每次取partition相当于把数组分成两部分，///////

// 情况1：数组有序。时间复杂度回退成O(n^2)。因为每次取边上的位pivot，会导致排序后不平衡。不平衡的树。
// 优化方法： 随机取pivot。保证分开的数组不会那么不平衡，从而继续递归。

// 情况2： 有大量重复值
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

int partition(int arr[], int l, int r) {
    int i = rand()%(r - l + 1);
    swap(arr[l], arr[rand() % (r - l + 1) + l]);
    int pvalue = arr[l];
    int j = l;
    for(int i = l + 1; i <= r; ++i) {
        if(arr[i] < pvalue) {
            j++;
            swap(arr[j], arr[i]);
        }
    }
    swap(arr[l], arr[j]);
    return j;
}

void _quick_sort(int arr[], int l, int r) {
    int pivot = partition(arr, l, r);
    _quick_sort(arr, l, pivot - 1);
    _quick_sort(arr, pivot + 1, r);

}

void quick_sort(int arr[], int N) {
    _quick_sort(arr, 0, N-1);
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << " " << arr[i];
}

int main() {
    int arr[] = {32,43,2,4,6,3,1,7,35,213};
    int N = sizeof(arr) / sizeof(arr[0]);
    cout << N << endl;
    quick_sort(arr, N);
    printArray(arr, N);

    return 0;
}