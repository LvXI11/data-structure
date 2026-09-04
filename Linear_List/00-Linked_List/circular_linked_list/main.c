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
    if(*head==NULL){
        printf("分配内存失败\n");
        exit(EXIT_FAILURE);
    }
    (*head)->next=*head;
}
bool is_empty(LinkList head){
    return head->next==head;
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
void clear_list(LinkList head){
    Node* p=head->next;
    while(p!=head){
        Node* del=p;
        p=p->next;
        free(del);
    }
    head->next=head;
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
int search_elem(LinkList head,ElemType e){
    Node* p=head->next;
    int i=1;
    while(p!=head){
        if(p->e==e){
            return i;
        }
        p=p->next;
        i++;
    }
    return -1;
}
bool get_elem_by_pos(LinkList head,int pos,ElemType* e){
    Node* p=head->next;
    int i=1;
    while(p!=head){
        if(pos==i){
            *e=p->e;
            return true;
        }
        p=p->next;
        i++;
    }
    return false;
}
bool delete_elem_by_value(LinkList head,ElemType e){
    if(is_empty(head))return false;
    Node* prev=head;
    Node* cur=head->next;
    bool deleted=false;
    while(cur!=head){
        if(cur->e==e){
            prev->next=cur->next;
            free(cur);
            cur=prev->next;
            deleted=true;
        }
        else{
            prev=cur;
            cur=cur->next;
        }
    }
    return deleted;
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
    if(!new_node)return false;
    new_node->e=e;
    new_node->next=prev->next;
    prev->next=new_node;
    return true;
}
void print_list(LinkList head){
    Node* p=head->next;
    if(head->next==head)printf("空表\n");
    printf("head<->");
    while(p!=head){
        printf("%d<->",p->e);
        p=p->next;
    }
    printf("head");
    printf("\n");
}
int main(void){
    LinkList head;
    init_list(&head);
    //依次打印 1 1 2 3
    insert_elem(head,1,3);
    insert_elem(head,1,2);
    insert_elem(head,1,1);
    insert_elem(head,1,1);
    print_list(head);
    //依次打印 2 3
    if(delete_elem_by_value(head,1))printf("成功删除%d\n",1);
    print_list(head);

    clear_list(head);
    printf("已清空链表\n");
    print_list(head);
    //依次打印 6 7 8 
    insert_elem(head,1,8);
    insert_elem(head,1,7);
    insert_elem(head,1,6);
    print_list(head);
    //打印序号为2的元素是7
    ElemType e;
    if(get_elem_by_pos(head,2,&e))printf("序号为%d的元素是%d\n",2,e);
    //打印表长为3
    printf("表长为%d\n",get_len(head));
    printf("\n");
    destroy_list(&head);
    printf("链表已销毁\n");
    return 0;
}