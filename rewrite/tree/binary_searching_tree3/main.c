#include<stdio.h>

typedef int ElemType;

typedef struct Tree{
    ElemType e;
    struct Tree *lchild,*rchild;
}Tree;

Tree* create_node(ElemType e){

}

Tree* insert(Tree* T,ElemType e){
    if(!T)return create_node(T);
    if(T->e>e) T->lchild=insert(T->lchild,e);
    else if(T->e<e) T->rchild=insert(T->rchild,e);
    else return T;
    return T;
}

void serach(Tree* T,ElemType e,Tree** rec){
    if(!T)return;
    if(T->e==e){
        *rec=T;
        return;
    }
    else if(T->e>e) serach(T->lchild,e,rec);
    else serach(T->rchild,e,rec);
}

Tree* get_min(Tree* T){
    while(T->lchild) T=T->lchild;
    return T;
}
Tree* delete_node(Tree* T,ElemType e){
    if(!T) return NULL;
    if(T->e>e) {T->lchild=delete_node(T->lchild,e);return T;}
    else if(T->e<e) {T->rchild=delete_node(T->rchild,e);return T;}

    if(!T->rchild&&!T->lchild){
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
int main(void){
    Tree* T;
    
    return 0;
}