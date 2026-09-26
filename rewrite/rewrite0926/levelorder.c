#include<stdio.h>
#include<stdlib.h>

typedef struct Tree{
    int e;
    struct Tree *lchild,*rchild;
}Tree;

Tree* create_node(int e){
    Tree* new_node=(Tree*)malloc(sizeof(Tree));
    if(!new_node)return NULL;
    new_node->e=e;
    new_node->lchild=new_node->rchild=NULL;
    return new_node;
}

Tree* buid_tree(Tree* T,int e){
    if(!T) return create_node(e);
    if(T->e>e) T->lchild=buid_tree(T->lchild,e);
    else if(T->e<e) T->rchild=buid_tree(T->rchild,e);
    else return T;
    return T;
}

typedef struct Queue{
    Tree* data[100];
    int front,rear;
}Queue;

void init_queue(Queue* Q) {Q->front=Q->rear=0;}
int isempty(Queue* Q) {return Q->rear==Q->front;}
void enqueue(Queue* Q,Tree* t) {Q->data[Q->rear]=t; Q->rear=(Q->rear+1)%100;}

Tree* dequeue(Queue* Q) {if(isempty(Q)) return NULL;
    Tree* out=Q->data[Q->front];
    Q->front=(Q->front+1)%100; return out;}

void level_order(Tree* T){
    Queue Q;
    init_queue(&Q);
    enqueue(&Q,T);
    while(!isempty(&Q)){
        Tree* p=dequeue(&Q);
        printf("%d ",p->e);
        if(p->lchild) enqueue(&Q,p->lchild);
        if(p->rchild) enqueue(&Q,p->rchild);
    }
}