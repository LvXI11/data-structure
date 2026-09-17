#include<stdio.h>
//随便取一个pivot，把数组里剩下的元素与其比较，大的放右边，小的放左边
int partition(int arr[],int low,int high){
    int x=arr[low];
    while(low<high){
        while(low<high&&arr[high]>=x) high--;
        arr[low]=arr[high];
        while(low<high&&arr[low]<=x) low++;
        arr[high]=arr[low];
    }
    arr[low]=x;
    return low;
}
//递归排左右两个子数组，直到low和high相等，就排完了，快速排序不稳定
void quik_sort(int arr[],int low,int high){
    if(low<high){
    int pivot=partition(arr,low,high);
    quik_sort(arr,low,pivot-1);
    quik_sort(arr,pivot+1,high);
    }
}
int main(void){
    int arr[]={5,4,9,1,2,2,7,3,10,8};
    printf("排序前：");
    for(int i=0;i<10;i++) printf("%d ",arr[i]);
    quik_sort(arr,0,9);
    printf("\n排序后：");
    for(int i=0;i<10;i++) printf("%d ",arr[i]);
    return 0;
}