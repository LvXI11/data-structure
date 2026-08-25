#include<stdio.h>
#include<stdlib.h>

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
int count=0;

void init_List(Node** pp);
void destroy_List(Node* head);
void clear_List(Node* head);
void get_list_len(Node* head);
Node* get_elem(Node* head,int id);
void search_elem(Node* head,ElemType e);
Node* insert_elem(Node* head,Node* new);
Node* delete_elem(Node* head,int id);
Node* add_elem_head(Node* head,Node* new);
void add_elem_tail(Node* head,Node* new);
Node* create_node(int id,ElemType e);
int main(void){
    init_List(&head);
    head=add_elem_head(head,create_node(1,8));
    add_elem_tail(head,create_node(1,7));
    head=add_elem_head(head,create_node(1,6));
    add_elem_tail(head,create_node(1,5));
    head=delete_elem(head,2);
    head=insert_elem(head,create_node(2,0));
    search_elem(head,8);

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
void clear_List(Node* head){
    Node* p=head->next;
    while(p!=NULL){
        Node* rec=p;
        p=p->next;
        free(rec);
    }
    head->next=NULL;
    printf("清空链表\n");
}
void get_list_len(Node* head){
    Node* p=head;
    while(p!=NULL){
        count++;
        p=p->next;
    }
    printf("链表长为%d\n",count);
}
Node* get_elem(Node* head,int id){
    if(id<1||id>count){
        printf("输入错误\n");
        return;
    }
    Node* p=head;
    while(p->data.id!=id){
        p=p->next;
    }
    return p;
}
void search_elem(Node* head,ElemType e){
    Node* p=head;
    while(p!=NULL){
        if(e==p->data.e){
            printf("找到了%d序号为%d\n",e,p->data.id);
            return;
        }
    }
    printf("未找的%d\n",e);
}
Node* insert_elem(Node* head,Node* new){
    if(new->data.id<1||new->data.id>count+1){
        printf("输入错误\n");
        return head;
    }
    Node* p=head;
    if(new->data.id==1){
        new->next=head->next;
        p=new->next;
        while(p!=NULL){
            p->data.id++;
            p=p->next;
        }
        printf("插入成功\n");
        return new;
    }
    while(p!=NULL){
        if(p->data.id==new->data.id-1){
            new->next=p->next;
            p->next=new;
            p=new->next;
            while(p!=NULL){
                p->data.id++;
                p=p->next;
            }
            printf("插入成功\n");
            break;
        }
        p=p->next;
    }
    return head;
}
Node* delete_elem(Node* head,int id){
    if(id==head->data.id){
        Node* temp=head;
        head=head->next;
        free(temp);
        Node* p=head;
        while(p!=NULL){
                p->data.id--;
                p=p->next;
        }
        printf("删除成功\n");
        return head;
    }
     Node* prev=head;
     Node* cur=head->next;
     while(cur!=NULL){
        if(cur->data.id==id){
            prev->next=cur->next;
            free(cur);
            Node* p=prev->next;
            while(p!=NULL){
                p->data.id--;
                p=p->next;
            }
            printf("删除成功\n");
            break;
        }
        prev=cur;
        cur=cur->next;
     }
     return head;
}
Node* add_elem_head(Node* head,Node* new){
    new->next=head;
    Node* p=new->next;
    while(p!=NULL){
        p->data.id++;
        p=p->next;
    }
    printf("添加成功_head\n");
    return new;
}
void add_elem_tail(Node* head,Node* new){
    Node* p=head;
    while(p->next!=NULL){
        p=p->next;
    }
    p->next=new;
    new->data.id=p->data.id+1;
    printf("添加成功_tail\n");
}
Node* create_node(int id,ElemType e){
    Node* new=(Node*)malloc(sizeof(Node));
    if(new==NULL){
        printf("创建失败\n");
        return NULL;
    }
    new->data.id=id;
    new->data.e=e;
    new->next=NULL;
    return new;
}