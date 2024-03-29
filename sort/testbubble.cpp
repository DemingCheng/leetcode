#include <iostream>
#include <algorithm>
using namespace std;

void heap_sort(int *a,int n);
void heapinsert(int *a,int heapsize);
void heapify(int *a,int *heapsize);


void heap_sort(int *a,int n){
	int heapsize = 0;
	for(;heapsize<n;heapsize++){
		heapinsert(a,heapsize);  
	}//形成一个大根堆

	heapify(a,&heapsize); 
}

void heapinsert(int *a,int heapsize){
	
	int i = heapsize;
	while(a[i] > a[(i-1)/2]){
	    swap(a[i],a[(i-1)/2]);
	    i = (i-1)/2;
	}
}

void heapify(int *a,int *heapsize){
//这里需要注意，heapsize是堆中数目的个数，但不是堆中最后一个元素的下标
//堆中最后一个元素下标为*heapsize-1	
	while( (*heapsize)>0 ){
		swap(a[0],a[(*heapsize)-1]); //交换堆中的根节点和最后一个子节点 
		(*heapsize)--;
		//整理heapsize的部分重新构成大根堆 
		int i = 0;
		while( (i*2+1)<=( *heapsize-1) ){   //判断是否有子节点 
			if((i*2+2)<= *heapsize-1 )     //左右孩子都有 
			{
				    int temp = (a[i*2+1]>a[i*2+2])?i*2+1:i*2+2;
			        if(a[i] < a[temp]){    //右孩子是否存在 ，找两者其中较大的一个 
					    swap(a[i],a[temp]);
				        i = temp;
				    }
				    else{
				    	break;
					} 
			}
			
		    else{ //只有左孩子 
			        if(a[i] < a[i*2+1]){    //没有右孩子的情况下，直接和左孩子进行比较
				 	    swap(a[i],a[i*2+1]);
				 	    i = i*2+1; 
		            }
		            else   //如果没有出现交换操作，说明已经到达了合适位置 
			             break;	
		    }
	    }
	} 
} 



int main(){
	int arr[] = {3,2,5,1,6,3,2,34,6,12,45,42,99};
	int n = sizeof(arr)/sizeof(int);

	heap_sort(arr,n);
	
	for(int i = 0;i<n;i++){
    	cout << arr[i] << " ";
	}


	return 0;
}
 
