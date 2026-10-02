#include<stdio.h>
#include<stdlib.h>

typedef struct Tree{
    int e;
    struct Tree *lchild,*rchild;
}Tree;

int size;

void create_node(int arr[],Tree* s[],int n){
    size=n;
    for(int i=0;i<n;i++){
        Tree* new_t=(Tree*)malloc(sizeof(Tree));
        if(!new_t) return;
        new_t->e=arr[i];
        new_t->lchild=new_t->rchild=NULL;
        s[i]=new_t;
    }
}

void sift_up(Tree* s[],Tree* t){
    s[size++]=t;
    int i=size-1;
    while(i>0&&s[i]->e<s[(i-1)/2]->e){
        Tree* temp=s[i];
        s[i]=s[(i-1)/2];
        s[(i-1)/2]=temp;
        i=(i-1)/2;
    }
}

void sift_down(Tree* s[],int i){
    while(2*i+1<size){
        int small=2*i+1;
        if(2*i+2<size&&s[2*i+2]->e<s[small]->e)
        small=2*i+2;
        if(s[i]->e<=s[small]->e) break;
        Tree* temp=s[i];
        s[i]=s[small];
        s[small]=temp;
        i=small;
    }
}

void build_heap(Tree* s[]){
    for(int i=size/2-1;i>=0;i--)
    sift_down(s,i);
}

int pop(Tree* s[],Tree** a,Tree** b){
    if(size<2) return 0;
    *a=s[0];
    s[0]=s[--size];
    sift_down(s,0);
    *b=s[0];
    s[0]=s[--size];
    sift_down(s,0);
    return 1;
}

Tree* build_tree(Tree* s[]){
    Tree* a;
    Tree* b;
    while(pop(s,&a,&b)){
        Tree* new_t=(Tree*)malloc(sizeof(Tree));
        if(!new_t) return NULL;
        new_t->e=a->e+b->e;
        new_t->lchild=a;
        new_t->rchild=b;
        sift_up(s,new_t);
    }
    return s[0];
}

int wpl(Tree* T,int depth){
    if(!T) return 0;
    if(!T->lchild&&!T->rchild) return depth*T->e;
    return wpl(T->lchild,depth+1)+wpl(T->rchild,depth+1);
}

void print_code(Tree* T,char code[],int depth){
    if(!T) return;
    if(!T->lchild&&!T->rchild){
        code[depth]='\0';
        printf("%s\n",code);
        return;
    }

    code[depth]='0';
    print_code(T->lchild,code,depth+1);

    code[depth]='1';
    print_code(T->rchild,code,depth+1);
}