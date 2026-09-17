#include<stdio.h>
#include<stdbool.h>

typedef int ElemType;
typedef struct Tree{
    ElemType e;
    struct Tree *lchild,*rchild;
}Tree;

typedef struct Queue{
    Tree* node;
    struct Queue* next;
}Queue,*QueuePtr;

typedef struct QList{
    QueuePtr front;
    QueuePtr rear;
}QList;

void init_queue(QList** Q){

}

void into_elem(QList* Q,Tree* T){

}

Queue* out_elem(QList* Q){

}

bool is_empty(QList* Q){

}

void levelorder(Tree* T){
    QList* Q;
    init_queue(&Q);
    into_elem(Q,T);
    while(!is_empty(Q)){
        Queue* p=out_elem(Q);
        printf("%d ",p->node->e);
        if(p->node->lchild) into_elem(Q,p->node->lchild);
        if(p->node->rchild) into_elem(Q,p->node->rchild);
    }
}
