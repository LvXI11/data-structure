#include<stdio.h>
#include<stdlib.h>

typedef struct HTNode{
    int w;
    struct HTNode *lchild,*rchild;
}HTNode;

int size=0;
void create_node(HTNode* arr[],int a[],int n){
    size=n;
    for(int i=0;i<n;i++){
        HTNode* new_node=(HTNode*)malloc(sizeof(HTNode));
        if(!new_node)return;
        new_node->w=a[i];
        new_node->lchild=new_node->rchild=NULL;
        arr[i]=new_node;
    }
}

void sift_up(HTNode* arr[],HTNode* e){
    arr[size++]=e;
    int i=size-1;
    while(i>0&&arr[i]->w<arr[(i-1)/2]->w){
        HTNode* temp=arr[i];
        arr[i]=arr[(i-1)/2];
        arr[(i-1)/2]=temp;
        i=(i-1)/2;
    }
}

void sift_down(HTNode* arr[],int i){
    while(2*i+1<size){
        int small=2*i+1;
        if(2*i+2<size&&arr[2*i+2]->w<arr[small]->w)
        small=2*i+2;
        if(arr[i]->w<=arr[small]->w) break;
        HTNode* temp=arr[i];
        arr[i]=arr[small];
        arr[small]=temp;
        i=small;
    }
}

void build_heap(HTNode* arr[]){
    for(int i=size/2-1;i>=0;i--)
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
    HTNode* a;
    HTNode* b;
    while(pop(arr,&a,&b)){
        HTNode* new_node=(HTNode*)malloc(sizeof(HTNode));
        if(!new_node)return;
        new_node->w=a->w+b->w;
        new_node->lchild=a;
        new_node->rchild=b;
        sift_up(arr,new_node);
    }
    *H=arr[0];
}

int wpl(HTNode* H){
    if(!H)return 0;
    if(!H->lchild&&!H->rchild)return 0;
    return H->w+wpl(H->lchild)+wpl(H->rchild);
}

void print_code(HTNode* H,char code[],int depth){
    if(!H)return;
    if(!H->lchild&&!H->rchild){
        code[depth]='\0';
        printf("%2d : %s\n",H->w,code);
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
    create_node(arr, w, 8);      
    build_heap(arr);             

    HTNode* H = NULL;
    build_tree(arr, &H);

    printf("WPL = %d\n", wpl(H));

    char code[32];
    print_code(H, code, 0);

    return 0;
}