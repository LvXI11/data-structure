#include<stdio.h>
#include<stdlib.h>
#define SIZE 11

typedef struct Node{
    int key;
    struct Node* next;
}Node;

Node* table[SIZE];

void init_table(){
    for(int i=0;i<SIZE;i++)
    table[i]=NULL;
}

void insert(int key){
    int pos=key%SIZE;
    Node* new_node=(Node*)malloc(sizeof(Node));
    if(!new_node) return;
    new_node->key=key;
    new_node->next=table[pos];
    table[pos]=new_node;
}

int delete_node(int key){
    int pos=key%SIZE;
    if(!table[pos]) return 0;
    Node** pp=&table[pos];
    while(*pp){
        if((*pp)->key==key){
            Node* del=*pp;
            *pp=(*pp)->next;
            free(del);
            return 1;
        }
        pp=&((*pp)->next);
    }
    return 0;
}

Node* search(int key){
    int pos=key%SIZE;
    if(!table[pos]) return NULL;
    Node* p=table[pos];
    while(p){
        if(p->key==key) return p;
        p=p->next;
    }
    return NULL;
}