#include<stdio.h>

int partition(int arr[],int low,int high){
    int x=arr[high];
    while(low<high){
        while(low<high&&arr[low]<=x) low++;
        arr[high]=arr[low];
        while(low<high&&arr[high]>=x) high--;
        arr[low]=arr[high];
    }
    arr[low]=x;
    return low;
}