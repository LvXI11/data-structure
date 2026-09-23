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

bool is_empty(Stack S){
    return S.next==NULL;
}

void push_elem(Stack* S,Tree* T){
    Stack* new_node=(Stack*)malloc(sizeof(Stack));
    if(!new_node)return;
    new_node->node=T;
    new_node->next=S->next;
    S->next=new_node;
}

Tree* pop_elem(Stack* S){
    if(is_empty(*S))return NULL;
    Stack* del=S->next;
    Tree* t=del->node;
    S->next=del->next;
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

void preorder(Tree* T){
    Stack* S;
    init_stack(&S);
    Tree* p=T;
    while(p||!is_empty(*S)){
        if(p){
            printf("%d ",p->e);
            push_elem(S,p);
            p=p->lchild;
        }
        else{
            p=pop_elem(S);
            p=p->rchild;
        }
    }
}

void reverse_child(Tree* T){
    if(!T)return;
    else{
        Tree* temp=T->lchild;
        T->lchild=T->rchild;
        T->rchild=temp;
        reverse_child(T->lchild);
        reverse_child(T->rchild);
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
    printf("before reversing:");
    preorder(n1);
    //前序：1 2 4 8 9 11 5 10 3 6 7
    reverse_child(n1);
    printf("\n");
    printf("after reversing:");
    preorder(n1);
    //翻转后：1 3 7 6 2 5 10 4 9 11 8
    return 0;
}