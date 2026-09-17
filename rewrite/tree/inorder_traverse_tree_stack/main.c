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

void init_stack(Stack** S){

}

void push(Stack* S){

}

Tree* pop(Stack* S){

}

Tree* create_node(ElemType e){

}

bool is_empty(Stack* S){

}
void inorder(Tree* T){
    Stack* S;
    init_stack(&S);
    Tree* p=T;
    while(p&&!is_empty(S)){
        if(p){
            push(p);
            p=p->lchild;
        }
        else{
            p=pop(S);
            printf("%d ",p->e);
            p=p->rchild;
        }
    }
}
int main(void){

    return 0;
}