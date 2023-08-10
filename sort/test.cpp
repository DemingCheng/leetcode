#include<iostream>
using namespace std;

void bubble_sort(int arr[], int n) {
    bool swapped;
    for(int i = 0; i < n - 1; i++) {
        swapped = false;
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if(swapped == false) {
            break;
        }
    }    
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << " " << arr[i];
}

int main() {
    int arr[] = {1,3,5,22,32,43,1234,32,9};
    int n = sizeof(arr) / sizeof(int);
    bubble_sort(arr, n);
    printArray(arr, n);
    return 0;
}