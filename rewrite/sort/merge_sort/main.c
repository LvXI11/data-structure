#include<stdio.h>
//三个变量跟着数组走
void merge(int arr[],int temp[],int low,int mid,int high){
    int i=low;
    int j=mid+1;
    int k=low;
    while(i<=mid&&j<=high){
        if(arr[i]<=arr[j]) temp[k++]=arr[i++];
        else              temp[k++]=arr[j++];
    }
    while(i<=mid)  temp[k++]=arr[i++];
    while(j<=high) temp[k++]=arr[j++];
    for(int t=low;t<=high;t++) arr[t]=temp[t];//复制数组只能用循环改，修改地址只是改了标签名，本地数组还是没变
}
//先分、后治、再合
void merge_sort(int arr[],int temp[],int low,int high){
    if(low>=high)return;
    int mid=(low+high)/2;
    merge_sort(arr,temp,low,mid);
    merge_sort(arr,temp,mid+1,high);
    merge(arr,temp,low,mid,high);
}
int main(void){
    int arr[]={3,4,6,2,1,1,1,98,23,5};
    int temp[10];
    printf("排序前：");
    for(int i=0;i<10;i++) printf("%d ",arr[i]);
    merge_sort(arr,temp,0,9);
    printf("\n排序后：");
    for(int i=0;i<10;i++) printf("%d ",arr[i]);
    return 0;
}