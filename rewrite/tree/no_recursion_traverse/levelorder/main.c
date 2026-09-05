#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int ElemType;

typedef struct Tree{
    ElemType e;
    struct Tree *lchild,*rchild;
}Tree;

typedef struct Queue{
    Tree* T;
    struct Queue* next;
}Queue,*QueuePtr;

typedef struct{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

void init_queue(LinkQueue* Q){
    Q->front=Q->rear=(Queue*)malloc(sizeof(Queue));
    if(!Q->front)exit(EXIT_FAILURE);
    Q->front->next=Q->rear->next=NULL;
}

bool is_empty(LinkQueue Q){
    return Q.front==Q.rear;
}

void into_queue(LinkQueue* Q,Tree* T){
    QueuePtr new_node=(QueuePtr)malloc(sizeof(Queue));
    if(!new_node)return;
    new_node->T=T;
    new_node->next=NULL;
    Q->rear->next=new_node;
    Q->rear=new_node;
}

Tree* out_queue(LinkQueue* Q){
    if(is_empty(*Q))return NULL;
    QueuePtr del=Q->front->next;
    Tree* t=del->T;
    Q->front->next=del->next;
    if(!del->next)Q->rear=Q->front;
    return t;
}

Tree* create_node(ElemType e){
    Tree* new_node=(Tree*)malloc(sizeof(Tree));
    if(!new_node)return NULL;
    new_node->e=e;
    new_node->lchild=new_node->rchild=NULL;
    return new_node;
}

void levelorder(Tree* T){
    LinkQueue Q;
    init_queue(&Q);
    into_queue(&Q,T);
    while(!is_empty(Q)){
        Tree* p=out_queue(&Q);
        printf("%d ",p->e);
        if(p->lchild)into_queue(&Q,p->lchild);
        if(p->rchild)into_queue(&Q,p->rchild);
    }
}

int main(void){
    Tree* n1=create_node(1);
    Tree* n2=create_node(2);
    Tree* n3=create_node(3);
    n1->lchild=n2;
    n1->rchild=n3;
    Tree* n4=create_node(4);
    Tree* n5=create_node(5);
    n2->lchild=n4;
    n2->rchild=n5;
    Tree* n6=create_node(6);
    Tree* n7=create_node(7);
    n3->lchild=n6;
    n3->rchild=n7;
    Tree* n8=create_node(8);
    Tree* n9=create_node(9);
    n4->lchild=n8;
    n4->rchild=n9;
    Tree* n10=create_node(10);
    n5->lchild=n10;
    Tree* n11=create_node(11);
    n9->rchild=n11;
    levelorder(n1);
    return 0;
}