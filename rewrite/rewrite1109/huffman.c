#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int val;
    struct Node *l, *r;
}Node;

int size;
void createNode(int* a, Node* p[], int n) {
    size = n;
    for(int i = 0;i < size; i++) {
        Node* n = (Node*)malloc(sizeof(Node));
        n->val = a[i];
        n->l = n->r = NULL;
        p[i] = n;
    }
}

void siftUp(Node* p[], Node* n) {
    p[size++] = n;
    int i = size - 1;
    while(i > 0 && p[i]->val < p[(i - 1) / 2]->val) {
        Node* tmp = p[i];
        p[i] = p[(i - 1) / 2];
        p[(i - 1)  / 2] = tmp;
        i = (i - 1) / 2; 
    }
}

void siftDown(Node* p[], int i) {
    while(2 * i + 1 < size) {
        int smaller = 2 * i + 1;
        if(2 * i + 2 < size && p[2 * i + 2]->val < p[smaller]->val) smaller = 2 * i + 2;
        if(p[i]->val <= p[smaller]->val) break;
        Node* tmp = p[i];
        p[i] = p[smaller];
        p[smaller] = tmp;
        i = smaller;
    }
}

void buildHeap(Node* p[]) {
    for(int i = size / 2 - 1;i >= 0; i--)
    siftDown(p, i);
}

int pop(Node* p[], Node** a, Node** b) {
    if(size < 2) return 0;
    *a = p[0];
    p[0] = p[--size];
    siftDown(p, 0);

    *b = p[0];
    p[0] = p[--size];
    siftDown(p, 0);
    return 1;
}

Node* buildTree(Node* p[]) {
    Node* a; Node* b;
    while(pop(p, &a, &b)) {
        Node* n = (Node*)malloc(sizeof(Node));
        n->val = a->val + b->val;
        n->l = a; n->r = b;
        siftUp(p, n);
    }
    return p[0];
}

int wpl(Node* root, int depth) {
    if(!root) return 0;
    if(!root->l && !root->r) {
        return depth * root->val;
    }

    return wpl(root->l, depth + 1) + wpl(root->r, depth + 1);
}

void printCode(Node* root, char* code, int depth) {
    if(!root) return;
    if(!root->l && !root->r) {
        code[depth] = '\0';
        printf("%s, %d", code, root->val);
        return;
    }

    code[depth] = '0';
    printCode(root->l, code, depth + 1);
    code[depth] = '1';
    printCode(root->r, code, depth + 1);
}