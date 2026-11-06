#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int val;
    int height;
    struct Node *l, *r;
}Node;

Node* createNode(int val) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->val = val;
    n->height = 1;
    n->l = n->r = NULL;
    return n;
}

int height(Node* t) { return t == NULL ? 0 : t->height; }
int max(int a, int b) { return a > b ? a : b; }
int bf(Node* t) { return t == NULL ? 0 : height(t->l) - height(t->r); }
void updateHeight(Node* t) { t->height = 1 + max(height(t->l), height(t->r)); }

Node* rotationRight(Node* y) {
    Node* x = y->l;
    Node* T2 = x->r;

     x->r = y;
    y->l = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node* rotationLeft(Node* x) {
    Node* y = x->r;
    Node* T2 = y->l;

    y->l = x;
    x->r = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Node* insert(Node* root, int val) {
    if(root == NULL) return createNode(val);

    if(val < root->val) root->l = insert(root->l, val);
    else if(val > root->val) root->r = insert(root->r, val);
    else return root;

    updateHeight(root);
    int b = bf(root);

    if(b > 1 && val < root->l->val) return rotationRight(root);
    if(b < -1 && val > root->r->val) return rotationLeft(root);

    if(b > 1 && val > root->l->val) {
        root->l = rotationLeft(root->l);
        return rotationRight(root);
    }
    if(b < -1 && val < root->r->val) {
        root->r = rotationRight(root->r);
        return rotationLeft(root);
    }
    return root;
}

void preorder(Node* root) {
    if(root == NULL) return;
    printf("%d ", root->val);
    preorder(root->l);
    preorder(root->r);
}

void inorder(Node* root) {
    if(root == NULL) return;
    inorder(root->l);
    printf("%d ", root->val);
    inorder(root->r);
}

int main(void) {
    Node* root = NULL;
    root = insert(root, 10); root = insert(root, 20); root = insert(root, 30);
    printf("10,20,30 : "); printf("根:%d", root->val); printf(" 前序:");
    preorder(root); printf("后序:"); inorder(root); printf(" 高:%d", height(root));
}

