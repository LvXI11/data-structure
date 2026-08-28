#include<stdio.h>
#include<stdbool.h>
typedef int ElemType;
typedef struct Node{
    ElemType e;
    struct Node *prior,*next;
}Node,*LinkList;
bool delete_list(LinkList head,ElemType e){
    if(!head->next)return false;
    Node* p=head->next;
    bool deleted=false;
    while(p){
        if(p->e==e){
            Node* del=p;
            p->prior->next=p->next;
            if(p->next)p->next->prior=p->prior;
            free(del);
            deleted=true;
        }
        p=p->next;
    }
    return deleted;
}