#include<stdio.h>
#include<stdbool.h>
#define MAXL 100
typedef struct Queue{
    int data[MAXL];
    int front,rear;
}Queue;

void init_queue(Queue* Q){
    Q->front=Q->rear=0;
}

bool is_empty(Queue* Q){
    return Q->front==Q->rear;
}

bool is_full(Queue* Q){
    return (Q->rear+1)%MAXL==Q->front;
}

void enqueue(Queue* Q,int e){
    if(is_full(Q))return;
    Q->data[Q->rear]=e;
    Q->rear=(Q->rear+1)%MAXL;
}

void dequeue(Queue* Q,int* rec){
    if(is_empty(Q))return;
    *rec=Q->data[Q->front];
    Q->front=(Q->front+1)%MAXL;
}

int get_len(Queue* Q){
    return (Q->rear-Q->front+MAXL)%MAXL;
}