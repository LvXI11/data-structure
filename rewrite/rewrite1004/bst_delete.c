#include<stdio.h>
#include<stdlib.h>

typedef struct Tree{
    int e;
    struct Tree *lchild,*rchild;
}Tree;

Tree* create_node(int e){
    Tree* new_node=(Tree*)malloc(sizeof(Tree));
    if(!new_node) return NULL;
    new_node->e=e;
    new_node->lchild=new_node->rchild=NULL;
    return new_node;
}

Tree* build_tree(Tree* T,int e){
    if(!T) return create_node(e);
    if(T->e>e)  T->lchild=build_tree(T->lchild,e);
    if(T->e<e) T->rchild=build_tree(T->rchild,e);
    if(T->e==e) return T;
    return T; 
}

Tree* get_min(Tree* T){
    while(T->rchild) T=T->rchild;
    return T;
}

Tree* delete_node(Tree* T,int e){
    if(!T) return NULL;
    if(T->e>e) {T->lchild=delete_node(T->lchild,e); return T;}
    if(T->e<e) {T->rchild=delete_node(T->rchild,e); return T;}

    if(!T->lchild&&!T->rchild) {free(T); return NULL;}

    if(!T->lchild) {Tree* right=T->rchild; free(T); return right;}
    if(!T->rchild) {Tree* left=T->lchild; free(T); return left;}

    Tree* succ=get_min(T->lchild);
    T->e=succ->e;
    T->lchild=delete_node(T->lchild,succ->e);
    return T;
}