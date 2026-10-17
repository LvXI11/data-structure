#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>

typedef struct HTree{
    int val;
    struct HTree *lchild, *rchild;
}HTree;

int count;
int size;
bool create_node(int* arr, HTree* p[], int n){
    size = n;
    count = 0;
    for(int i = 0;i < n; i++){
        HTree* new_node = (HTree*)malloc(sizeof(HTree));
        if(!new_node) return false;
        new_node->val = arr[i];
        new_node->lchild = new_node->rchild = NULL;
        p[i] = new_node;
        count++;
    }
    return count == size;
}

void sift_up(HTree* p[], HTree* h){
    p[count++] = h;
    int i = count - 1;
    while(i > 0 && p[i]->val < p[(i - 1) / 2]->val){
        HTree* temp = p[i];
        p[i] = p[(i - 1) / 2];
        p[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

void sift_down(HTree* p[], int i){
    while(2 * i + 1 < count){
        int smaller = 2 * i + 1;
        if(2 * i + 2 < count && p[2 * i + 2]->val < p[smaller]->val) smaller = 2 * i + 2;
        if(p[i]->val <= p[smaller]->val) break;
        HTree* temp = p[i];
        p[i] = p[smaller];
        p[smaller] = temp;
        i = smaller;
    }
}

void build_heap(HTree* p[]){
    for(int i = size / 2 - 1;i >= 0; i--)
    sift_down(p, i);
}

bool pop(HTree* p[], HTree** a, HTree** b){
    if(count < 2) return false;
    *a = p[0];
    count--;
    p[0] = p[count];
    sift_down(p, 0);
    *b = p[0];
    count--;
    p[0] = p[count];
    sift_down(p, 0);
    return true;
}

HTree* build_tree(HTree* p[]){
    HTree *a, *b;
    while(pop(p, &a, &b)){
        HTree* new_node = (HTree*)malloc(sizeof(HTree));
        if(!new_node) return NULL;
        new_node->val = a->val + b->val;
        new_node->lchild = a;
        new_node->rchild = b;
        sift_up(p, new_node);
    }
    return p[0];
}

int wpl(HTree* root, int depth){
    if(!root) return 0;

    if(!root->lchild && !root->rchild){
        return root->val * depth;
    }
    return wpl(root->lchild, depth + 1) + wpl(root->rchild, depth + 1);
}

void print_code(HTree* root, char* code, int depth){
    if(!root) return;
    
    if(!root->lchild && !root->rchild){
        code[depth] = '\0';
        printf("%s  %2d\n", code, root->val);
        return;
    }

    code[depth] = '0';
    print_code(root->lchild, code, depth + 1);

    code[depth] = '1';
    print_code(root->rchild, code, depth + 1);
}