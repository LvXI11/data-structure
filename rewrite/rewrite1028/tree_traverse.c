#include<stdio.h>
#include<stdlib.h>

typedef struct Tree{
    int val;
    struct Tree *lchild, *rchild;
}Tree;

typedef struct Stack{
    Tree* data[100];
    int top;
}Stack;

typedef struct Queue{
    Tree* data[100];
    int front, rear;
}Queue;

void init_stack(Stack* S) { S->top = -1; }
void push(Stack* S, Tree* t) { S->data[++S->top] = t; }
Tree* pop(Stack* S) { return S->data[S->top--]; }
int stack_empty(Stack* S) { return S->top == -1; }

void init_queue(Queue* Q) { Q->front = Q->rear = 0; }
void enqueue(Queue* Q, Tree* t) { Q->data[Q->rear++] = t; }
Tree* dequeue(Queue* Q) { return Q->data[Q->front++]; }
int queue_empty(Queue* Q) { return Q->front == Q->rear; }

void init_tree(Tree* T) {
    T->lchild = T->rchild = NULL;
}

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

void preorder(Tree* root) {
    if(!root) return;
    printf("%d ", root->val);
    preorder(root->lchild);
    preorder(root->rchild);
}

void inorder(Tree* root) {
    if(!root) return;
    inorder(root->lchild);
    printf("%d ", root->val);
    inorder(root->rchild);
}

void postorder(Tree* root) {
    if(!root) return;
    postorder(root->lchild);
    postorder(root->rchild);
    printf("%d ", root->val);
}


void inorder_stack(Tree* root) {
    Stack S;
    init_stack(&S);
    Tree* p = root;

    while(p || !stack_empty(&S)) {
        if(p) {
            push(&S, p);
            p = p->lchild;
        } else {
            p = pop(&S);
            printf("%d ", p->val);
            p = p->rchild;
        }
    }
}

void level_order(Tree* root) {
    Queue Q;
    init_queue(&Q);
    enqueue(&Q, root);
    Tree* p = NULL;
    while(!queue_empty(&Q)) {
        p = dequeue(&Q);
        printf("%d ", p->val);
        if(p->lchild) enqueue(&Q, p->lchild);
        if(p->rchild) enqueue(&Q, p->rchild);
    }
}

int main(void) {
    Tree* root = NULL;
    int vals[] = {4, 2, 6, 1, 3, 5, 7};
    for (int i = 0; i < 7; i++) root = build_tree(root, vals[i]);

    printf("preorder     : "); preorder(root);      printf("\n");
    printf("inorder      : "); inorder(root);       printf("\n");
    printf("postorder    : "); postorder(root);     printf("\n");
    printf("inorder_stack: "); inorder_stack(root); printf("\n");
    printf("level_order  : "); level_order(root);   printf("\n");
    return 0;
}