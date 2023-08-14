#include<iostream>
using namespace std;




void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << " " << arr[i];
}

int main() {
    int arr[] = {1,3,5,22,32,43,1234,32,9};
    int n = sizeof(arr) / sizeof(int);
    merge_sort(arr, 0, n - 1);
    printArray(arr, n);
    return 0;
}