#include<stdio.h>

int partition(int arr[],int low,int high){
    arr[0]=arr[low];
    while(low<high){
        while(low<high&&arr[high]>=arr[0]) high--;
        arr[low]=arr[high];
        while(low<high&&arr[low]<=arr[0]) low++;
        arr[high]=arr[low];
    }
    arr[low]=arr[0];
    return low;
}
void quik_sort(int arr[],int low,int high){
   if(low<high){
    int pivot=partition(arr,low,high);
    quik_sort(arr,low,pivot-1);
    quik_sort(arr,pivot+1,high);
   }
}

int main(void){
    int arr[11]={0,2,65,9,23,45,5,7,12,2,9};
    printf("排序前：");
    for(int i=1;i<11;i++){
        printf("%d ",arr[i]);
    }

    quik_sort(arr,1,10);

    printf("\n排序后：");
    for(int i=1;i<11;i++){
        printf("%d ",arr[i]);
    }
    return 0;
}