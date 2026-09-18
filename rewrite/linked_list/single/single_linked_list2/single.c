#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Node{
    int elem;
    struct Node* next;
}Node;

void insert(Node* head,int e){
    Node* new_node=(Node*)malloc(sizeof(Node));
    if(!new_node)return;
    new_node->elem=e;
    new_node->next=head->next;
    head->next=new_node;
}
bool is_empty(Node* head){
    return head->next==NULL;
}
void delete_node(Node* head,int e){
    if(is_empty(head))return;
    Node* prev=head;
    Node* cur=head->next;
    while(cur){
        if(cur->elem==e){
            prev->next=cur->next;
            free(cur);
            cur=prev->next;
        }
        else{
            prev=cur;
            cur=cur->next;
        }
    }
}