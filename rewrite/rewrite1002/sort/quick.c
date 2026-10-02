#include<stdio.h>
#include<stdlib.h>

int partition(int arr[],int low,int high){
    int x=arr[low];
    int i=low;
    int j=high;
    while(i<j){
        while(i<j&&arr[j]>=x) j--;
        arr[i]=arr[j];
        while(i<j&&arr[i]<=x) i++;
        arr[j]=arr[i]; 
    }
    arr[i]=x;
    return i;
}

void quick_sort(int arr[],int low,int high){
    if(low>=high) return;
    int pivot=partition(arr,low,high);
    quick_sort(arr,low,pivot-1);
    quick_sort(arr,pivot+1,high);
}