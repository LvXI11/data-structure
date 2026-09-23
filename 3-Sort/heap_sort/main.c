#include<stdio.h>
//从最后一个非叶子节点开始下沉，底层有序后再依次往堆顶走
void sift_down(int arr[],int size,int i){
    while(2*i+1<size){
        int bigger=2*i+1;
        if(2*i+2<size&&arr[2*i+2]>arr[bigger])
        bigger=2*i+2;
        if(arr[i]>=arr[bigger]) break;
        int temp=arr[i];
        arr[i]=arr[bigger];
        arr[bigger]=temp;
        i=bigger;
    }
}
//先建堆，堆虽然父子之间是有序的，但是存在数组里面两个相邻的兄弟不一定有序，所有需要循环取堆顶值放的到数组末尾
void heap_sort(int arr[],int n){
    for(int i=n/2-1;i>=0;i--) sift_down(arr,n,i);
    for(int end=n-1;end>0;end--){
        int temp=arr[end];
        arr[end]=arr[0];
        arr[0]=temp;
        sift_down(arr,end,0);
    }
}
int main(void){
    int arr[]={8,5,3,78,22,1,4,0,2,6};
    printf("排序前：");
    for(int i=0;i<10;i++) printf("%d ",arr[i]);
    heap_sort(arr,10);
    printf("\n排序后：");
    for(int i=0;i<10;i++) printf("%d ",arr[i]);
    return 0;
}