#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct Stack{
    int data;
    struct Stack* next;
}Stack;

void init_stack(Stack** S){
    *S=(Stack*)malloc(sizeof(Stack));
    if(!*S)return;
    (*S)->next=NULL;
}

bool is_empty(Stack* S){
    return S->next==NULL;
}

void push(Stack* S,int e){
    Stack* new_node=(Stack*)malloc(sizeof(Stack));
    if(!new_node)return;
    new_node->data=e;
    new_node->next=S->next;
    S->next=new_node;
}

int pop(Stack* S){
    if(is_empty(S)) return -99999;
    Stack* del=S->next;
    int e=del->data;
    S->next=del->next;
    free(del);
    return e;
}