#include<stdio.h>

int count=0;
void insert_gap_sort(int arr[],int n){
    int gap=n/2;
    for(;gap>=1;gap/=2){
        for(int j=gap;j<n;j++){
            int x=arr[j];
            int k=j-gap;
            while(k>=0&&arr[k]>x){
                count++;
                arr[k+gap]=arr[k];
                k-=gap;
            }
            arr[k+gap]=x;
        }
        printf("gap=%d ",gap);
        for(int m=0;m<n;m++)
        printf("%d ",arr[m]);
        printf("\n");
    }
    printf("count=%d",count);
}

int main(void){
    int a[]={81,94,11,96,12,35,17,95};
    insert_gap_sort(a,8);
    return 0;
}