#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
typedef int ElemType;

typedef struct Queue{
    ElemType e;
    struct Queue* next;
}Queue,*QueuePtr;

typedef struct {
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

void init_queue(LinkQueue* Q){
    Q->front=Q->rear=(QueuePtr)malloc(sizeof(Queue));
    if(!Q->front){
        printf("内存分配失败\n");
        exit(EXIT_FAILURE);
    }
    Q->front->next=NULL;
}
void destroy_queue(LinkQueue* Q){
    QueuePtr q=Q->front;
    while(q){
        QueuePtr del=q;
        q=q->next;
        free(del);
    }
    Q->front=Q->rear=NULL;
}
bool is_empty(LinkQueue Q){
    return Q.front->next==NULL;
}
bool into_queue(LinkQueue* Q,ElemType e){
    QueuePtr new_node=(QueuePtr)malloc(sizeof(Queue));
    if(!new_node)return false;
    new_node->e=e;
    new_node->next=NULL;
    Q->rear->next=new_node;
    Q->rear=new_node;
    return true;
}
bool out_queue(LinkQueue* Q,ElemType* e){
    if(is_empty(*Q))return false;
    QueuePtr del=Q->front->next;
    *e=del->e;
    if(!del->next)Q->rear=Q->front;
    Q->front->next=Q->front->next->next;
    free(del);
    return true;
}
void print_queue(LinkQueue Q){
    if(is_empty(Q)){
        printf("空队\n");
        return;
    }
    QueuePtr q=Q.front->next;
    printf("front ");
    while(q){
        printf("%d ",q->e);
        q=q->next;
    }
    printf("rear\n");
}
int main(void){
    LinkQueue Q;
    init_queue(&Q);
    //预期输出1 2 3 4 5
    into_queue(&Q,1);
    into_queue(&Q,2);
    into_queue(&Q,3);
    into_queue(&Q,4);
    into_queue(&Q,5);
    print_queue(Q);
    //预期输出1 2 3 4 5
    ElemType value;
    if(out_queue(&Q,&value))printf("out's value:%d\n",value);
    else printf("out failed\n");
    if(out_queue(&Q,&value))printf("out's value:%d\n",value);
    else printf("out failed\n");
    if(out_queue(&Q,&value))printf("out's value:%d\n",value);
    else printf("out failed\n");
    if(out_queue(&Q,&value))printf("out's value:%d\n",value);
    else printf("out failed\n");
    if(out_queue(&Q,&value))printf("out's value:%d\n",value);
    else printf("out failed\n");
    destroy_queue(&Q);
    printf("队列已销毁\n");
    return 0;
}