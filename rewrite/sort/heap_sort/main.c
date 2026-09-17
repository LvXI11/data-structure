#include<stdio.h>
//比儿子小就下沉
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
    for(int i=n/2-1;i>=0;i--) sift_down(arr,n,i);//建堆
    for(int end=n-1;end>0;end--){       //排序
        int temp=arr[end];
        arr[end]=arr[0];
        arr[0]=temp;
        sift_down(arr,end,0);//重构堆
    }
}

int main(void){

    int arr[]={4,5,7,2,6,1,0,9,-1,3};
    printf("排序前：");
    for(int i=0;i<10;i++) printf("%d ",arr[i]);
    heap_sort(arr,10);
    printf("\n排序后：");
    for(int i=0;i<10;i++) printf("%d ",arr[i]);
    return 0;
}