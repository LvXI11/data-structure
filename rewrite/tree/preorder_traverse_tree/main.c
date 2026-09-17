#include<stdio.h>

void preorder(Tree* T){
    printf("%d ",T->e);
    preorder(T->lchild);
    preorder(T->rchild);
}
