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

void inorder(Tree* T){
    if(!T)return;
    inorder(T->lchild);
    printf("%d ",T->e);
    inorder(T->rchild);
}

//与前序重构一样的方法，只是是镜像的
Tree* rebuild(int post[],int posL,int posR,int in[],int inL,int inR){
    if(posL>posR)return NULL;
    Tree* root=create_node(post[posR]);
    int k;
    for(k=inL;k<=inR;k++)if(in[k]==post[posR])break;
    int rightLen=inR-k;
    root->lchild=rebuild(post,posL,posR-rightLen-1,in,inL,k-1);
    root->rchild=rebuild(post,posR-rightLen,posR-1,in,k+1,inR);
    return root;
}

int main(void){
    //中序：8 4 9 11 2 10 5 1 6 3 7
    //后序：8 11 9 4 10 5 2 6 7 3 1
    int in[11]={8,4,9,11,2,10,5,1,6,3,7};
    int post[11]={8,11,9,4,10,5,2,6,7,3,1};
    Tree* root=rebuild(post,0,10,in,0,10);
    inorder(root);
    return 0;
}