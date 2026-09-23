#include<stdlib.h>
#include<stdio.h>
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

Tree* create_node(ElemType e){
    Tree* t=(Tree*)malloc(sizeof(Tree));
    if(!t)return NULL;
    t->e=e;
    t->lchild=t->rchild=NULL;
    return t;
}

void init_stack(Stack** S){
    *S=(Stack*)malloc(sizeof(Stack));
    if(!*S){
        printf("内存分配失败\n");
        exit(EXIT_FAILURE);
    }
    (*S)->next=NULL;
}

bool stack_is_empty(Stack* S){
    return S->next==NULL;
}

bool push_elem(Stack* S, Tree* node){
    Stack* new_node=(Stack*)malloc(sizeof(Stack));
    if(!new_node)return false;
    new_node->node=node;
    new_node->next=S->next;
    S->next=new_node;
    return true;
}

Tree* pop_elem(Stack* S){
    if(stack_is_empty(S))return NULL;
    Stack* del=S->next;
    Tree* node=del->node;
    S->next=S->next->next;
    free(del);
    return node;
}

void inorder(Tree* T){
    Stack* S;
    init_stack(&S);
    Tree* p=T;
    while(p || !stack_is_empty(S)){
        if(p){
            push_elem(S, p);
            p=p->lchild;
        }
        else{
            p=pop_elem(S);
            printf("%d ", p->e);
            p=p->rchild;
        }
    }
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
    inorder(n1);
// 前序：1 2 4 8 9 11 5 10 3 6 7
// 中序：8 4 9 11 2 10 5 1 6 3 7
// 后序：8 11 9 4 10 5 2 6 7 3 1
    return 0;
}