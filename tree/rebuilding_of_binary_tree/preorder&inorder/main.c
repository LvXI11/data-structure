#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;

typedef struct Tree{
    ElemType e;
    struct Tree *lchild,*rchild;
}Tree;

Tree* create_node(ElemType e){
    Tree* new_node=(Tree*)malloc(sizeof(Tree));
    if(!new_node)return NULL;
    new_node->e=e;
    new_node->lchild=new_node->rchild=NULL;
    return new_node;
}
Tree* rebuild(int pre[],int preL,int preR,int in[],int inL,int inR){
    if(preL>preR)return NULL;
    Tree* root=create_node(pre[preL]);
    int k;
    for(k=inL;k<=inR;k++)if(in[k]==pre[preL])break;
    int leftLen=k-inL;
    root->lchild=rebuild(pre,preL+1,preL+leftLen,in,inL,k-1);
    root->rchild=rebuild(pre,preL+leftLen+1,preR,in,k+1,inR);
    return root;
}

void preorder(Tree* T){
    if(!T)return;
    printf("%d ",T->e);
    preorder(T->lchild);
    preorder(T->rchild);
}

int main(void){
    //前序：1 2 4 8 9 11 5 10 3 6 7
    //中序：8 4 9 11 2 10 5 1 6 3 7
    int pre[11]={1,2,4,8,9,11,5,10,3,6,7};
    int in[11]={8,4,9,11,2,10,5,1,6,3,7};
    Tree* root=rebuild(pre,0,10,in,0,10);
    preorder(root);
    return 0;
}