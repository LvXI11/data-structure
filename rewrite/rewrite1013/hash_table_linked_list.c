#include<stdlib.h>
#define SIZE 11
#include<stdbool.h>

typedef struct Node{
    int val;
    struct Node* next;
}Node;

Node* table[SIZE];

void init_table(Node* table[]){
    for(int i = 0;i < SIZE; i++)
    table[i] = NULL;
}

bool insert(int val){
    int pos = (val % SIZE + SIZE) % SIZE;
    if(table[pos] != NULL){
        Node* p = table[pos];
        while(p){
            if(p->val == val) return false;
            p = p->next;
        }
    }
    Node* new_node = (Node*)malloc(sizeof(Node));
    if(!new_node) return false;
    new_node->val = val;
    new_node->next = table[pos];
    table[pos] = new_node;
    return true;
}

bool delete_node(int val){
    int pos = (val % SIZE + SIZE) % SIZE;
    if(table[pos] == NULL) return false;
    Node** p = &table[pos];
    while(*p){
        if((*p)->val == val){
            Node* del = *p;
            *p = del->next;
            free(del);
            return true;
        }
        p = &(*p)->next;
    }
    return false;
}

Node* search(int val){
    int pos = (val % SIZE + SIZE) % SIZE;
    if(table[pos] == NULL) return NULL;
    Node* p = table[pos];
    while(p){
        if(p->val == val) return p;
        p = p->next;
    }
    return NULL;
}