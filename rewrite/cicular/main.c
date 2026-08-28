#include<stdio.h>
#include<stdbool.h>
typedef int ElemType;
typedef struct Node{
    ElemType e;
    struct Node* next;
}Node,*LinkList;
bool delete_list(LinkList head,ElemType e){
    if(head->next==head)return false;
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