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
    (*head)->next=NULL;
}
bool insert_list(LinkList head,int pos,ElemType e){
    if(pos<1)return false;
    Node* prev=head;
    int i=0;
    while(prev&&i<pos-1){
        prev=prev->next;
        i++;
    }
    if(!prev)return false;
    Node* new_node=(Node*)malloc(sizeof(Node));
    if(!new_node)return false;
    new_node->e=e;
    new_node->next=prev->next;
    prev->next=new_node;
    return true;
}
void print_list(LinkList head){
    Node* p=head->next;
    if(!head->next){
        printf("空表\n");
        return;
    }
    printf("head<->");
    while(p){
        printf("%d<->",p->e);
        p=p->next;
    }
    printf("NULL");
    printf("\n");
}
bool merge_two_list(LinkList A,LinkList B,LinkList C){
    Node* a1=A->next;
    Node* b1=B->next;
    Node* tail=C;
    while(a1&&b1){
        Node* new_node=(Node*)malloc(sizeof(Node));
        if(!new_node)return false;
        if(a1->e<=b1->e){
            new_node->e=a1->e;
            new_node->next=NULL;
            tail->next=new_node;
            tail=tail->next;
            a1=a1->next;
        }
        else{
            new_node->e=b1->e;
            new_node->next=NULL;
            tail->next=new_node;
            tail=tail->next;
            b1=b1->next;
        }
    }
    if(a1){
        while(a1){
            Node* temp=(Node*)malloc(sizeof(Node));
            if(!temp)return false;
            temp->e=a1->e;
            temp->next=NULL;
            tail->next=temp;
            tail=tail->next;
            a1=a1->next;
        }
    }
    if(b1){
        while(b1){
            Node* temp=(Node*)malloc(sizeof(Node));
            if(!temp)return false;
            temp->e=b1->e;
            temp->next=NULL;
            tail->next=temp;
            tail=tail->next;
            b1=b1->next;
        }
    }
    return true;
}
bool clear_list(LinkList head){
    if(!head->next)return false;
    Node* p=head->next;
    while(p){
        Node* del=p;
        p=p->next;
        free(del);
    }
    head->next=NULL;
    return true;
}
int main(void){
    LinkList A,B,C;
    init_list(&A);
    init_list(&B);
    init_list(&C);
    //插入元素
    //预期输出1 1 3 5
    printf("A:");
    insert_list(A,1,5);
    insert_list(A,1,3);
    insert_list(A,1,1);
    insert_list(A,1,1);
    print_list(A);
    //预期输出2 2 4 6
    printf("B:");
    insert_list(B,1,6);
    insert_list(B,1,4);
    insert_list(B,1,2);
    insert_list(B,1,2);
    print_list(B);

    merge_two_list(A,B,C);
    //预期输出 1 2 3 4 5 6
    printf("C:");
    print_list(C);
    //清空链表
    clear_list(A);
    printf("A:");
    print_list(A);

    clear_list(B);
    printf("B:");
    print_list(B);

    clear_list(C);
    printf("C:");
    print_list(C);
    //两空表合并
    if(merge_two_list(A,B,C)){
        print_list(C);
    }
    else{
        printf("合并失败\n");
    }
    insert_list(A,1,3);
    insert_list(A,1,1);

    printf("A:");
    print_list(A);
    printf("B:");
    print_list(B);

    merge_two_list(A,B,C);
    //预期打印 1 3
    printf("C:");
    print_list(C);
    //清空链表
    clear_list(A);
    printf("A:");
    print_list(A);

    clear_list(B);
    printf("B:");
    print_list(B);

    clear_list(C);
    printf("C:");
    print_list(C);

    //预期输出1 3 5
    printf("A:");
    insert_list(A,1,5);
    insert_list(A,1,3);
    insert_list(A,1,1);
    print_list(A);
    //预期输出2 4 6
    printf("B:");
    insert_list(B,1,6);
    insert_list(B,1,4);
    insert_list(B,1,2);
    print_list(B);

    merge_two_list(A,B,C);
    //预期输出 1 2 3 4 5 6
    printf("C:");
    print_list(C);
    return 0;
}