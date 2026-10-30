#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int val;
    struct Node *next;
}Node;

Node* init(Node* head) {
    head = (Node*)malloc(sizeof(Node));
    if(!head) return NULL;
    head->next = head;
    return head;
}

void create(Node* head, int n) {
    head->val = 1;
    Node* p = head;
    for(int i = 2;i <= n; i++) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        if(!new_node) return;
        new_node->val = i;
        new_node->next = head;
        p->next = new_node;
        p = new_node;
    }
}

void insert(Node* head, int val) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if(!new_node) return;
    new_node->val = val;
    new_node->next = head;
    head = new_node;
}

Node* delete_node(Node* head, int val) {
    if(head == NULL) return NULL;
    if(val == head->val) {
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

    while(curr != head) {
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

int len(Node* head) {
    if(head == NULL) return 0;
    Node* p = head;
    int count = 0;
    do{
        count++;
        p = p->next;
    }while(p != head);
    return count;
}

int josephus(int n, int k) {
    Node* head = NULL;
    head = init(head);

    create(head, n);
    Node* p = head;
    printf("淘汰者: ");
    while(len(head) != 1) {
        for(int i = 1;i < k; i++) {
            p = p->next;
        }
        int value = p->val;
        printf("%d ", value);
        p = p->next;
        head = delete_node(head, value);
    }
    printf("\n");
    return head->val;
}

int main(void) {
    int n = 7, k = 3;
    printf("n=%d k=%d\n", n, k);
    int last = josephus(n, k);
    printf("最后剩下: %d\n", last);
    return 0;
}