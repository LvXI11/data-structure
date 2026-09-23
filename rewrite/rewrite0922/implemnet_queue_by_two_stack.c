#include<stdio.h>
#include<stdlib.h>

typedef struct Stack{
    int e;
    struct Stack* next;
}Stack;

void init_stack(Stack** S){
    *S=(Stack*)malloc(sizeof(Stack));
    if(!*S)return;
    (*S)->next=NULL;
}

int is_empty(Stack* S){
    return S->next==NULL;
}

void push(Stack* S,int e){
    Stack* new_node=(Stack*)malloc(sizeof(Stack));
    if(!new_node)return;
    new_node->e=e;
    new_node->next=S->next;
    S->next=new_node;
}

void pop(Stack* inS,Stack* ouS){
    if(is_empty(ouS)){
        if(is_empty(inS))return;
        
        while(!is_empty(inS)){
            Stack* rec=inS->next;

            Stack* new_node=(Stack*)malloc(sizeof(Stack));
            if(!new_node)return;
            new_node->e=rec->e;
            new_node->next=ouS->next;
            ouS->next=new_node;

            inS->next=rec->next;
            free(rec);
        }
    }

    Stack* del=ouS->next;
    int deleted=del->e;
    ouS->next=del->next;
    free(del);
    printf("%d出栈\n",deleted);
}

void print_stack(Stack* S){
    if(is_empty(S)){
        printf("栈为空\n");
        return;
    }
    Stack* p=S->next;
    while(p){
        printf("%d ",p->e);
        p=p->next;
    }
    printf("\n");
}

int main(void){
    Stack* inS;
    Stack* ouS;
    init_stack(&inS);
    init_stack(&ouS);
    push(inS,1);
    push(inS,2);
    push(inS,3);
    push(inS,4);
    push(inS,5);
    push(inS,6);
    push(inS,7);
    push(inS,8);
    push(inS,9);
    push(inS,0);

    print_stack(inS);
    for(int i=0;i<10;i++){
        pop(inS,ouS);
    }
    print_stack(ouS);
    return 0;
}