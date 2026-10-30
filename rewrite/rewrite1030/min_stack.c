#include<stdio.h>
#define MAX 100

typedef struct Stack{
    int data[MAX];
    int top;
}Stack;

void init(Stack* S, Stack* minS) {
    S->top = -1;
    minS->top = -1;
}

int empty(Stack* S) { return S->top == -1; }

void push(Stack* S, Stack* minS, int val) {
    S->data[++S->top] = val;
    if(empty(minS)) {
        minS->data[++(minS->top)] = val;
    } else {
        if(val < minS->data[minS->top]) {
            minS->data[++(minS->top)] = val;
        } else {
            minS->data[minS->top + 1] = minS->data[minS->top];
            minS->top++;
        }
    }
}

void pop(Stack* S, Stack* minS) {
    S->top--;
    minS->top--;
}

int get_min(Stack* minS) {
    return minS->data[minS->top];
}
int top(Stack* S) { return S->data[S->top]; }

int main(void) {
    Stack S;
    Stack minS;
    init(&S, &minS);

    push(&S, &minS, -2); push(&S, &minS, 0); push(&S, &minS, -3);
    printf("push -2, 0, -3\n");

    printf("getMin -> %d\n", get_min(&minS));

    pop(&S, &minS);
    printf("pop\n");

    printf("top    -> %d\n", top(&S));
    printf("getMin -> %d\n", get_min(&minS));

    return 0;
}