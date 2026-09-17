#include<stdio.h>

void sift_down(int arr[],int size,int i){//下沉，满足大顶堆的定义
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

void build(int arr[],int n,int i){//建堆
    sift_down(arr,n,i);
}

void heap_sort(int arr[],int n){//排序
    for(int i=n/2-1;i>=0;i--)
    build(arr,n,i);
    for(int end=n-1;end>0;end--){
        int temp=arr[end];
        arr[end]=arr[0];
        arr[0]=temp;
        sift_down(arr,end,0);//整理堆，使其始终保持大顶堆的顺序
    }
}

int main(void){
    int arr[]={8,4,4,3,7,9,1,5,0,6};
    for(int i=0;i<10;i++) printf("%d ",arr[i]);
    printf("\n");
    heap_sort(arr,10);
    for(int i=0;i<10;i++) printf("%d ",arr[i]);
    return 0;
}