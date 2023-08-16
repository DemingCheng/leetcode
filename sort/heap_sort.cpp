// 逻辑上是一颗完全二叉树，形式上是数组的形式存储。
// 以完全二叉树的结构来维护一组数据。这使得它操作的时间复杂度为O(1)~O(logN)之间
// i节点的 左孩子 2i+1, 右孩子 2i+2, 父节点 (i-1)/2
// 大顶堆，最大元素在堆顶
// https://blog.csdn.net/weixin_50941083/article/details/121096435

// 增序排列 是大顶堆。每次取堆头放入arr[heapsize]也就是最大的放最后面

#include <iostream>
#include <algorithm>
using namespace std;
void heapinsert(int arr[], int heapsize);
void heapify(int arr[], int heapsize);
void heap_sort(int arr[], int heapsize);

void heapify(int arr[], int heapsize) {
    while(heapsize > 0) {
        swap(arr[0], arr[heapsize]);
        heapsize--;

        int i = 0;
        while((i * 2 + 1) <= heapsize - 1) {
            if((i * 2 + 2) <= heapsize - 1) {
                int temp = arr[i*2+1] > arr[i*2+2] ? i*2+1 : i*2+2; //重点
                if (arr[i] < arr[temp]) {
                    swap(arr[i], arr[temp]);
                    i = temp;
                }
                else {
                    break;
                }
            }
            else {
                if (arr[i] < arr[i*2+1]) {
                    swap(arr[i], arr[i*2+1]);
                    i = i*2+1;
                }
                else {
                    break;
                }
            }
        }
    }

}

void heapinsert(int arr[], int heapsize) {
    int i = heapsize;
    while(arr[i] > arr[(i - 1) / 2]) {
        swap(arr[i], arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void heap_sort(int arr[], int heapsize) {
    for(int i = 0; i < heapsize; ++i) {
        heapinsert(arr, i);
    }
    heapify(arr, heapsize);
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

    heap_sort(arr, n);


    printArray(arr, n);
    return 0;
}

// https://blog.csdn.net/weixin_50941083/article/details/121096435?ops_request_misc=&request_id=0f0d7750574b4e0989cfeca198ff220d&biz_id=&utm_medium=distribute.pc_search_result.none-task-blog-2~blog~koosearch~default-2-121096435-null-null.268^v1^control&utm_term=%E6%8E%92%E5%BA%8F&spm=1018.2226.3001.4450