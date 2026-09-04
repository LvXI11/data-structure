#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef int ElemType;
typedef struct Stack{
    ElemType e;
    struct Stack* next;
}Stack,*LinkStack;
void init_stack(LinkStack* S){
    *S=(Stack*)malloc(sizeof(Stack));
    if(!*S){
        printf("内存分配失败\n");
        exit(EXIT_FAILURE);
    }
    (*S)->next=NULL;
}
bool is_empty(LinkStack S){
    return S->next==NULL;
}
void destroy_stack(LinkStack* S){
    Stack* p=*S;
    while(p){
        Stack* del=p;
        p=p->next;
        free(del);
    }
    *S=NULL;
}
bool push_stack(LinkStack S,ElemType e){
    Stack* new_node=(Stack*)malloc(sizeof(Stack));
    if(!new_node)return false;
    new_node->e=e;
    new_node->next=S->next;
    S->next=new_node;
    return true;
}
bool pop_elem(LinkStack S,ElemType* e){
    if(is_empty(S))return false;
    Stack* del=S->next;
    *e=del->e;
    S->next=S->next->next;
    free(del);
    return true;
}
void print_stack(LinkStack S){
    if(is_empty(S)){
        printf("空栈\n");
        return;
    }
    printf("top ");
    Stack* p=S->next;
    while(p){
        printf("%d ",p->e);
        p=p->next;
    }
    printf("base\n");
}
bool pop_out_queue(LinkStack IN,LinkStack OUT,ElemType* e){
    if(is_empty(OUT)){
        while(!is_empty(IN)){
            ElemType rec;
            pop_elem(IN,&rec);
            push_stack(OUT,rec);
        }
    }
    ElemType rec;
    bool deleted=pop_elem(OUT,&rec);
    *e=rec;
    return deleted;
}
int main(void){
    LinkStack IN;
    LinkStack OUT;
    init_stack(&IN);
    init_stack(&OUT);
    //预期输出5 4 3 2 1
    push_stack(IN,1);
    push_stack(IN,2);
    push_stack(IN,3);
    push_stack(IN,4);
    push_stack(IN,5);
    print_stack(IN);
    //预期输出1 2 3 4 5
    ElemType value;
    if(pop_out_queue(IN,OUT,&value))printf("out's value:%d\n",value);
    else printf("pop failed\n");
    if(pop_out_queue(IN,OUT,&value))printf("out's value:%d\n",value);
    else printf("pop failed\n");
    if(pop_out_queue(IN,OUT,&value))printf("out's value:%d\n",value);
    else printf("pop failed\n");
    if(pop_out_queue(IN,OUT,&value))printf("out's value:%d\n",value);
    else printf("pop failed\n");
    if(pop_out_queue(IN,OUT,&value))printf("out's value:%d\n",value);
    else printf("pop failed\n");
    return 0;
}