#include<stdio.h>

void merge(int arr[],int temp[],int low,int mid,int high){
    int i=low;
    int j=mid+1;
    int k=low;
    while(i<=mid&&j<=high){
        if(arr[i]<=arr[j]) temp[k++]=arr[i++];
        else               temp[k++]=arr[j++];
    }
    while(i<=mid) temp[k++]=arr[i++];
    while(j<=high) temp[k++]=arr[j++];

    for(int t=low;t<=high;t++) arr[t]=temp[t];
}

void merge_sort(int arr[],int temp[],int low,int high){
    if(low>=high) return;
    int mid=(low+high)/2;
    merge_sort(arr,temp,low,mid);
    merge_sort(arr,temp,mid+1,high);
    merge(arr,temp,low,mid,high);
}