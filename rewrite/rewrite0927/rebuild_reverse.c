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

void preorder(Tree* T){
    if(!T) return;
    printf("%d ",T->e);
    preorder(T->lchild);
    preorder(T->rchild);
}

void inorder(Tree* T){
    if(!T) return;
    inorder(T->lchild);
    printf("%d ",T->e);
    inorder(T->rchild);
}

Tree* rebuild_tree(int pre[],int prl,int prr,int in[],int inl,int inr){
    if(prl>prr)return NULL;
    Tree* root=create_node(pre[prl]);
    int k;
    for(k=inl;k<=inr;k++) if(in[k]==root->e) break;
    int leftLen=k-inl;
    root->lchild=rebuild_tree(pre,prl+1,prl+leftLen,in,inl,k-1);
    root->rchild=rebuild_tree(pre,prl+leftLen+1,prr,in,k+1,inr);
    return root;
}

void reverse_tree(Tree* T){
    if(!T)return;
    else{
        Tree* temp=T->lchild;
        T->lchild=T->rchild;
        T->rchild=temp;
        reverse_tree(T->lchild);
        reverse_tree(T->rchild);
    }
}
