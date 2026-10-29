#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int val;
    struct Node *next;
}Node;

Node* create(int n) {
    if(n < 0) return NULL;

    Node* head = (Node*)malloc(sizeof(Node));
    if(!head) return NULL;

    head->val = 1;
    head->next = head;
    Node* p = head;

    for(int i = 2;i <= n; i++) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        if(!new_node) return NULL;
        new_node->val = i;
        new_node->next = head;
        p->next = new_node;
        p = new_node;
    }

    return head;
}

void print_all(Node* head) {
    if(head == NULL) {
        printf("空表\n");
        return;
    }

    printf("head->");
    Node* p = head;
    do{
        printf("%d->", p->val);
        p = p->next;
    }while(p != head);

    printf("head\n");
}

void insert_after(Node* head, int target, int val) {
    Node* p = head;
    while(p->next != head && p->val != target) {
        p = p->next;
    }

    if(p->val != target) return;
    Node* new_node = (Node*)malloc(sizeof(Node));
    if(!new_node) return;
    new_node->val = val;

    new_node->next = p->next;
    p->next = new_node;

}

Node* delete_val(Node* head, int val) {
    if(head->val == val) {
        if(head->next == head) {
            free(head);
            return NULL;
        }
        
        Node* tail = head;
        while(tail->next != head) tail = tail->next;
        Node* newHead = head->next;
        tail->next = newHead;
        free(head);
        return newHead;
    }

    Node* prev = head;
    Node* curr = head->next;
    while(curr->next != head) {
        if(curr->val == val) {
            prev->next = curr->next;
            free(curr);
            return head;
        }
        prev = curr;
        curr = curr->next;
    }

    return head;
}

int count(Node* head) {
    if(head == NULL) return 0;
    Node* p = head;
    int count = 0;

    do{
        count++;
        p = p->next;
    }while(p != head);

    return count;
}

void free_all(Node* head) {
    Node* p = head;
    while(p->next != head){
        Node* del = p;
        p = p->next;
        free(del);
    }
    free(p);

}

int main(void) {
    Node* head = create(5);
    printf("create 1..5       -> "); print_all(head);
    printf("count             -> %d\n", count(head));

    insert_after(head, 3, 99);
    printf("insert 99 after 3 -> "); print_all(head);

    head = delete_val(head, 99);
    printf("delete 99         -> "); print_all(head);

    head = delete_val(head, 1);
    printf("delete head(1)    -> "); print_all(head);
    printf("count             -> %d\n", count(head));

    free_all(head);
    return 0;
}