#include<stdio.h>

void shell_sort(int arr[],int n){
    int gap=n/2;
    for(;gap>=1;gap/=2){
        for(int i=gap;i<n;i++){
            int x=arr[i];
            int j=i-gap;
            while(j>=0&&arr[j]>x){
                arr[j+gap]=arr[j];
                j-=gap;
            }
            arr[j+gap]=x;
        }
    }
}