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

typedef struct Stack{
    Tree* data[100];
    int top;
}Stack;

void init(Stack* S) {S->top=-1;}
int  is_empty(Stack* S) {return S->top==-1;}
void push(Stack* S,Tree* t) {S->data[++S->top]=t;}
Tree* pop(Stack* S) {if(is_empty(S)) return NULL; return S->data[S->top--];}

void inoder_stack(Tree* T){
    Stack S;
    init(&S);
    Tree* p=T;
    while(p||!is_empty(&S)){
        if(p){
            push(&S,p);
            p=p->lchild;
        }
        else{
            p=pop(&S);
            printf("%d ",p->e);
            p=p->rchild;
        }
    }
}