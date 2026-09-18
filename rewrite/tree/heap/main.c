#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
                       //小根堆
typedef struct Heap{
    int data[100];
    int size;
}Heap;

void sift_up(Heap* H,int elem){
    H->data[H->size++]=elem;
    int i=H->size-1;
    while(i>0&&H->data[i]<H->data[(i-1)/2]){
        int temp=H->data[i];
        H->data[i]=H->data[(i-1)/2];
        H->data[(i-1)/2]=temp;
        i=(i-1)/2;
    }
}

void sift_down(Heap* H){
    int i=0;
    while(2*i+1<H->size){
        int smaller=2*i+1;
        if(2*i+2<H->size&&H->data[2*i+2]<H->data[2*i+1])smaller=2*i+2;
        if(H->data[i]<H->data[smaller])break;
        int temp=H->data[i];
        H->data[i]=H->data[smaller];
        H->data[smaller]=temp;
        i=smaller;
    }
}

int pop_min(Heap* H){
    int min=H->data[0];
    H->data[0]=H->data[H->size-1];
    H->size--;
    sift_down(H);
    return min;
}

void print_heap(Heap* H){
    for(int i=0;i<H->size;i++) printf("%d ",H->data[i]);
    printf("\n");
}

int main(void){
    Heap H;
    H.size=0;
    sift_up(&H,5);
    sift_up(&H,90);
    sift_up(&H,23);
    sift_up(&H,0);
    sift_up(&H,-8);
    sift_up(&H,4);
    sift_up(&H,15);
    print_heap(&H);

    pop_min(&H);
    print_heap(&H);

    pop_min(&H);
    print_heap(&H);
    return 0;
}