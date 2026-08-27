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
        printf("分配内存失败\n");
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
    head->next=NULL;
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
    int pos=1;
    while(p){
        if(e==p->e){
            return pos;
        }
        p=p->next;
        pos++;
    }
    return -1;
}
bool get_elem(LinkList head,int pos,ElemType* e){
    Node* p=head->next;
    int i=1;
    while(p){
        if(i==pos){
            *e=p->e;
            return true;
        }
        p=p->next;
        i++;
    }
    return false;
}
void print_list(LinkList head){
    Node* p=head->next;
    if(!p)printf("空表\n");
    printf("head<->");
    while(p){
        printf("%d<->",p->e);
        p=p->next;
    }
    printf("NULL");
}
bool delete_by_value(LinkList head,ElemType e){
    Node* p=head->next;
    bool deleted=false;
    while(p){
        if(e==p->e){
            Node* rec=p->prior;
            Node* del=p;
            p->prior->next=p->next;
            if(p->next)p->next->prior=p->prior;
            free(del);
            deleted=true;
            p=rec;
        }
        p=p->next;
    }
    return deleted;
}
bool insert_elem(LinkList head,int pos,ElemType e){
    Node* prev=head;
    int i=0;
    while(prev&&i<pos-1){
        prev=prev->next;
        i++;
    }
    if(!prev)return false;
    Node* new_node=(Node*)malloc(sizeof(Node));
    if(!new_node){
        printf("内存分配失败\n");
        return false;
    }
    new_node->e=e;
    new_node->next=prev->next;
    new_node->prior=prev;
    if(prev->next)prev->next->prior=new_node;
    prev->next=new_node;
    return true;
}
int main(void){
    LinkList head;
    init_list(&head);

    // 测试 1：头插三个元素，预期打印 1 2 3
    insert_elem(head, 1, 3);
    insert_elem(head, 1, 2);
    insert_elem(head, 1, 1);
    print_list(head);
    printf("\n");
    // 测试 2：尾插一个（插到 length+1 位置），预期 1 2 3 4
    insert_elem(head, get_len(head)+1, 4);
    print_list(head);
    printf("\n");
    // 测试 3：删一个值，预期输出变化
    if(delete_by_value(head, 2))printf("已删掉%d\n",2);
    print_list(head);
    printf("\n");
    // 测试 4：/ 空表操作 / 非法位置(pos=99)……
    // ——剩下的边界情况你自己补，这正是你昨天学的"边界意识"
    if(!delete_by_value(head,99))printf("未找到要删除的元素\n");
    print_list(head);
    printf("\n");
    
    clear_list(head);
    printf("链表已清空\n");

    insert_elem(head,1,1);
    insert_elem(head,1,1);
    insert_elem(head,1,1);
    insert_elem(head,1,1);
    print_list(head);
    printf("\n");

    delete_by_value(head,1);
    print_list(head);
    printf("\n");

    insert_elem(head,1,1);
    insert_elem(head,1,3);
    insert_elem(head,1,2);
    insert_elem(head,1,1);
    print_list(head);
    printf("\n");

    delete_by_value(head,1);
    print_list(head);
    printf("\n");
    
    destroy_list(&head);
    printf("链表已销毁\n");
    return 0;
}