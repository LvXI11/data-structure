#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Circluar{
    int data;
    struct Circluar* next;
}Circluar;

void init(Circluar** head){
    *head=(Circluar*)malloc(sizeof(Circluar));
    if(!*head)return;
    (*head)->next=*head;
}

int get_len(Circluar* head){
    Circluar* p=head->next;
    int count=0;
    while(p!=head){
        count++;
        p=p->next;
    }
    return count;
}

bool is_empty(Circluar* head){
    return head->next==head;
}

void insert(Circluar* head,int pos,int e){
    if(pos<1||pos>get_len(head)+1)return;
    int i=0;
    Circluar* pre=head;
    while(pre->next!=head&&i<pos-1){
        pre=pre->next;
        i++;
    }
    if(!pre)return;
    Circluar* new_node=(Circluar*)malloc(sizeof(Circluar));
    if(!new_node)return;
    new_node->data=e;
    new_node->next=pre->next;
    pre->next=new_node;
}

bool delete_elem(Circluar* head,int e){
    Circluar* pre=head;
    Circluar* cur=head->next;
    bool deleted=false;
    while(cur!=head){
        if(cur->data==e){
            pre->next=cur->next;
            free(cur);
            cur=pre->next;
            deleted=true;
        }
        else{
            pre=cur;
            cur=cur->next;
        }
    }
    return deleted;
}

void josephus(Circluar* head,int m,int n){
    Circluar* pre=head;
    Circluar* cur=head->next;
    if(cur==head)return;
    int reminded=n;
    while(reminded>1){
        for(int i=0;i<m-1;i++){
            pre=cur;
            cur=cur->next;
            if(cur==head){
                pre=head;
                cur=head->next;
            }
        }
        printf("%d ",cur->data);
        pre->next=cur->next;
        free(cur);
        cur=pre->next;
        if(cur==head){
            pre=head;
            cur=head->next;
        }
        reminded--;    
    }
    printf("\n幸存者：%d\n",head->next->data);
}