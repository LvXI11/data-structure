#include<stdio.h>
#include<stdlib.h>

typedef struct HTNode{
    int weight;
    struct HTNode *lchild,*rchild;
}HTNode;

int size=0;

void create_node(int w[],int n,HTNode* arr[]){
    size=n;
    for(int i=0;i<n;i++){
        HTNode* new_node=(HTNode*)malloc(sizeof(HTNode));
        if(!new_node)return;
        new_node->weight=w[i];
        new_node->lchild=new_node->rchild=NULL;
        arr[i]=new_node;
    }
}

void sift_up(HTNode* arr[],HTNode* e){
    arr[size++]=e;
    int i=size-1;
    while(i>0&&arr[(i-1)/2]->weight>arr[i]->weight){
        HTNode* temp=arr[(i-1)/2];
        arr[(i-1)/2]=arr[i];
        arr[i]=temp;
        i=(i-1)/2;
    }
}

void sift_down(HTNode* arr[],int i){
    while(2*i+1<size){
        int small=2*i+1;
        if(2*i+2<size&&arr[small]->weight>arr[2*i+2]->weight)
        small=2*i+2;
        if(arr[i]->weight<arr[small]->weight) break;
        HTNode* temp=arr[i];
        arr[i]=arr[small];
        arr[small]=temp;
        i=small;
    }
}

void build_heap(HTNode* arr[],int n){
    for(int i=n/2-1;i>=0;i--)
    sift_down(arr,i);
}

int pop(HTNode* arr[],HTNode** a,HTNode** b){
    if(size<2)return 0;
    *a=arr[0];
    arr[0]=arr[size-1];
    size--;
    sift_down(arr,0);
    *b=arr[0];
    arr[0]=arr[size-1];
    size--;
    sift_down(arr,0);
    return 1;
}

void build_tree(HTNode* arr[],HTNode** H){
    HTNode *a,*b;
    while(pop(arr,&a,&b)){
    int w=a->weight+b->weight;
    HTNode* new_node=(HTNode*)malloc(sizeof(HTNode));
    if(!new_node)return;
    new_node->weight=w;
    new_node->lchild=a;
    new_node->rchild=b;
    sift_up(arr,new_node);
    }
    *H=arr[0];
}

int wpl(HTNode* H){
    if(!H) return 0;
    if(!H->lchild&&!H->rchild) return 0;
    return H->weight+wpl(H->rchild)+wpl(H->lchild);
}

void print_code(HTNode* H,char code[],int depth){
    if(!H)return;
    if(!H->lchild&&!H->rchild){
        code[depth]='\0';
        printf("%2d : %s\n",H->weight,code);
        return;
    }

    code[depth]='0';
    print_code(H->lchild,code,depth+1);
    code[depth]='1';
    print_code(H->rchild,code,depth+1);
}

int main(void){
    int w[] = {5, 29, 7, 8, 14, 23, 3, 11};
    HTNode* arr[100];
    create_node(w,8,arr);
    build_heap(arr,8);
    HTNode* H=NULL;
    build_tree(arr,&H);
    printf("%d",wpl(H));
    printf("\n");
    char code[32];
    print_code(H,code,0);
    return 0;
}