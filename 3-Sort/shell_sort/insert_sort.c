#include<stdio.h>

int count=0;
void insert_sort(int arr[],int n){
    for(int i=1;i<n;i++){
        int x= arr[i];
        int j=i-1;
        while(j>=0&&arr[j]>x){
            count++;
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=x;
    }
}

int main(void){
    int a[] = {81, 94, 11, 96, 12, 35, 17, 95};
    insert_sort(a,8);
    for(int i=0;i<8;i++)
    printf("%d ",a[i]);
    printf("\ncount=%d",count);
    return 0;
}