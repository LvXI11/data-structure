#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Stack{
    int val;
    struct Stack *next;
}Stack;

void init(Stack** S) {
    *S = (Stack*)malloc(sizeof(Stack));
    if(!*S) return;
    (*S)->next = NULL;
}

void push(Stack* S, int val) {
    Stack* new_node = (Stack*)malloc(sizeof(Stack));
    if(!new_node) return;
    new_node->val = val;
    new_node->next = S->next;
    S->next = new_node;
}

bool empty(Stack* S) { return S->next == NULL; }

int pop(Stack* S) {
    if(empty(S)) {
        printf("栈空");
        return -1;
    }
    Stack* del = S->next;
    int v = del->val;
    S->next = del->next;
    free(del);
    return v;
}

int peak(Stack* S) {
    if(empty(S)) {
        printf("栈空");
        return -1;
    }
    return S->next->val;
}

int size(Stack* S) {
    if(empty(S)) {
        printf("栈空");
        return 0;
    }
    int count = 0;
    Stack* p = S->next;
    while(p) {
        count++;
        p = p->next;
    }
    return count;
}

int main(void) {
    Stack* S = NULL;
    init(&S);

    push(S, 1); push(S, 2); push(S, 3);
    printf("push 1 2 3  -> size=%d top=%d\n", size(S), peak(S));

    printf("peek        -> %d  size=%d\n", peak(S), size(S));

    for (int i = 0; i < 3; i++)
        printf("pop         -> %d  size=%d\n", pop(S), size(S));

    printf("pop         -> ");  pop(S);  printf("  size=%d\n", size(S));
    printf("peek        -> ");  peak(S); printf("  size=%d\n", size(S));

    free(S);                    // 别忘释放那个哑结点
    return 0;
}