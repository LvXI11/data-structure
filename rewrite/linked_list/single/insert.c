#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
typedef int ElemType;
typedef struct Node{
    ElemType e;
    struct Node* next;
}Node,*LinkList;
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