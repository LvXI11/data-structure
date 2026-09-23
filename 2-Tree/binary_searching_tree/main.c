#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

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

Tree* insert(Tree* T,ElemType e){
    if(!T)return create_node(e);
    if(T->e>e) T->lchild=insert(T->lchild,e);
    else if(T->e<e) T->rchild=insert(T->rchild,e);
    else return T;
    return T;
}

void search(Tree* T,ElemType e,Tree** rec){
    if(!T)return;
    if(T->e==e){
        *rec=T;
        return;
    }
    else if(T->e>e) search(T->lchild,e,rec);
    else search(T->rchild,e,rec);
}

void preorder(Tree* T){
    if(!T)return;
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

Tree* find_min(Tree* T){
    while(T->lchild)T=T->lchild;
    return T;
}

Tree* delete_child(Tree* T,ElemType e){
    if(!T)return NULL;
    if(T->e>e){T->lchild=delete_child(T->lchild,e);return T;}; 
    if(T->e<e){T->rchild=delete_child(T->rchild,e);return T;};

    if(!T->lchild&&!T->rchild){
        free(T);
        return NULL;
    }

    if(!T->lchild){Tree* right=T->rchild;free(T);return right;};
    if(!T->rchild){Tree* left=T->lchild;free(T);return left;};

    Tree* succ=find_min(T->rchild);
    T->e=succ->e;
    T->rchild=delete_child(T->rchild,succ->e);
    return T;
    
}

int main(void){
    Tree* rec=NULL;
    Tree* root=NULL;
    int arr[] = {5,3,8,1,4,6,9};
    for(int i=0;i<7;i++) root=insert(root,arr[i]);
    printf("先序：");
    preorder(root);
    printf("\n");
    printf("中序：");
    inorder(root);
    search(root,6,&rec);
    if(rec)printf("\n找到了%d\n",rec->e);
    else printf(" \n未找到\n");

    rec=NULL;
    search(root,2,&rec);
    if(rec)printf("\n找到了%d\n",rec->e);
    else printf(" 未找到\n");

    delete_child(root,3);
    inorder(root);
    delete_child(root,8);
    printf("\n");
    inorder(root);
    return 0;
}