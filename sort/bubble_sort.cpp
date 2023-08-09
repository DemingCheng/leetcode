#include <bits/stdc++.h>
using namespace std;

void bubble_sort(int array[], int n) {
    bool swapped;
    for(int i = 0; i < n - 1; ++i) {
        swapped = false;
        for(int j = 0; j < n - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                swap(array[j], array[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false) {
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
    int array[] = {64, 34, 25, 12, 22, 11, 90};
    int N = sizeof(array) / sizeof(array[0]);
    bubble_sort(array, N);
    printArray(array, N);
    return 0;
}