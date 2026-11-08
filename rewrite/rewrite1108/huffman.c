#include<stdio.h>
#include<stdlib.h>

typedef struct HTree{
    int val;
    struct HTree *l, *r;
}HTree;

int size;

void createNode(int* a, HTree* p[], int n) {
    size = n;
    for(int i = 0;i < n; i++) {
        HTree* h = (HTree*)malloc(sizeof(HTree));
        h->val = a[i];
        h->l = h->r = NULL;
        p[i] = h;
    }
}

void siftUp(HTree* p[], HTree* h) {
    p[size++] = h;
    int i = size - 1;
    while(i > 0 && p[i]->val < p[(i - 1) / 2]->val) {
        HTree* temp = p[i];
        p[i] = p[(i - 1) / 2];
        p[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

void siftDown(HTree* p[], int i) {
    while(2 * i + 1 < size) {
        int smaller = 2 * i + 1;
        if(2 * i + 2 < size && p[smaller]->val > p[2 * i + 2]->val) smaller = 2 * i + 2;
        if(p[i]->val <= p[smaller]->val) break;
        HTree* temp = p[i];
        p[i] = p[smaller];
        p[smaller] = temp;
        i = smaller;
    }
}

void buildHeap(HTree* p[]) {
    for(int i = size / 2 - 1;i >= 0; i--)
    siftDown(p, i);
}

int pop(HTree* p[], HTree** a, HTree** b) {
    if(size < 2) return 0;
    *a = p[0];
    p[0] = p[--size];
    siftDown(p, 0);

    *b = p[0];
    p[0] = p[--size];
    siftDown(p, 0);

    return 1;
}

HTree* buildTree(HTree* p[]) {
    HTree* a; HTree* b;
    while(pop(p, &a, &b)) {
        HTree* h = (HTree*)malloc(sizeof(HTree));
        h->val = a->val + b->val;
        h->l = a; h->r = b;
        siftUp(p, h);
    }

    return p[0];
}

int wpl(HTree* root, int depth) {
    if(!root) return 0;

    if(!root->l && !root->r) {
        return depth * root->val;
    }

    return wpl(root->l, depth + 1) + wpl(root->r, depth + 1);
}

void printCode(HTree* root, char* code, int depth) {
    if(!root) return;

    if(!root->l && !root->r) {
        code[depth] = '\0';
        printf("%s, %d\n", code, root->val);
        return;
    }

    code[depth] = '0';
    printCode(root->l, code, depth + 1);

    code[depth] = '1';
    printCode(root->r, code, depth + 1);
}