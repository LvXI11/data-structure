#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct DList{
    int val;
    struct DList *prev, *next;
    int size;
}DList;

void init(DList* D) {
    D->prev = D->next = NULL;
    D->size = 0;
}

bool insert(DList* D, int val, int pos) {
    if(pos < 0 || pos > D->size) return false;
    DList* p = D;
    int i = 0;
    while(i < pos) {
        p = p->next;
        i++;
    }

    DList* new_node = (DList*)malloc(sizeof(DList));
    if(!new_node) return false;
    new_node->val = val;
    new_node->next = p->next;
    new_node->prev = p;
    if(p->next) p->next->prev = new_node;
    p->next = new_node;
    D->size++;
    return true;
}

bool delete_at(DList* D, int pos, int* rec) {
    if(pos < 0 || pos >= D->size) return false;
    DList* p = D->next;
    int i = 0;
    while(i < pos) {
        p = p->next;
        i++;
    }
    *rec = p->val;
    p->prev->next = p->next;
    if(p->next) p->next->prev = p->prev;
    D->size--;
    return true;
}

void print(DList* D) {
    DList* p = D->next;
    for(int i = 0;i < D->size; i++) {
        printf("%d ", p->val);
        p = p->next;
    }
}

void rprintf(DList* D) {
    DList* tail = D->next;
    while(tail && tail->next) tail = tail->next;
    for(int i = 0;i < D->size; i++) {
        printf("%d ", tail->val);
        tail = tail->prev;
    }
}

int main(void) {
    DList D;
    init(&D);

    printf("--- ① 空链表插第一个（测 pos=0 空链）---\n");
    insert(&D, 1, 0);
    print(&D); printf("   |   "); rprintf(&D); printf("\n");

    printf("--- ② 尾插 2 3 4 5（测 pos=size）---\n");
    for (int v = 2; v <= 5; v++) {
        insert(&D, v, D.size);
    }
    print(&D); printf("   |   "); rprintf(&D); printf("\n");

    printf("--- ③ 按位插：位置 2 插 99 ---\n");
    insert(&D, 99, 2);
    print(&D); printf("   |   "); rprintf(&D); printf("\n");

    printf("--- ④ 删位置 2 ---\n");
    int rec = -1;
    if (delete_at(&D, 2, &rec)) printf("删掉了 %d\n", rec);
    print(&D); printf("   |   "); rprintf(&D); printf("\n");

    printf("--- ⑤ 边界 ---\n");
    printf("insert pos=99 -> %d（应 0）\n", (int)insert(&D, 7, 99));
    printf("delete pos=99 -> %d（应 0）\n", (int)delete_at(&D, 99, &rec));

    printf("--- size = %d ---\n", D.size);
    return 0;
}