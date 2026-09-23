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
void push(Stack* S,Stack* minS,int e){
    Stack* new_node=(Stack*)malloc(sizeof(Stack));
    if(!new_node)return;
    new_node->e=e;
    new_node->next=S->next;
    S->next=new_node;
    if(is_empty(minS)){
        minS->next=(Stack*)malloc(sizeof(Stack));
        if(!minS->next)return;
        minS->next->e=e;
        minS->next->next=NULL;
    }
    else{
        Stack* p=(Stack*)malloc(sizeof(Stack));
        if(!p)return;
        if(minS->next->e>e){
            p->e=e;
            p->next=minS->next;
            minS->next=p;
        }
        else{
            p->e=minS->next->e;
            p->next=minS->next;
            minS->next=p;
        }
    }
}

void pop(Stack* S,Stack* minS){
    if(is_empty(S))return;
    Stack* del=S->next;
    S->next=del->next;
    free(del);
    del=minS->next;
    minS->next=del->next;
    free(del);
}

int get_min(Stack* minS){
    if(is_empty(minS)) return 0;
    return minS->next->e;
}

int main(void){
    Stack* S;
    Stack* minS;
    init_stack(&S);
    init_stack(&minS);
    push(S,minS,5);
    printf("%d\n",get_min(minS));
    push(S,minS,3);
    printf("%d\n",get_min(minS));
    push(S,minS,7);
    printf("%d\n",get_min(minS));
    pop(S,minS);
    printf("%d\n",get_min(minS));
    pop(S,minS);
    printf("%d\n",get_min(minS));
    push(S,minS,2);
    printf("%d\n",get_min(minS));
    pop(S,minS);
    printf("%d\n",get_min(minS));
    return 0;
}