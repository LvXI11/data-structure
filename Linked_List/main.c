#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int ElemType;
typedef struct Node{
    ElemType e;
    struct Node* next;
}Node,*LinkList;

void init(LinkList* head){
    *head=(Node*)malloc(sizeof(Node));
    if(*head==NULL){
        printf("内存分配失败\n");
        exit(EXIT_FAILURE);
    }
    (*head)->next=NULL;
}
void destroy_list(LinkList* head){
    Node* p=*head;
    while(p){
        Node* rec=p;
        p=p->next;
        free(rec);
    }
    *head=NULL;
}
bool clear_list(LinkList head){
    Node* p=head->next;
    while(p){
        Node* rec=p;
        p=p->next;
        free(rec);
    }
    head->next=NULL;
    return true;
}
bool is_empty(LinkList head){
    return head->next==NULL;
}
int get_len(LinkList head){
    Node* p=head->next;
    int len=0;
    while(p){
        len++;
        p=p->next;
    }
    return len;
}
int print_list(LinkList head){
    Node* p=head->next;
    int count=1;
    printf("打印链表\n");
    printf("\n========\n");
    while(p){
        printf("id:%d elem:%d\n",count,p->e);
        p=p->next;
        count++;
    }
    if(count==1)printf("空\n");
    printf("========\n");
    return count;
}
bool insert_elem(LinkList head,int pos,ElemType e){//重点看
    Node* pre=head;
    int i=0;
    while(pre&&i<pos-1){
        pre=pre->next;
        i++;
    }
    if(!pre)return false;
    Node* new_node=(Node*)malloc(sizeof(Node));
    if(!new_node)return false;
    new_node->e=e;
    new_node->next=pre->next;
    pre->next=new_node;
    return true;
}
bool delete_elem(LinkList head,int pos,ElemType* e){
    Node* pre=head;
    int i=0;
    while(pre&&i<pos-1){
        pre=pre->next;
        i++;
    }
    if(!pre||!pre->next)return false;
    Node* del=pre->next;
    *e=del->e;
    pre->next=del->next;
    free(del);
    return true;
}
bool get_elem(LinkList head,int pos,ElemType* e){
    Node* p=head->next;
    int i=1;
    while(p&&i<pos){
        p=p->next;
        i++;
    }
    if(!p)return false;
    *e=p->e;
    return true;
}
int locate_elem(LinkList head,ElemType e){
    Node* p=head->next;
    int count=1;
    while(p){
        if(p->e==e){
            return count;
        }
        p=p->next;
        count++;
    }
    return -1;
}
int main(void){
    LinkList head=NULL;
    init(&head);

    if(clear_list(head))printf("清空成功\n");
    else printf("清空失败\n");
    
    if(is_empty(head))printf("为空链表\n");
    else printf("不为空链表\n");

    destroy_list(&head);
    return 0;
}