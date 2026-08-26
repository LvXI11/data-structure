#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int ElemType;

typedef struct Node{
    ElemType e;
    struct Node *prior,*next;
}Node,*LinkList;

void init_list(LinkList* head){
    *head=(Node*)malloc(sizeof(Node));
    if(!(*head)){
        printf("内存分配失败\n");
        exit(EXIT_FAILURE);
    }
    (*head)->prior=NULL;
    (*head)->next=NULL;
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
void clear_list(LinkList head){
    Node* p=head->next;
    while(p){
        Node* del=p;
        p=p->next;
        free(del);
    }
}
bool is_empty(LinkList head){
    return head->next==NULL;
}
int get_len(LinkList head){
    Node* p=head->next;
    int count=0;
    while(p){
        count++;
        p=p->next;
    }
    return count;
}

int search_elem(LinkList head,ElemType e){
    Node* p=head->next;
    int count=1;
    while(p){
        if(e==p->e){
            return count;
        }
        p=p->next;
        count++;
    }
    return -1;
}

bool get_elem(LinkList head,int pos,ElemType* e){
    if(pos<1)return false;
    Node* p=head->next;
    int count=1;
    while(p){
        if(count==pos){
            *e=p->e;
            return true;
        }
        p=p->next;
    }
    return false;
}
void print_list(LinkList head){
    Node* p=head->next;
    int i=1;
    printf("\n==========\n");
    if(!p)printf("空表\n");
    while(p){
        printf("id:%d elem:%d\n",i,p->e);
        p=p->next;
        i++;
    }
    printf("==========\n");
}

bool delete_by_value(LinkList head,ElemType e){
    Node* p=head->next;
    while(p&&e!=p->e)p=p->next;
    if(!p)return false;
    p->prior->next=p->next;
    if(p->next)p->next->prior=p->prior;
    free(p);
    return true;
}
bool insert_elem(LinkList head,int pos,ElemType e){
    Node* prev=head;
    int i=0;
    while(prev&&i<pos-1){
        prev=prev->next;
    }
    if(!prev)return false;
    Node* new_node=(Node*)malloc(sizeof(Node));
    new_node->e=e;
    new_node->next=prev->next;
    new_node->prior=prev;
    if(prev->next!=NULL)prev->next->prior=new_node;
    prev->next=new_node;
    return true;
}
int main(void){
    LinkList head=NULL;
    init_list(&head);

    return 0;
}