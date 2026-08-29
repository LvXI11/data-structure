#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX_LEN 100
typedef int ElemType;
typedef struct Stack{
    ElemType* top;
    ElemType* base;
}Stack;
void init_stack(Stack* S){
    S->base=(ElemType*)malloc(MAX_LEN*sizeof(ElemType));
    if(!S->base){
        printf("内存分配失败\n");
        exit(EXIT_FAILURE);
    }
    S->top=S->base;
}
void destroy_stack(Stack* S){
    free(S->base);
    S->base=NULL;
    S->top=NULL;
}
void clear_stack(Stack* S){
    S->top=S->base;
}
bool is_empty(Stack S){
    return S.base==S.top;
}
int get_len(Stack S){
    return S.top-S.base;
}
void print_stack(Stack S){
    if(is_empty(S)){
        printf("空栈\n");
        return;
    }
    printf("base ");
    while(S.base<S.top)
    printf("%d ",*(S.base++));
    printf("top\n");
}
bool push_elem(Stack* S,ElemType e){
    if(S->top-S->base==MAX_LEN)return false;
    *(S->top++)=e;
    return true;
}
bool pop_elem(Stack* S,ElemType* e){
    if(S->base==S->top){
        printf("空表\n");
        return false;
    }
    *e=*(S->top-1);
    S->top--;
    return true;
}
int main(void){
    Stack S;
    init_list(&S);
    if(is_empty(S))printf("空栈\n");
    else{printf("栈不为空\n");}
    //预期输出base 1 2 3 top
    push_elem(&S,1);
    push_elem(&S,2);
    push_elem(&S,3);
    print_stack(S);
    ElemType value;
    if(pop_elem(&S,&value))printf("pop's vaule:%d\n",value);
    print_stack(S);
    if(pop_elem(&S,&value))printf("pop's vaule:%d\n",value);
    print_stack(S);
    if(is_empty(S))printf("空栈\n");
    else{printf("栈不为空\n");}
    printf("长度:%d\n",get_len(S));
    return 0;
}