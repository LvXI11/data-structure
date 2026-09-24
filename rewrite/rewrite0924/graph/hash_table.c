#include<stdio.h>
#include<stdlib.h>
#define N 11

typedef struct Node{
    int key;
    struct Node* next;
}Node;

Node* table[N];

void init_node(){
    for(int i=0;i<N;i++)
    table[i]=NULL;
}

void insert(int key){
    int pos=key%N;
    Node* new_node=(Node*)malloc(sizeof(Node));
    if(!new_node)return;
    new_node->key=key;
    new_node->next=table[pos];
    table[pos]=new_node;
}

int delete_node(int key){
    int pos=key%N;
    if(!table[pos])return 0;
    Node** pp=&table[pos];
    while(*pp){
        if((*pp)->key==key){
            Node* del=*pp;
            *pp=(del)->next;
            free(del);
            return 1;
        }
        pp=&(*pp)->next;
    }
    return 1;
}