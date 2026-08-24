#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int ElemType;
#define MAX_LEN 100

typedef struct{
    ElemType* elem;
    int len;
}SQList;

void modify_sqlist(SQList* L,ElemType e,ElemType new);
void List_delete(SQList* L,ElemType e);
bool search_elem(SQList* L,ElemType e);
void add_elem(SQList* L,ElemType e);
void destroy_sqlist(SQList* L);
void init_sqlist(SQList* L);
void insert_elem(SQList* L,ElemType e,int id);
void print_list(SQList* L);
int main(void){
    SQList L;
    bool receive;
    init_sqlist(&L);
    add_elem(&L,7);
    add_elem(&L,8);
    print_list(&L);
    insert_elem(&L,6,0);
    print_list(&L);
    List_delete(&L,8);
    print_list(&L);
    receive=search_elem(&L,7);
    receive=search_elem(&L,3);
    modify_sqlist(&L,7,9);
    print_list(&L);
    receive=search_elem(&L,9);
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
    if(!L->len){
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
    L->elem[L->len]=e;
    L->len++;
    printf("添加成功\n");
}

bool search_elem(SQList* L,ElemType e){
    if(!L->len){
        printf("顺序表为空\n");
        return false;
    }
    for(int i=0;i<L->len;i++){
        if(e==L->elem[i]){
            printf("找到了%d,序号为%d\n",e,i+1);
            return true;
        }
    }
    printf("未找到\n");
    return false;
}

void List_delete(SQList* L,ElemType e){
    if(search_elem(L,e)){
        for(int i=0;i<L->len;i++){
        if(e==L->elem[i]){
            if(!(i==L->len-1)){
                for(int j=i;j<L->len-1;j++)
                L->elem[j]=L->elem[j+1];
            }
            L->len--;
            break;
        }
    }
    printf("删除成功\n");
    }
}

void modify_sqlist(SQList* L,ElemType e,ElemType new){
    if(search_elem(L,e)){
        for(int i=0;i<L->len;i++){
        if(e==L->elem[i]){
            L->elem[i]=new;
            printf("修改成功\n");
        }
    }
}
}
void insert_elem(SQList* L,ElemType e,int id){
    if(id<0||id>L->len){
        printf("输入错误\n");
        return;
    }
    if(!L->len){
        printf("顺序表为空\n");
        return;
    }
    if(L->len==MAX_LEN){
        printf("已存满\n");
        return;
    }
    for(int i=L->len-1;i>=id;i--)
        L->elem[i+1]=L->elem[i];
    L->elem[id]=e;
    L->len++;
    printf("插入成功\n");

}

void print_list(SQList* L){
    if(!L->len){
        printf("顺序表为空\n");
        return;
    }
    for(int i=0;i<L->len;i++)
        printf("id:%d elem:%d\n",i+1,L->elem[i]);
}