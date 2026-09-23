#include<stdio.h>

typedef struct Heap{
    int data[100];
    int size;
}Heap;

void sift_up(Heap* H,int elem){
    H->data[H->size++]=elem;
    int i=H->size-1;
    while(i>0&&H->data[i]>H->data[(i-1)/2]){
        int temp=H->data[i];
        H->data[i]=H->data[(i-1)/2];
        H->data[(i-1)/2]=temp;
        i=(i-1)/2;
    }
}

void sift_down(Heap* H){
    int i=0;
    while(2*i+1<H->size){
        int bigger=2*i+1;
        if(2*i+2<H->size&&H->data[2*i+2]>H->data[bigger])bigger=2*i+2;
        if(H->data[i]>H->data[bigger])break;
        int temp=H->data[bigger];
        H->data[bigger]=H->data[i];
        H->data[i]=temp;
        i=bigger;
    }
}

int pop_elem(Heap* H){
    int del=H->data[0];
    H->data[0]=H->data[H->size-1];
    H->size--;
    sift_down(H);
    return del;
}

void print_heap(Heap* H){
    for(int i=0;i<H->size;i++) printf("%d ",H->data[i]);
    printf("\n");
}

int main(void){
    Heap H;
    H.size=0;
    sift_up(&H,5);
    sift_up(&H,87);
    sift_up(&H,3);
    sift_up(&H,8);
    sift_up(&H,1);
    sift_up(&H,98);
    sift_up(&H,-2);
    print_heap(&H);

    pop_elem(&H);
    print_heap(&H);

    pop_elem(&H);
    print_heap(&H);

    return 0;
}