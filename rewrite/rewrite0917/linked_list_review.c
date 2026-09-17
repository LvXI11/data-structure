#include<stdio.h>
#include<stdlib.h>

/* ==================================================================
   一、双链表（哑头节点版）—— 8/27 学的，今天第 21 天
   ================================================================== */

typedef struct DNode{
    int data;
    struct DNode *prior, *next;
}DNode;

/* ---------- 样板，不用动 ---------- */

DNode* init_dlist(){                       // 建哑头节点（不存数据）
    DNode* head=(DNode*)malloc(sizeof(DNode));
    head->prior=head->next=NULL;
    return head;
}

void insert_tail(DNode* head,int e){        // 尾插
    DNode* p=head;
    while(p->next) p=p->next;
    DNode* n=(DNode*)malloc(sizeof(DNode));
    n->data=e;
    n->next=NULL;
    n->prior=p;
    p->next=n;
}

void print_dlist(DNode* head){
    printf("正向: ");
    for(DNode* p=head->next; p; p=p->next) printf("%d ",p->data);
    printf("\n反向: ");
    if(head->next){                        // 空链表要判一下，否则下面会解引用 NULL
        DNode* p=head->next;
        while(p->next) p=p->next;          // 走到尾巴
        for(; p!=head; p=p->prior) printf("%d ",p->data);
    }
    printf("\n");
}

/* ---------- 你写的：删除第一个值为 e 的节点 ---------- */
void delete_dnode(DNode* head,int e){
    DNode* p=head->next;// ① 从哪开始找？（哑头节点里没有数据）
    while(p){
        if(p->data==e) break;
        p=p->next;
    }
    if(!p)return;
    p->prior->next=p->next;
    if(p->next) p->next->prior=p->prior;
    free(p);
}

/* ==================================================================
   二、循环链表 —— 8/27 学的，今天第 21 天
   ================================================================== */

typedef struct CNode{
    int data;
    struct CNode *next;
}CNode;

/* ---------- 样板，不用动 ---------- */

void insert_circular(CNode** head,int e){   // 尾插（head 是哑头节点）
    CNode* n=(CNode*)malloc(sizeof(CNode));
    n->data=e;
    CNode* p=*head;
    while(p->next!=*head) p=p->next;        // 注意终止条件
    p->next=n;
    n->next=*head;
}

/* ---------- 你写的 ---------- */

void init_circular(CNode** head){
    *head=(CNode*)malloc(sizeof(CNode));
    if(!*head)return;
    (*head)->next=head;
}

void print_circular(CNode* head){
    CNode* p=head->next;
    while(p!=head){
        printf("%d ",p->data);
        p=p->next;
    }
}

/* ==================================================================
   main
   ================================================================== */

int main(void){
    /* ---- 双链表 ---- */
    printf("===== 双链表 =====\n");
    DNode* h=init_dlist();
    int a[]={10,20,30,40};
    for(int i=0;i<4;i++) insert_tail(h,a[i]);
    printf("原始   ");
    print_dlist(h);

    delete_dnode(h,30);                     // 删中间节点
    printf("删30后 ");
    print_dlist(h);

    delete_dnode(h,40);                     // 删【尾节点】← 最容易错的
    printf("删40后 ");
    print_dlist(h);

    delete_dnode(h,99);                     // 删不存在的
    printf("删99后 ");
    print_dlist(h);

    /* ---- 循环链表 ---- */
    printf("\n===== 循环链表 =====\n");
    CNode* c=NULL;
    init_circular(&c);
    printf("空的循环链表遍历: ");
    print_circular(c);                      // 应该是空的
    printf("（上面这行不该崩，也该什么都不打印）\n");

    int b[]={1,2,3,4,5};
    for(int i=0;i<5;i++) insert_circular(&c,b[i]);
    printf("插入1..5后: ");
    print_circular(c);

    system("pause");
    return 0;
}
