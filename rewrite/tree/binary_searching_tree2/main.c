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

    //insert和search两个函数的返回值不一样：insert需要把新挂上去的节点返回给双亲；而search函数只需要找到对应的值就行
    //这两个函数的本质都是判断节点本身+调用自己的函数去判断子树节点
void search(Tree* T,ElemType e,Tree** rec){
    if(!T)return;
    if(T->e==e){
        *rec=T;
        return;
    }
    else if(T->e>e)search(T->lchild,e,rec);
    else search(T->rchild,e,rec);
}
    //delete函数分三种情况
    //1.删除节点是叶子节点，直接删除返回NULL，因为删除后会返回指针给双亲
    //2.删除节点只有一个孩子时，判断是哪个孩子，几下那个孩子的地址，等删除完之后，返回给双亲
    //3.删除节点有两个孩子的时候，需要找最小的节点的元素值放到被删节点的位置，
    //实际上没有删，然后删除最小元素的节点（借尸还魂）

Tree* get_min(Tree* T){
    while(T->lchild)T=T->lchild;
    return T;
}

Tree* delete_node(Tree* T,ElemType e){
    if(!T)return NULL;
    if(T->e>e){T->lchild=delete_node(T->lchild,e);return T;};
    if(T->e<e){T->rchild=delete_node(T->rchild,e);return T;};

    if(!T->lchild&&!T->rchild){
        free(T);
        return NULL;
    }

    if(!T->lchild){Tree* right=T->rchild;free(T);return right;};
    if(!T->rchild){Tree* left=T->lchild;free(T);return left;};

    Tree* succ=get_min(T->rchild);
    T->e=succ->e;
    T->rchild=delete_node(T->rchild,succ->e);
    return T;
}

void inorder(Tree* T){
    if(!T)return;
    inorder(T->lchild);
    printf("%d ",T->e);
    inorder(T->rchild);
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
    delete_node(root,3);
    inorder(root);
    printf("\n");
    delete_node(root,9);
    inorder(root);
    return 0;
}