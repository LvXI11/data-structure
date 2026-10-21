#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Node{
    int val;
    struct Node* next;
}Node;

void init_node(Node** head) {
    *head = (Node*)malloc(sizeof(Node));
    if(!*head) return;
    (*head)->next = NULL;
}

bool insert_at(Node* head, int pos, int val) {
    if(pos < 0) return false;
    Node* p = head;
    int i = 0;
    while(p && i < pos) {
        p = p->next;
        i++;
    }

    if(!p) return false;
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->val = val;
    new_node->next = p->next;
    p->next = new_node;
    return true;
}

bool delete_at(Node* head, int pos) {
    if(head->next == NULL) return false;
    if(pos < 0) return false;
    Node* prev = head;
    Node* curr = head->next;
    int i = 0;
    while(curr && i < pos) {
        prev = curr;
        curr = curr->next;
        i++;
    }
    if(curr == NULL) return false;
    prev->next = curr->next;
    free(curr);
    return true;
}

void reverse(Node* head) {
    if(head->next == NULL) return;
    Node* p = head->next;
    Node* prev = NULL;
    while(p) {
        Node* next = p->next;
        p->next = prev;
        prev = p;
        p = next;
    }
    head->next = prev;
}

void print_list(Node* head) {
    if(head->next == NULL) {
    printf("NULL\n");
    return;
    }
    head = head->next;
    printf("head->");
    while(head) {
        printf("%d->", head->val);
        head = head->next;
    }
    printf("NULL\n");
}

int find(Node* head, int val) {
    if(head->next == NULL) return -1;
    Node* p = head->next;
    int index = 0;
    while(p) {
        if(p->val == val) return index;
        p = p->next;
        index++;
    }
    return -1;
}

int main(void) {
    Node* head = NULL;
    init_node(&head);
    for(int i = 0;i < 5; i++) {
        insert_at(head, i, i + 1);
    }
    print_list(head);

    reverse(head);
    print_list(head);

    if(delete_at(head, 1)) printf("deleted  ");
    print_list(head);
    printf("%d\n", find(head, 1));
}