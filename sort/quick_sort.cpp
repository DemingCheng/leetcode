// 时间复杂度O(nlogn), 每次取partition相当于把数组分成两部分，///////
// 数组有n个元素，因为要递归运算，算出支点pivot的位置，然后递归调用左半部分和有半部分，这个时候理解上是若第一层的话就是n/2、n/2，若是第二层就是n/4、n/4、n/4、n/4这四部分，即n个元素理解上是一共有几层2^k=n，k=log2(n)，然后每层都是n的复杂度，那么平均就是O(nlog2 n)的时间复杂度。但这种肯定是平均情况，如果你是标准排序的情况下，如果已经是升序的顺序，那么递归只存在右半部分了，左半部分都被淘汰了。(n-1)(n-2)....*1，这个复杂度肯定就是O(n^2)。

// 空间复杂度
// 快排的实现是递归调用的， 而且每次函数调用中只使用了常数的空间，因此空间复杂度等于递归深度。

// 最好的情况最多需要O(log2 n)次的嵌套递归调用，所以它需要O(log2 n)的空间。最坏情况下需要O(n)次嵌套递归调用，因此需要O(n)的空间。


// 情况1：数组有序。时间复杂度回退成O(n^2)。因为每次取边上的位pivot，会导致排序后不平衡。不平衡的树。
// 优化方法： 随机取pivot。保证分开的数组不会那么不平衡，从而继续递归。

// 情况2： 有大量重复值 需要二路快排
// https://blog.csdn.net/u010712012/article/details/102853922

#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

// 对nums[l...r]部分进行partition操作
// 返回p, 使得nums[l...p-1] < nums[p] ; nums[p+1...r] > nums[p]
int partition(int nums[], int l, int r) {
    swap(nums[l], nums[rand() % (r - l + 1) + l]);
    int pvalue = nums[l];

    int j = l; 
    for(int i = l + 1; i <= r; ++i) {
        if(nums[i] < pvalue) { 
            j++; // 重点
            swap(nums[j], nums[i]);
        }
    }
    swap(nums[l], nums[j]);
    return j;
}

int partition2(int nums[], int l, int r) {
    swap(nums[l], nums[random()%(r - l + 1) + l]);
    int pvalue = nums[l];

    int i = l + 1, j = r;
    while(true) {
        while(i <= r && nums[i] < pvalue) {
            ++i;
        }
        while(j >= l + 1 && nums[j] > pvalue) {
            --j;
        }
        if (i > j) break;
        swap(nums[i], nums[j]);
        ++i;
        --j;
    }

    swap(nums[l], nums[j]);
    return j;
}

void quick_sort(int nums[], int l, int r) {
    if(l < r) {
        int pivot = partition2(nums, l, r);
        quick_sort(nums, l, pivot - 1);
        quick_sort(nums, pivot + 1, r);
    }
}

void printnumsay(int nums[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << " " << nums[i];
}

int main() {
    int nums[] = {32,43,2,4,6,3,1,7,35,213};
    int n = sizeof(nums) / sizeof(nums[0]);

    quick_sort(nums, 0, n - 1);

    printnumsay(nums, n);
    return 0;
}






// 双路快速排序的partition
// 返回p, 使得nums[l...p-1] <= nums[p] ; nums[p+1...r] >= nums[p]
// 双路快排处理的元素正好等于nums[p]的时候要注意，详见下面的注释：）
template <typename T>
int _partition2(T nums[], int l, int r){

    // 随机在nums[l...r]的范围中, 选择一个数值作为标定点pivot
    swap( nums[l] , nums[rand()%(r-l+1)+l] );
    T v = nums[l];

    // nums[l+1...i) <= v; nums(j...r] >= v
    int i = l+1, j = r;
    while( true ){
        // 注意这里的边界, nums[i] < v, 不能是nums[i] <= v
        // 思考一下为什么?
        while( i <= r && nums[i] < v )
            i ++;

        // 注意这里的边界, nums[j] > v, 不能是nums[j] >= v
        // 思考一下为什么?
        while( j >= l+1 && nums[j] > v )
            j --;

        // 对于上面的两个边界的设定, 有的同学在课程的问答区有很好的回答:)
        // 大家可以参考: http://coding.imooc.com/learn/questiondetail/4920.html

        if( i > j )
            break;

        swap( nums[i] , nums[j] );
        i ++;
        j --;
    }

    swap( nums[l] , nums[j]);

    return j;
}