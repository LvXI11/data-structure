#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX_LEN 5
typedef int ElemType;
typedef struct Queue{
    ElemType* elem;
    int front;
    int rear;
}Queue;
void init_queue(Queue* Q){
    Q->elem=(ElemType*)malloc(MAX_LEN*sizeof(ElemType));
    if(!Q->elem){
        printf("内存分配失败\n");
        exit(EXIT_FAILURE);
    }
    Q->front=0;
    Q->rear=0;
}
void destroy_queue(Queue* Q){
    free(Q->elem);
    Q->elem=NULL;
}
int get_len(Queue Q){
    return (Q.rear-Q.front+MAX_LEN)%MAX_LEN;
}
bool is_empty(Queue Q){
    return Q.front==Q.rear;
}
bool is_full(Queue Q){
    if((Q.rear+1)%MAX_LEN==Q.front)return true;
    else return false;
}
bool into_queue(Queue* Q,ElemType e){
    if(is_full(*Q))return false;
    Q->elem[Q->rear]=e;
    Q->rear=(Q->rear+1)%MAX_LEN;
    return true;
}
bool out_queue(Queue* Q,ElemType* e){
    if(is_empty(*Q))return false;
    *e=Q->elem[Q->front];
    Q->front=(Q->front+1)%MAX_LEN;
    return true;
}
void print_queue(Queue Q){
    if(is_empty(Q)){
        printf("空队\n");
        return;
    }
    printf("front ");
    while(Q.front!=Q.rear){
        printf("%d ",Q.elem[Q.front]);
        Q.front=(Q.front+1)%MAX_LEN;
    }
    printf("rear\n");
}
int main(void){
    Queue Q;
    init_queue(&Q);
    //预期输出 1 2 3 4 
    into_queue(&Q,1);
    into_queue(&Q,2);
    into_queue(&Q,3);
    into_queue(&Q,4);
    print_queue(Q);
    printf("队列长度:%d\n",get_len(Q));
    //预期输出3 4 5
    ElemType value;
    if(out_queue(&Q,&value))printf("out's value:%d\n",value);
    else printf("out failed\n");
    if(out_queue(&Q,&value))printf("out's value:%d\n",value);
    else printf("out failed\n");
    print_queue(Q);
    printf("队列长度:%d\n",get_len(Q));
    //预期输出3 4 5 6 7
    into_queue(&Q,6);
    into_queue(&Q,7);
    print_queue(Q);
    printf("队列长度:%d\n",get_len(Q));

    destroy_queue(&Q);
    printf("队列已销毁\n");
    return 0;
}