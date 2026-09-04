#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int ElemType;
typedef struct Stack{
    ElemType e;
    struct Stack* next;
}Stack,*LinkList;
void init_stack(LinkList* head){
    *head=(Stack*)malloc(sizeof(Stack));
    if(!*head){
        printf("内存分配失败\n");
        exit(EXIT_FAILURE);
    }
    (*head)->next=NULL;
}
void destroy_stack(LinkList* head){
    Stack* s=*head;
    while(s){
        Stack* del=s;
        s=s->next;
        free(del);
    }
    *head=NULL;
}
bool is_empty(LinkList head){
    return head->next==NULL;
}
int get_len(LinkList head){
    Stack* s=head->next;
    int count=0;
    while(s){
        count++;
        s=s->next;
    }
    return count;
}
void print_stack(LinkList head){
    Stack* p=head->next;
    if(is_empty(head)){
        printf("空表\n");
        return;
    }
    printf("top<->");
    while(p){
        printf("%d<->",p->e);
        p=p->next;
    }
    printf("base\n");
}
bool push_elem(LinkList head,ElemType e){
    Stack* s=head;
    Stack* new_node=(Stack*)malloc(sizeof(Stack));
    if(!new_node)return false;
    new_node->e=e;
    new_node->next=head->next;
    head->next=new_node;
    return true;
}
bool pop_elem(LinkList head,ElemType* e){
    if(is_empty(head)){
        printf("空表\n");
        return false;
    }
    Stack* prev=head;
    Stack* cur=head->next;
    while(cur->next){
        prev=cur;
        cur=cur->next;
    }
    *e=cur->e;
    free(cur);
    prev->next=NULL;
    return true;
}
int main(void){
    LinkList head;
    init_stack(&head);
    //预期打印1 2 3 7
    push_elem(head,7);
    push_elem(head,3);
    push_elem(head,2);
    push_elem(head,1);
    print_stack(head);
    ElemType value;
    if(pop_elem(head,&value))printf("pop's value:%d\n",value);
    //预期打印1 2 3
    print_stack(head);
    destroy_stack(&head);
    printf("栈已销毁\n");

    return 0;
}