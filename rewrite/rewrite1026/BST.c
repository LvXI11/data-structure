#include<stdio.h>
#include<stdlib.h>

typedef struct Tree{
    int val;
    struct Tree *lchild, *rchild;
}Tree;

Tree* create_node(int val) {
    Tree* new_node = (Tree*)malloc(sizeof(Tree));
    if(!new_node) return NULL;
    new_node->val = val;
    new_node->lchild = new_node->rchild = NULL;
    return new_node;
}

Tree* build_tree(Tree* root, int val) {
    if(!root) return create_node(val);

    if(val < root->val) { root->lchild = build_tree(root->lchild, val); }
    if(val > root->val) { root->rchild = build_tree(root->rchild, val); }
    return root;
}

Tree* search(Tree* root, int val) {
    if(!root) return NULL;
    if(root->val == val) {
        return root;
    }

    if(val < root->val) { return search(root->lchild, val); }
    else { return search(root->rchild, val); }
}

Tree* get_min(Tree* root) {
    while(root->lchild) root = root->lchild;
    return root;
}

Tree* delete_node(Tree* root, int val) {
    if(!root) return NULL;
    if(val < root->val) { root->lchild = delete_node(root->lchild, val); return root; }
    if(val > root->val) { root->rchild = delete_node(root->rchild, val); return root; }

    if(!root->lchild && !root->rchild) {
        free(root);
        return NULL;
    }

    if(!root->lchild) { Tree* right = root->rchild; free(root); return right; }
    if(!root->rchild) { Tree* left = root->lchild; free(root); return left; }

    Tree* succ = get_min(root->rchild);
    root->val = succ->val;
    root->rchild = delete_node(root->rchild, succ->val);
    return root;
}