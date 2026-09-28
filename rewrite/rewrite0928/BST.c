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
    if(T->e>e) T->lchild=build_tree(T->lchild,e);
    else if(T->e<e) T->rchild=build_tree(T->rchild,e);
    else return T;
    return T;
}

Tree* search(Tree* T,int e){
    if(!T) return NULL;
    if(T->e==e){
        printf("找到了%d\n",e);
        return T;
    }
    else{
        if(T->e>e) return search(T->lchild,e);
        else return search(T->rchild,e);
    }
}

Tree* get_min(Tree* T){
    while(T->lchild) T=T->lchild;
    return T;
}

Tree* delete_node(Tree* T,int e){
    if(!T) return NULL;
    if(T->e>e) {T->lchild=delete_node(T->lchild,e); return T;}
    if(T->e<e) {T->rchild=delete_node(T->rchild,e); return T;}

    if(!T->lchild&&!T->rchild) {free(T); return NULL;}

    if(!T->lchild) {Tree* right=T->rchild; free(T); return right;}
    if(!T->rchild) {Tree* left=T->lchild; free(T); return left;}

    Tree* succ=get_min(T->rchild);
    T->e=succ->e;
    T->rchild=delete_node(T->rchild,succ->e);
    return T;
}