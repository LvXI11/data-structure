#include<stdio.h>

void select_sort(int arr[],int n){
    for(int i=0;i<n;i++){
        int min=i;
        for(int j=i;j<n;j++){
            if(arr[min]>arr[j]){
                min=j;
            }
        }
        int temp=arr[min];
        arr[min]=arr[i];
        arr[i]=temp;
    }
}