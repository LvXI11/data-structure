#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef char bracket;
typedef struct Stack{
    bracket b;
    struct Stack* next;
}Stack,*LinkStack;

void init_stack(LinkStack* head){
    *head=(Stack*)malloc(sizeof(Stack));
    if(!*head){
        printf("内存分配失败\n");
        exit(EXIT_FAILURE);
    }
    (*head)->next=NULL;
}
bool is_empty(LinkStack head){
    return head->next==NULL;
}
void print_stack(LinkStack head){
    if(is_empty(head)){
        printf("空栈\n");
        return;
    }
    printf("top ");
    Stack* p=head->next;
    while(p){
        printf("%c ",p->b);
        p=p->next;
    }
    printf("base\n");
}
void destroy_stack(LinkStack* head){
    Stack* p=*head;
    while(p){
        Stack* del=p;
        p=p->next;
        free(del);
    }
    *head=NULL;
}
bool push_bracket(LinkStack head,bracket b){
    Stack* new_node=(Stack*)malloc(sizeof(Stack));
    if(!new_node)return false;
    new_node->b=b;
    new_node->next=head->next;
    head->next=new_node;
    return true;
}
bool pop_bracket(LinkStack head,bracket* b){
    if(is_empty(head))return false;
    Stack* del=head->next;
    *b=del->b;
    head->next=head->next->next;
    free(del);
    return true;
}
int main(void){
    LinkStack head;
    init_stack(&head);
    char ch;
    bool matched=true;
    while((ch=getchar())!='\n'&&ch!=EOF){
        if(ch!=' '&&ch!='\n'){
            if(ch=='('||ch=='['||ch=='{')push_bracket(head,ch);
            else if(ch==')'||ch==']'||ch=='}'){
                char rec;
                bool ok=pop_bracket(head,&rec)&&
                ((ch==')'&&rec=='(')||(ch==']'&&rec=='[')||(ch=='}'&&rec=='{'));
                if(!ok){
                    matched=false;
                    break;
                }
            }
        }
    }
    if(matched&&is_empty(head))printf("合法\n");
    else printf("不合法\n");
    destroy_stack(&head);
    printf("栈已销毁\n");
    system("pause");
    return 0;
}