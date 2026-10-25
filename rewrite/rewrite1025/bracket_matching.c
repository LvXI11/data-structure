#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Stack{
    char* data;
    int top;
    int size;
}Stack;

void init_stack(Stack* S, int n) {
    S->size = n;
    S->data = (char*)malloc(sizeof(char) * n);
    S->top = -1;
}

void push(Stack* S, char val) {
    S->data[++S->top] = val;
}

int is_empty(Stack* S) {
    return S->top == -1;
}

bool pop(Stack* S, char* rec) {
    if(is_empty(S)) return false;
    *rec = S->data[S->top--];
    return true;
}

int main(void) {
    Stack S;
    init_stack(&S, 100);
    char ch;
    bool matched = true;
    while((ch = getchar()) != '\n' && ch != EOF) {
        if(ch == '(' || ch == '[' || ch == '{') {
            push(&S, ch);
        }else if(ch == ')' || ch == ']' || ch == '}') {
            char rec;
            bool ok = pop(&S, &rec) && ((ch == ')' && rec == '(') ||
                                       (ch == ']' && rec == '[') ||
                                       (ch == '}' && rec == '{'));
            if(!ok) {
                matched = false;
                break;
            }
        }
    }

    if(is_empty(&S) && matched) printf("合法");
    else printf("非法");
    system("pause");
    return 0;
}