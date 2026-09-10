#include<stdio.h>

int main(void){

    int arr[]={5,-1,6,34,12,11,3,0,8,1};
    printf("排序前：");
    for(int i=0;i<10;i++) printf("%d ",arr[i]);
    for(int i=1;i<10;i++){
        int x=arr[i];
        int j=i-1;
        for(;j>=0&&x<arr[j];j--){
            arr[j+1]=arr[j];
        }
        arr[j+1]=x;
    }
     printf("\n排序后：");
    for(int i=0;i<10;i++) printf("%d ",arr[i]);
    return 0;
}