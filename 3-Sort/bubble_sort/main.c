#include<stdio.h>
#include<stdbool.h>

int main(void){
    int arr[]={5,3,8,1,2,7,4};
    printf("排序前：");
    for(int i=0;i<7;i++){
        printf("%d ",arr[i]);
    }
    for(int i=0;i<7-1;i++){
        bool swapped=false;
        for(int j=0;j<7-1-i;j++){
            if(arr[j]>arr[j+1]){
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
                swapped=true;
            }
        }
        if(!swapped)break;
    }
    printf("\n排序后：");
    for(int i=0;i<7;i++){
        printf("%d ",arr[i]);
    }
    return 0;
}