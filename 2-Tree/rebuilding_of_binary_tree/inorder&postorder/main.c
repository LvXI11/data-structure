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
Tree* rebuild(int post[],int posR,int posL,int in[],int inL,int inR){
    if(posR<posL)return NULL;
    Tree* root=create_node(post[posR]);
    int k;
    for(k=inL;k<=inR;k++)if(in[k]==post[posR])break;
    int rightLen=inR-k;
    root->lchild=rebuild(post,posR-rightLen-1,posL,in,inL,k-1);
    root->rchild=rebuild(post,posR-1,posR-rightLen,in,k+1,inR);
    return root;
}

void inorder(Tree* T){
    if(!T)return;
    inorder(T->lchild);
     printf("%d ",T->e);
    inorder(T->rchild);
}

int main(void){
    //中序：8 4 9 11 2 10 5 1 6 3 7
    //后序：8 11 9 4 10 5 2 6 7 3 1
    int in[11]={8,4,9,11,2,10,5,1,6,3,7};
    int post[11]={8,11,9,4,10,5,2,6,7,3,1};
    Tree* root=rebuild(post,10,0,in,0,10);
    inorder(root);
    return 0;
}