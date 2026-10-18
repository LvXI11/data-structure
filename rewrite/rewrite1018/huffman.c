#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>

typedef struct Tree{
    int val;
    struct Tree *lchild, *rchild;
}Tree;

int size;

bool create_node(int* s, Tree* p[], int n) {
    size = n;
    for(int i = 0;i < n; i++) {
        Tree* new_node = (Tree*)malloc(sizeof(Tree));
        if(!new_node) return false;
        new_node->val =s[i];
        new_node->lchild = new_node->rchild = NULL;
        p[i] = new_node;
    }
    return true;
}

void sift_up(Tree* p[], Tree* t) {
    p[size++] = t;
    int i = size - 1;
    while(i > 0 && p[i]->val < p[(i - 1) / 2]->val) {
        Tree* temp = p[i];
        p[i] = p[(i - 1) / 2];
        p[(i - 1) /2]= temp;
        i = (i - 1) / 2;
    }
}

void sift_down(Tree* p[], int i) {
    while(2 * i + 1 < size) {
        int smaller = 2 * i + 1;
        if(2 * i + 2 < size && p[2 * i + 2]->val < p[smaller]->val) smaller = 2 * i + 2;
        if(p[i]->val <= p[smaller]->val) break;
        Tree* temp = p[i];
        p[i] = p[smaller];
        p[smaller] = temp;
        i = smaller;
    }
}

void build_heap(Tree* p[]) {
    for(int i = size / 2 - 1;i >= 0; i--)
    sift_down(p, i);
}

bool pop(Tree* p[], Tree** a, Tree** b){
    if(size < 2) return false;
    *a = p[0];
    p[0] =p[--size];
    sift_down(p, 0);
    *b = p[0];
    p[0] = p[--size];
    sift_down(p, 0);
    return true;
}

Tree* build_tree(Tree* p[]){
    Tree *a, *b;
    while(pop(p, &a, &b)){
        Tree* new_node = (Tree*)malloc(sizeof(Tree));
        if(!new_node) return NULL;
        new_node->val = a->val + b->val;
        new_node->lchild = a; new_node->rchild = b;
        sift_up(p, new_node);
    }
    return p[0];
}

int wpl(Tree* root, int depth){
    if(!root) return 0;

    if(!root->lchild && !root->rchild) {
        return depth * root->val;
    }

    return wpl(root->lchild, depth + 1) + wpl(root->rchild, depth + 1);
}

void print_code(Tree* root, char* code, int depth){
    if(!root) return;
    if(!root->lchild && !root->rchild) {
        code[depth] = '\0';
        printf("%s = %d\n", code, root->val);
        return;
    }

    code[depth] = '0';
    print_code(root->lchild, code, depth + 1);

    code[depth] = '1';
    print_code(root->rchild, code, depth + 1);
}