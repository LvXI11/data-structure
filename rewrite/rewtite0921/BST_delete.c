#include<stdio.h>

typedef struct Tree{
    int e;
    struct Tree *lchild,*rchild;
}Tree;

Tree* get_min(Tree* T){
    while(T->lchild)T=T->lchild;
    return T;
}
Tree* delete_node(Tree* T,int e){
    if(!T)return;
    if(T->e>e) {T->lchild=delete_node(T->lchild,e); return T;}
    else if(T->e<e) {T->rchild=delete_node(T->rchild,e); return T;}

    if(!T->lchild&&!T->rchild){
        free(T);
        return NULL;
    }

    if(!T->lchild) {Tree* right=T->rchild;free(T);return right;}
    if(!T->rchild) {Tree* left=T->lchild;free(T);return left;}

    Tree* succ=get_min(T->rchild);
    T->e=succ->e;
    T->rchild=delete_node(T->rchild,succ->e);
    return T;
}