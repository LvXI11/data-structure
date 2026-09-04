#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define MAX_LEN 50
typedef int ElemTpye;

typedef struct Tree{
    ElemTpye e;
    struct Tree *lchild,*rchild;
}Tree,*TreePtr;

typedef struct Queue{
    TreePtr* elem;
    int front,rear;
}Queue;

void init_queue(Queue* Q){
    Q->elem=(Tree**)malloc(MAX_LEN*sizeof(Tree*));
    if(!Q->elem)exit(EXIT_FAILURE);
    Q->front=Q->rear=0;
}

bool is_empty(Queue Q){
    return Q.front==Q.rear;
}

bool is_full(Queue Q){
    return (Q.rear+1)%MAX_LEN==Q.front;
}

void into_queue(Queue* Q,Tree* T){
    if(is_full(*Q))return;
    Q->elem[Q->rear]=T;
    Q->rear=(Q->rear+1)%MAX_LEN;
}

Tree* out_queue(Queue*Q){
    if(is_empty(*Q))return NULL;
    Tree* t=Q->elem[Q->front];
    Q->front=(Q->front+1)%MAX_LEN;
    return t;
}

Tree* create_node(ElemTpye e){
    Tree* new_node=(Tree*)malloc(sizeof(Tree));
    if(!new_node)return NULL;
    new_node->e=e;
    new_node->lchild=new_node->rchild=NULL;
    return new_node;
}

void levelorder(Tree* T){
    Queue Q;
    init_queue(&Q);
    into_queue(&Q,T);
    while(!is_empty(Q)){
        Tree* q=out_queue(&Q);
        printf("%d ",q->e);
        if(q->lchild)into_queue(&Q,q->lchild);
        if(q->rchild)into_queue(&Q,q->rchild);
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