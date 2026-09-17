#include<stdio.h>

void sift_down(int arr[],int size,int i){
    while(2*i+1<size){
        int bigger=2*i+1;
        if(2*i+2<size&&arr[2*i+2]>arr[bigger])
        bigger=2*i+2;
        if(arr[i]>=arr[bigger]) break;
        int temp=arr[i];
        arr[i]=arr[bigger];
        arr[bigger]=temp;
        i=bigger;
    }
}

void heap_sort(int arr[],int n){
    for(int i=n/2-1;i>=0;i--)//建堆
    sift_down(arr,n,i);
    //排序：把堆顶换到数组末尾
    for(int end=n-1;end>0;end--){
        int temp=arr[end];
        arr[end]=arr[0];
        arr[0]=temp;
        sift_down(arr,end,0);
    }
}