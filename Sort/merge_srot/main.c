#include<stdio.h>
//合并两个有序子数组
void merge(int arr[],int temp[],int low,int mid,int high){
    int i=low;
    int j=mid+1;
    int k=low;
    while(i<=mid&&j<=high){
        if(arr[i]<=arr[j]) temp[k++]=arr[i++];
        else               temp[k++]=arr[j++];
    }
    //这里while充当了if来判断是否把arr中的全部元素搬到temp里面去了，妙！
    while(i<=mid)  temp[k++]=arr[i++];
    while(j<=high) temp[k++]=arr[j++];

    //若要在函数内修改指针的值必须传指针的地址(例如：int** p)
    //int* p只能用于操作p指向的那片空间内的值(这也是为什么传数组名能修改数组内元素的原因)
    for(int t=low;t<=high;t++) arr[t]=temp[t];
    //先前用arr=temp发现修改不了
    /*解释：arr和temp传进函数来的是它们的地址的值，
    函数会单独申请空间放它们传进来的值，(离开函数后这片空间会被释放掉)
    所有在函数内赋值相当于修改函数申请的空间内的值*/
}
//递归归并排序
void merge_sort(int arr[],int temp[],int low,int high){
    if(low>=high)return;
    int mid=(low+high)/2;
    //拆分为两子数组递归
    merge_sort(arr,temp,low,mid);
    merge_sort(arr,temp,mid+1,high);
    //需要两个子数组排完序之后才能合并
    merge(arr,temp,low,mid,high);
}
int main(void){

    int arr[]={11,23,5,5,6,34,3,5,2,1};
    int temp[10];
    printf("排序前：");
    for(int i=0;i<10;i++) printf("%d ",arr[i]);
    merge_sort(arr,temp,0,9);
    printf("\n排序后：");
    for(int i=0;i<10;i++) printf("%d ",arr[i]);
    return 0;
}