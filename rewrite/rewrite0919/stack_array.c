#include<stdio.h>
#include<stdbool.h>

typedef struct Stack{
    int data[10];
    int top;
}Stack;

void init_stack(Stack* S){S->top=0;}

bool is_empty(Stack* S){return S->top==0;}

void push(Stack* S,int e){
    S->data[S->top++]=e;
}

int pop(Stack* S){
    if(is_empty(S)) return -9999;
    return S->data[--S->top]; 
}