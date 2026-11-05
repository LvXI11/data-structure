#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int val;
    int height;
    struct Node *l, *r;
}Node;

int height(Node* t) { return t == NULL ? 0 : t->height; }
int bf(Node* t) { return t == NULL ? 0 : height(t->l) - height(t->r); }
int max2(int a, int b) { return a > b ? a : b; }
void updataHeight(Node* t) { if(t) t->height = 1 + max2(height(t->l), height(t->r)); }

Node* create_node(int val) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->val = val;
    n->height = 1;
    n->l = n->r = NULL;
    return n;
}

Node* rotateRight(Node* y) {
    Node* x = y->l;
    Node* b = x->r;

    x->r = y;
    y->l = b;

    updataHeight(y);
    updataHeight(x);
    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->r;
    Node* b = y->l;

    y->l = x;
    x->r = b;

    updataHeight(x);
    updataHeight(y);
    return y;
}

Node* insert(Node* t, int val) {
    if(t == NULL) return create_node(val);

    if(val < t->val)      t->l = insert(t->l, val);
    else if(val > t->val) t->r = insert(t->r, val);
    else return t;

    updataHeight(t);
    int b = bf(t);

    if(b > 1 && val < (t->l->val)) return rotateRight(t);
    if(b < -1 && val > (t->r->val)) return rotateLeft(t);

    if(b > 1 && val > (t->l->val)) {
        t->l = rotateLeft(t->l);
        return rotateRight(t);
    }
    if(b < -1 && val < (t->r->val)) {
        t->r = rotateRight(t->r);
        return rotateLeft(t);
    }

    return t;
}

void preOrder(Node *t) { if (!t) return; printf("%d ", t->val); preOrder(t->l); preOrder(t->r); }
void inOrder(Node *t)  { if (!t) return; inOrder(t->l);  printf("%d ", t->val); inOrder(t->r); }

Node *build(int *a, int n) {
    Node *root = NULL;
    for (int i = 0; i < n; i++) {
        root = insert(root, a[i]);
        printf("插入 %d 后：根=%d 高=%d 前序=", a[i], root->val, height(root));
        preOrder(root);
        printf("\n");
    }
    return root;
}

int main(void) {
    int c1[] = {10, 20, 30};      // RR → 左旋
    int c2[] = {30, 20, 10};      // LL → 右旋
    int c3[] = {30, 10, 20};      // LR → 先左后右
    int c4[] = {10, 30, 20};      // RL → 先右后左
    int c5[] = {10, 20, 30, 40, 50, 25};  // 连续插入，多次旋转

    printf("=== RR 10,20,30 ===\n");    Node *r1 = build(c1, 3); printf("中序="); inOrder(r1); printf("\n\n");
    printf("=== LL 30,20,10 ===\n");    Node *r2 = build(c2, 3); printf("中序="); inOrder(r2); printf("\n\n");
    printf("=== LR 30,10,20 ===\n");    Node *r3 = build(c3, 3); printf("中序="); inOrder(r3); printf("\n\n");
    printf("=== RL 10,30,20 ===\n");    Node *r4 = build(c4, 3); printf("中序="); inOrder(r4); printf("\n\n");
    printf("=== 连续 10,20,30,40,50,25 ===\n"); Node *r5 = build(c5, 6); printf("中序="); inOrder(r5); printf("\n");
    return 0;
}