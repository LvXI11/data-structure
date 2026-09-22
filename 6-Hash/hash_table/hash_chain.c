#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node{
    int key;
    struct Node* next;
}Node;

Node* table[11];

void init_table(int n){
    for(int i=0;i<n;i++)
    table[i]=NULL;
}

void hash_insert(int n,int key){
    int pos=key%n;
    Node* new_node=(Node*)malloc(sizeof(Node));
    if(!new_node)return;
    new_node->key=key;
    new_node->next=table[pos];
    table[pos]=new_node;
}

Node* hash_search(int n,int key){
    int pos=key%n;
    Node* p=table[pos];
    while(p){
        if(p->key==key)return p;
        p=p->next;
    }
    return NULL;
}

int hash_delete(int n,int key){
    int pos=key%n;
    if(!table[pos]) return 0;
    Node** pp=&table[pos];
    while(*pp){
        if((*pp)->key==key){
            Node* del=*pp;
            *pp=del->next;
            free(del);
            return 1;
        }
        pp=&(*pp)->next;
    }
    return 0;
}

void print_table(int n){
    for(int i=0;i<n;i++){
        if(!table[i]){
            printf("- ");
            continue;
        }
        Node* p=table[i];
        while(p){
            printf("%d ",p->key);
            p=p->next;
        }
    }
    printf("\n");
}

int main(void){
    hash_insert(11,25);
    hash_insert(11,4);
    hash_insert(11,15);
    hash_insert(11,12);
    hash_insert(11,6);
    hash_insert(11,9);
    hash_insert(11,7);
    hash_insert(11,18);
    hash_insert(11,3);
    print_table(11);

    if(hash_search(11,4)) printf("找到了%d\n",4);
    else printf("未找到\n");
    if(hash_search(11,1)) printf("找到了%d\n",1);
    else printf("未找到\n");
    if(hash_search(11,3)) printf("找到了%d\n",3);
    else printf("未找到\n");

    if(hash_delete(11,25)) printf("成功删除%d\n",25);
    else printf("未找到%d\n",25);
    if(hash_delete(11,7)) printf("成功删除%d\n",7);
    else printf("未找到%d\n",7);
    if(hash_delete(11,3)) printf("成功删除%d\n",3);
    else printf("未找到%d\n",3);
    if(hash_delete(11,12)) printf("成功删除%d\n",12);
    else printf("未找到%d\n",12);
    if(hash_delete(11,100)) printf("成功删除%d\n",100);
    else printf("未找到%d\n",100);
    if(hash_delete(11,26)) printf("成功删除%d\n",26);
    else printf("未找到%d\n",26);
    print_table(11);

    return 0;
}