#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Stack{
    char data;
    struct Stack* next;
}Stack;

void init_stack(Stack** S){
    *S=(Stack*)malloc(sizeof(Stack));
    if(!*S)return;
    (*S)->next=NULL;
}

void push(Stack* S,char e){
    Stack* new_node=(Stack*)malloc(sizeof(Stack));
    if(!new_node)return;
    new_node->data=e;
    new_node->next=S->next;
    S->next=new_node;
}

int is_empty(Stack* S){return S->next==NULL;}

bool pop(Stack* S,char* rec){
    if(is_empty(S))return false;
    Stack* del=S->next;
    *rec=del->data;
    S->next=del->next;
    free(del);
    return true;
}

int main(void){
    Stack* S;
    init_stack(&S);
    char ch;
    bool matched=true;
    while((ch=getchar())!='\n'&&ch!=EOF){
        if(ch=='('||ch=='{'||ch=='[') push(S,ch);
        else if(ch==')'||ch=='}'||ch==']'){
            char rec;
            bool ok=pop(S,&rec) && 
            ((ch==')'&&rec=='(')
            ||(ch=='}'&&rec=='{')
            ||(ch==']'&&rec=='['));
            
            if(!ok){
                matched=false;
                break;
            }
        }
    }
    if(matched&&is_empty(S)) printf("ok\n");
    else printf("false");
}

