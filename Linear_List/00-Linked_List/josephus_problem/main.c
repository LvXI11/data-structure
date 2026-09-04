#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int ElemType;
typedef struct Node{
    ElemType e;
    struct Node* next;
}Node,*LinkList;

void init_list(LinkList* head){
    *head=(Node*)malloc(sizeof(Node));
    if(!(*head)){
        printf("内存分配失败\n");
        exit(EXIT_FAILURE);
    }
    (*head)->next=*head;
}
bool is_empty(LinkList head){
    return head->next==head;
}
int get_len(LinkList head){
    Node* p=head->next;
    int count=0;
    while(p!=head){
        count++;
        p=p->next;
    }
    return count;
}
void destroy_list(LinkList* head){
    if(is_empty(*head)){
        free(*head);
        *head=NULL;
        return;
    }
    Node* p=(*head)->next;
    while(p!=(*head)){
        Node* del=p;
        p=p->next;
        free(del);
    }
    free(*head);
    *head=NULL;
}
bool insert_list(LinkList head,int pos,ElemType e){
    if(pos<1||pos>get_len(head)+1)return false;
    Node* prev=head;
    int i=0;
    while(prev->next!=head&&i<pos-1){
        prev=prev->next;
        i++;
    }
    Node* new_node=(Node*)malloc(sizeof(Node));
    if(!new_node)return false;
    new_node->e=e;
    new_node->next=prev->next;
    prev->next=new_node;
    return true;
}
void print_list(LinkList head){
    Node* p=head->next;
    if(is_empty(head)){
        printf("空表\n");
        return;
    }
    printf("head<->");
    while(p!=head){
        printf("%d<->",p->e);
        p=p->next;
    }
    printf("head\n");
}

void out_by_count(LinkList head,int n,int m){
    for(int i=n;i>0;i--){
        insert_list(head,1,i);
    }
    print_list(head);
    Node* prev=head;
    Node* cur=head->next;
    while(get_len(head)>1){
        for(int i=0;i<m-1;i++){
            prev=cur;
            cur=cur->next;
            if(cur==head){
                prev=head;
                cur=head->next;
            }
        }
        printf("出圈者:%d  ",cur->e);
        prev->next=cur->next;
        free(cur);
        cur=prev->next;
        if(cur==head){
            prev=head;
            cur=head->next;
        }
        print_list(head);
    }
    printf("幸存者:%d\n",cur->e);
}
int main(void){
    LinkList head;
    init_list(&head);
    out_by_count(head,7,3);
    destroy_list(&head);
    printf("链表已销毁\n");
    return 0;
}