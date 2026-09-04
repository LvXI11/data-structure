#include<stdio.h>
#include<stdlib.h>
#include<Stdbool.h>
typedef int ElemType;
typedef struct Queue{
    ElemType e;
    struct Queue* next;
}Queue,*QueuePtr;
typedef struct{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;//相当于"head"
void init_queue(LinkQueue* Q){
    Q->front=Q->rear=(QueuePtr)malloc(sizeof(Queue));
    if(!Q->front){
        printf("内存分配失败\n");
        exit(EXIT_FAILURE);
    }
    Q->front->next=NULL;
}
void destroy_queue(LinkQueue* Q){
    QueuePtr p=Q->front;
    while(p){
        QueuePtr del=p;
        p=p->next;
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
bool out_queue(LinkQueue* Q,ElemType* value){
    if(is_empty(*Q))return false;
    QueuePtr del=Q->front->next;
    *value=del->e;
    Q->front->next=del->next;
    if(Q->rear==del)Q->rear=Q->front;
    free(del);
    return true;
}
void print_queue(LinkQueue Q){
    if(is_empty(Q)){
        printf("空队\n");
        return;
    }
    printf("front ");
    QueuePtr p=Q.front->next;
    while(p){
        printf("%d ",p->e);
        p=p->next;
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

    //预期输出3 4 5
    ElemType value;
    if(out_queue(&Q,&value))printf("out's value:%d\n",value);
    if(out_queue(&Q,&value))printf("out's value:%d\n",value);

    print_queue(Q);
    destroy_queue(&Q);
    printf("链队已销毁\n");
    return 0;
}