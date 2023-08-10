// 我们使用master公式计算一下它的时间复杂度为O(NlogN)。相比较选择排序和冒泡排序的O(N^2)，我们的归并排序明显时间复杂度比前两者好。前两者明显浪费了大量的比较行为，而递归的归并排序就没有浪费大量的比较行为，它可以看作是两个有序部分合并在了一起，但是它额外空间复杂度为O(logN)。

// 插入节点，调整堆时，只会影响他的祖先节点。
#include <iostream>
using namespace std;

void merge(int arr[], int l, int mid, int r) {
    int temp[r - l + 1];
    //初始化，i指向左半部分的起始索引位置l；j指向右半部分起始索引位置mid+1
    int i = l, j = mid + 1, k = 0;
    while(i <= mid && j <= r) {
        temp[k++] = (arr[i] < arr[j]) ? arr[i++] : arr[j++]; //重点
    }
    while(i <= mid) {
        temp[k++] = arr[i++];
    }
    while(j <= r) {
        temp[k++] = arr[j++];
    }

    for(int id = l; id <= r; ++id) { 
        arr[id] = temp[id - l];   //重点 -l
    }
}

void merge_sort(int arr[], int l, int r) {
    if(l == r) {
        return;
    }
    int mid = (r - l) / 2 + l;
    merge_sort(arr, l, mid);
    merge_sort(arr, mid + 1, r);
    merge(arr, l, mid, r);
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << " " << arr[i];
}

int main() {
    int arr[] = {1,4,5,23,12,54,21,55,19};
    int n = sizeof(arr)/sizeof(int);
    merge_sort(arr, 0, n - 1);
    printArray(arr, n);
    return 0;
}

// 图片步骤 https://blog.csdn.net/weixin_12138/article/details/127173748?spm=1001.2101.3001.6650.6&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-6-127173748-blog-103159131.235%5Ev38%5Epc_relevant_sort_base1&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-6-127173748-blog-103159131.235%5Ev38%5Epc_relevant_sort_base1&utm_relevant_index=13