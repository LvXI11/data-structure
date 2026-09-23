#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int ElemType;
typedef struct Tree{
    ElemType e;
    struct Tree *lchild,*rchild;
}Tree;

Tree* create_node(ElemType e){
    Tree* t=(Tree*)malloc(sizeof(Tree));
    if(!t)return NULL;
    t->e=e;
    t->lchild=t->rchild=NULL;
    return t;
}
void preorder(Tree* T){
    if(T==NULL)return;
    printf("%d ",T->e);
    preorder(T->lchild);
    preorder(T->rchild);
}

void inorder(Tree* T){
    if(!T)return;
    inorder(T->lchild);
    printf("%d ",T->e);
    inorder(T->rchild);
}
void postorder(Tree* T){
    if(!T)return;
    postorder(T->lchild);
    postorder(T->rchild);
    printf("%d ",T->e);
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
    printf("前序：");
    preorder(n1);
    printf("\n");
    printf("中序：");
    inorder(n1);
    printf("\n");
    printf("后序：");
    postorder(n1);
// 前序：1 2 4 8 9 11 5 10 3 6 7
// 中序：8 4 9 11 2 10 5 1 6 3 7
// 后序：8 11 9 4 10 5 2 6 7 3 1
    return 0;
}