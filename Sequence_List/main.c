#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;
#define MAX_LEN 100

typedef struct{
    ElemType* elem;
    int len;
}SQList;

void modify_sqlist(SQList* L,ElemType e,ElemType new);
void List_delete(SQList* L,ElemType e);
void search_elem(SQList* L,ElemType e);
void add_elem(SQList* L,ElemType e);
void destroy_sqlist(SQList* L);
void init_sqlist(SQList* L);

int main(void){
    SQList L;
    init_sqlist(&L);
    add_elem(&L,7);
    add_elem(&L,8);
    List_delete(&L,8);
    search_elem(&L,7);
    search_elem(&L,3);
    modify_sqlist(&L,7,9);
    search_elem(&L,9);
    destroy_sqlist(&L);
    printf("Done!\n");
    return 0;
}

void init_sqlist(SQList* L){
    L->elem=(ElemType*)malloc(MAX_LEN*sizeof(ElemType));
    if(L->elem==NULL){
        printf("内存分配失败\n");
        return;
    }
    L->len=0;
}

void destroy_sqlist(SQList* L){
    if(L->elem==NULL){
        printf("顺序表为空\n");
        return;
    }
    free(L->elem);
    printf("销毁成功\n");
}

void add_elem(SQList* L,ElemType e){
    if(L->len==MAX_LEN){
        printf("顺序表已满\n");
        return;
    }
    if(!L->len){
        L->elem[0]=e;
    }
    L->elem[L->len]=e;
    printf("添加成功\n");
}

void search_elem(SQList* L,ElemType e){
    if(L->len){
        printf("顺序表为空\n");
        return;
    }
    for(int i=0;i<L->len;i++){
        if(e==L->elem[i]){
            printf("找到了%d,序号为%d\n",e,i+1);
            return;
        }
    }
    printf("未找到\n");
}

void List_delete(SQList* L,ElemType e){
    search_elem(L,e);
    if(e==L->elem[L->len-1]){
        L->len--;
        printf("删除成功\n");
        return;
    }
    for(int i=0;i<L->len;i++){
        if(e==L->elem[i]){
            for(int j=i;j<L->len;j++)
            L->elem[j]=L->elem[j+1];
        }
    }
    printf("删除成功\n");
}

void modify_sqlist(SQList* L,ElemType e,ElemType new){
    search_elem(L,e);
    for(int i=0;i<L->len;i++){
        if(e==L->elem[i]){
            L->elem[i]=new;
            printf("修改成功\n");
        }
    }
}