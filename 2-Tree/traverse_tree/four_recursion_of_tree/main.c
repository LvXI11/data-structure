#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int ElemType;

typedef struct Tree{
    ElemType e;
    struct Tree *lchild,*rchild;
}Tree;

typedef struct Stack{
    Tree* node;
    struct Stack* next;
}Stack;

void init_stack(Stack** S){
    *S=(Stack*)malloc(sizeof(Stack));
    if(!*S)exit(EXIT_FAILURE);
    (*S)->next=NULL;
}

bool is_empty(Stack* S){
    return S->next==NULL;
}

void push_elem(Stack* S,Tree* T){
    Stack* new_node=(Stack*)malloc(sizeof(Stack));
    if(!new_node)return;
    new_node->node=T;
    new_node->next=S->next;
    S->next=new_node;
}

Tree* pop_elem(Stack* S){
    if(is_empty(S))return NULL;
    Stack* del=S->next;
    Tree* t=del->node;
    S->next=S->next->next;
    free(del);
    return t;
}

Tree* create_node(ElemType e){
    Tree* new_node=(Tree*)malloc(sizeof(Tree));
    if(!new_node)return NULL;
    new_node->e=e;
    new_node->lchild=new_node->rchild=NULL;
    return new_node;
}

int count_node(Tree* T){
    if(!T)return 0;
    return 1+count_node(T->lchild)+count_node(T->rchild);
}

int get_height(Tree* T){
    if(!T)return 0;
    int lh=get_height(T->lchild);
    int rh=get_height(T->rchild);
    return 1+(lh>rh?lh:rh);
}

int leves_count(Tree* T){
    if(!T)return 0;
    if(T->lchild==NULL&&T->rchild==NULL)return 1;
    return leves_count(T->lchild)+leves_count(T->rchild);
}
int count_even(Tree* T){
    if(!T)return 0;
    return (T->e%2==0)+count_even(T->lchild)+count_even(T->rchild);
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
    printf("nodes count:%d\n",count_node(n1));
    printf("tree's height:%d\n",get_height(n1));
    printf("tree's leves:%d\n",leves_count(n1));
    printf("even count:%d\n",count_even(n1));
    return 0;
}