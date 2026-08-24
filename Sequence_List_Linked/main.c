#include<stdio.h>
typedef int ElemType;

typedef struct{
    int id;
    ElemType e;
}Data;

typedef struct Node{
    Data data;
    struct Node* next;
}Node,*LinkList;//LinkList==Node*

LinkList head=NULL;

void init_List(Node** pp);
void destroy_List(Node* head);
void clear_List(Node* head);
void get_list_len(Node* head);
void get_elem(Node* head,int id);
void search_elem(Node* head,ElemType e);
Node* insert_elem(Node* head,int id,ElemType e);
Node* delete_elem(Node* head,int id);
Node* add_elem_head(Node* head,ElemType e);
Node* add_elem_tail(Node* head,ElemType e);

int main(void){
    init_List(&head);

    return 0;
}
void init_List(Node** pp){
    *pp=(Node*)malloc(sizeof(Node));
    if(*pp==NULL){
        printf("分配失败\n");
        return;
    }
    (*pp)->next=NULL;
}

void destroy_List(Node* head){
    Node* p=head;
    while(p!=NULL){
        Node* rec=p;
        p=p->next;
        free(rec);
    }
    printf("已销毁\n");
}