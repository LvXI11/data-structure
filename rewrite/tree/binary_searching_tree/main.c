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
    if(T->e>e)T->lchild=insert(T->lchild,e);
    else if(T->e<e)T->rchild=insert(T->rchild,e);
    else return T;
    return T;
}

void search(Tree* T,ElemType e,Tree** rec){
    if(!T)return;
    if(T->e==e){
        *rec=T;
        return;
    }
    else if(T->e>e)search(T->lchild,e,rec);
    else search(T->rchild,e,rec);
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

Tree* delete(Tree* T,ElemType e){
    if(!T)return NULL;

    if(T->e>e){T->lchild=delete(T->lchild,e);return T;};
    if(T->e<e){T->rchild=delete(T->rchild,e);return T;};

    if(!T->lchild&&!T->rchild){
        free(T);
        return NULL;
    }

    if(!T->rchild){Tree* left=T->lchild;free(T);return left;};
    if(!T->lchild){Tree* right=T->rchild;free(T);return right;};

    Tree* succ=find_min(T->rchild);
    T->e=succ->e;
    T->rchild=delete(T->rchild,succ->e);
    return T;
}

int main(void){
    Tree* root=NULL;
    Tree* rec=NULL;
    int arr[] = {5,3,8,1,4,6,9};
    for(int i=0;i<7;i++)root=insert(root,arr[i]);

    inorder(root);

    search(root,5,&rec);
    if(rec)printf("找到了%d\n",rec->e);
    else printf("未找到\n");
    rec=NULL;
    search(root,2,&rec);
    if(rec)printf("找到了%d\n",rec->e);
    else printf("未找到\n");
    delete(root,3);
    inorder(root);
    printf("\n");
    delete(root,9);
    inorder(root);
    return 0;
}