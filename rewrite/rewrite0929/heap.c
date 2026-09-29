#include<stdio.h>
#define MAXLEN 100

typedef struct Heap{
    int data[MAXLEN];
    int size;
}Heap;

void init_heap(Heap* H) {H->size=0;}

void sift_up(Heap* H,int e){
    H->data[H->size++]=e;
    int i=H->size-1;
    while(i>0&&H->data[i]<H->data[(i-1)/2]){
        int temp=H->data[i];
        H->data[i]=H->data[(i-1)/2];
        H->data[(i-1)/2]=temp;
        i=(i-1)/2;
    }
}

void sift_down(int arr[],int size,int i){
    while(2*i+1<size){
        int small=2*i+1;
        if(2*i+2<size&&arr[2*i+2]<arr[small])
        small=2*i+2;
        if(arr[i]<arr[small]) break;
        int temp=arr[i];
        arr[i]=arr[small];
        arr[small]=temp;
        i=small;
    }
}

int heap_empty(Heap* H) {return H->size==0;}

int delete_node(Heap* H,int e){
    if(heap_empty(H)) return 99999;
    int out=H->data[0];
    H->data[0]=H->data[H->size-1];
    H->size--;
    sift_down(H->data,H->size,0);
    return out;
}

void build_heap(int arr[],int n){
    for(int i=n/2-1;i>=0;i--)
    sift_down(arr,n,i);
}

void heap_sort(int arr[],int n){
    build_heap(arr,n);
    for(int end=n-1;end>0;end--){
        int temp=arr[end];
        arr[end]=arr[0];
        arr[0]=temp;
        sift_down(arr,end,0);
    }
}