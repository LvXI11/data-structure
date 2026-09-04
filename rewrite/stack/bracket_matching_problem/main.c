#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef char bracket;
typedef struct Stack{
    bracket b;
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
void destroy_stack(LinkStack* S){
    Stack* p=*S;
    while(p){
        Stack* del=p;
        p=p->next;
        free(del);
    }
    *S=NULL;
}
bool is_empty(LinkStack S){
    return S->next==NULL;
}
bool push_elem(LinkStack S,bracket b){
    Stack* new_node=(Stack*)malloc(sizeof(Stack));
    if(!new_node)return false;
    new_node->b=b;
    new_node->next=S->next;
    S->next=new_node;
    return true;
}
bool pop_elem(LinkStack S,bracket* b){
    if(is_empty(S))return false;
    Stack* del=S->next;
    *b=del->b;
    S->next=S->next->next;
    free(del);
    return true;
}
int main(void){
    LinkStack S;
    init_stack(&S);
    char ch;
    bool matched=true;
    while(ch=getchar()!='\n'&&ch!=EOF){
        if(ch!='\n'&&ch!=' '){
            if(ch=='('||ch=='['||ch=='{')push_elem(S,ch);
            else if(ch==')'||ch==']'||ch=='}'){
                char rec;
                bool ok=pop_elem(S,&rec)&&
                ((ch==')'&&rec=='(')
                ||(ch==']'&&rec=='[')
                ||(ch=='}'&&rec=='{'));
                if(!ok){
                    matched=false;
                    break;
                }
            }
        }
    }
    if(matched&&is_empty(S))printf("合法\n");
    else printf("非法\n");
    destroy_stack(&S);
    printf("栈已销毁\n");
    system("pause");
    return 0;
}