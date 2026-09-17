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

void preorder(Tree* T){
    if(!T)return;
    printf("%d ",T->e);
    preorder(T->lchild);
    preorder(T->rchild);
}

//判空条件为遍历完前序数组
//前序数组的首元素为root直接create_node
//找头root在中序中的位置，左边为左子树，右边为右子树，循环获取左子树的个数用于下次递归
//调用函数自身重构左右子树

//递归函数的核心是只看当前节点，不往后看，自身+调用函数获取子树(信任递归)
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
int main(void){
    //前序：1 2 4 8 9 11 5 10 3 6 7
    //中序：8 4 9 11 2 10 5 1 6 3 7
    int pre[11]={1,2,4,8,9,11,5,10,3,6,7};
    int in[11]={8,4,9,11,2,10,5,1,6,3,7};
    Tree* root=rebuild(pre,0,10,in,0,10);
    preorder(root);
    return 0;
}