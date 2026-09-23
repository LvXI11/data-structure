#include<stdio.h>

int main(void){

    int arr[]={34,56,3,0,6,8,1,2,7,5};
    printf("排序前：");
    for(int i=0;i<10;i++) printf("%d ",arr[i]);

    for(int i=0;i<10-1;i++){
        int min=i;
        for(int j=i+1;j<10;j++){
            if(arr[min]>arr[j]){
                min=j;
            }
        }
        int temp=arr[i];
        arr[i]=arr[min];
        arr[min]=temp;
    }
    printf("\n排序后：");
    for(int i=0;i<10;i++) printf("%d ",arr[i]);
    return 0;
}