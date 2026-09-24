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
        return;
    }
    (*S)->next=NULL;
}
void destroy_stack(LinkStack* S){
    Stack* s=*S;
    while(s){
        Stack* del=s;
        s=s->next;
        free(del);
    }
    *S=NULL;
}
bool is_empty(LinkStack S){
    return S->next==NULL;
}
bool push(LinkStack S,LinkStack minS,ElemType e){
    Stack* new_node=(Stack*)malloc(sizeof(Stack));
    if(!new_node)return false;
    new_node->e=e;
    new_node->next=S->next;
    S->next=new_node;
    Stack* new_node2=(Stack*)malloc(sizeof(Stack));
    if(!new_node2)return false;
    new_node2->e=e;
    if(is_empty(minS)){
        new_node2->next=minS->next;
        minS->next=new_node2;
    }
    else{
        if(new_node2->e>minS->next->e){
            new_node2->e=minS->next->e;
        }
        new_node2->next=minS->next;
        minS->next=new_node2;
    }
    return true;
}
bool pop(LinkStack S,LinkStack minS,ElemType* e){
    if(is_empty(S))return false;
    Stack* del=S->next;
    *e=del->e;
    S->next=S->next->next;
    free(del);
    del=minS->next;
    minS->next=minS->next->next;
    free(del);
    return true;
}
bool top(LinkStack S,ElemType* e){
    if(is_empty(S))return false;
    *e=S->next->e;
    return true;
}
bool get_min(LinkStack minS,ElemType* min){
    if(is_empty(minS))return false;
    *min=minS->next->e;
    return true;
}
void print_stack(LinkStack S){
    if(is_empty(S)){
        printf("空栈\n");
        return;
    }
    printf("top ");
    Stack* s=S->next;
    while(s){
        printf("%d ",s->e);
        s=s->next;
    }
    printf("base\n");
}
int main(void){
    LinkStack S;
    LinkStack minS;
    init_stack(&S);
    init_stack(&minS);
    //预期打印5 1 4 7 3 2 3
    push(S,minS,3);
    push(S,minS,2);
    push(S,minS,3);
    push(S,minS,7);
    push(S,minS,4);
    push(S,minS,1);
    push(S,minS,5);
    print_stack(S);
    ElemType min;
    if(get_min(minS,&min))printf("minimum elem:%d\n",min);
    else printf("failed\n");
    ElemType e;
    if(top(S,&e))printf("top' elem:%d\n",e);
    else printf("failed\n");
    printf("\n");
    //预期输出4 7 3 2 3
    ElemType value;
    if(pop(S,minS,&value))printf("pop' value:%d\n",value);
    else printf("failed\n");
    if(pop(S,minS,&value))printf("pop' value:%d\n",value);
    else printf("failed\n");
    print_stack(S);
    if(get_min(minS,&min))printf("minimum elem:%d\n",min);
    else printf("failed\n");
    if(top(S,&e))printf("top' elem:%d\n",e);
    else printf("failed\n");
    destroy_stack(&S);
    destroy_stack(&minS);
    printf("\n栈已销毁\n");
    return 0;
}