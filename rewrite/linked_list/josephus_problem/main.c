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
    if(!*head){
        printf("内存分配失败\n");
        exit(EXIT_FAILURE);
    }
    (*head)->next=*head;
}
void destroy_list(LinkList* head){
    Node* p=*head;
    while(p){
        Node* del=p;
        p=p->next;
        free(del);
    }
    *head=NULL;
}
bool is_empty(LinkList head){
    return head->next==head;
}
int get_len(LinkList head){
    int count=0;
    Node* p=head;
    while(p->next!=head){
        count++;
        p=p->next;
    }
    return count;
}
void pirnt_list(LinkList head){
    if(is_empty(head)){
        printf("空表\n");
        return;
    }
    Node* p=head->next;
    printf("head<->");
    while(p!=head){
        printf("%d<->",p->e);
        p=p->next;
    }
    printf("head\n");
}
bool insert_elem(LinkList head,int pos,ElemType e){
    if(pos<1||pos>get_len(head)+1)return false;
    Node* prev=head;
    int i=0;
    while(prev->next!=head&&i<pos-1){
        prev=prev->next;
        i++;
    }
    Node* new_node=(Node*)malloc(sizeof(Node));
    new_node->e=e;
    new_node->next=prev->next;
    prev->next=new_node;
    return true;
}
bool out_by_num(LinkList head,int n,int m){
    for(int i=n;i>0;i--){
        insert_elem(head,1,i);
    }
    pirnt_list(head);
    printf("出围者:");
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
        Node* del=cur;
        printf("%d ",del->e);
        prev->next=cur->next;
        free(del);
        cur=prev->next;
        if(cur==head){
            prev=head;
            cur=head->next;
        }
    }
    printf("幸存者:%d\n",head->next->e);
}

int main(void){
    LinkList head;
    init_list(&head);
    out_by_num(head,5,2);
    printf("表长:%d\n",get_len(head));
}
