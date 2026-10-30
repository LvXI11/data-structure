#include<stdio.h>
#include<stdlib.h>
#define MAX 100

typedef struct Stack{
    int data[MAX];
    int top;
}Stack;

void init_stack(Stack* S) { S->top = -1; }

void push(Stack* S,int val) { S->data[++S->top] = val; };

int empty(Stack* S) { return S->top == -1; }

int pop(Stack* S) {
   return S->data[S->top--];
}

int dequeue(Stack* QS, Stack* S) {
    if(empty(QS)) {
        while(!empty(S)) {
            push(QS, pop(S));
        }
    }
    return QS->data[QS->top--];
}