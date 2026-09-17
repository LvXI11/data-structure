#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int ElemType;

typedef struct Node{
    ElemType e;
    struct Node* next;
}Node;

void init_Node(Node** N){
    *N=(Node*)malloc(sizeof(Node));
    if(!*N)exit(EXIT_FAILURE);
    (*N)->next=*N;
}

bool is_empty(Node* N){
    return N->next==N;
}

int get_len(Node* N){
    int count=0;
    Node* p=N->next;
    while(p!=N){
        count++;
        p=p->next;
    }
    return count;
}

bool insert_elem(Node* N,int pos,ElemType e){
    if(pos<1||pos>get_len(N)+1)return false;
    Node* pre=N;
    int i=0;
    while(pre&&i<pos-1){
        pre=pre->next;
        i++;
    }
    if(!pre)return false;
    Node* new_node=(Node*)malloc(sizeof(Node));
    if(!new_node)return false;
    new_node->e=e;
    new_node->next=pre->next;
    pre->next=new_node;
    return true;
}

bool delete_elem(Node* N,ElemType e){
    if(is_empty(N))return false;
    Node* prev=N;
    Node* cur=N->next;
    bool deleted=false;
    while(cur!=N){
        if(cur->e==e){
            prev->next=cur->next;
            free(cur);
            cur=prev->next;
            deleted=true;
        }
        else{
            prev=cur;
            cur=cur->next;
        }
    }
    return deleted;
}

void out_by_number(Node* N,int n,int m){
    Node* prev=N;
    Node* cur=N->next;
    printf("出圈者:");
    while(get_len(N)>1){
        for(int i=0;i<m-1;i++){
            prev=cur;
            cur=cur->next;
            if(cur==N){
                prev=N;
                cur=N->next;
            }
        }
        printf("%d ",cur->e);
        prev->next=cur->next;
        free(cur);
        cur=prev->next;
        if(cur==N){
            prev=N;
            cur=N->next;
        }
    }
    printf("\n幸存者:%d\n",N->next->e);
}
int main(void){
    Node* N;
    init_Node(&N);
    for(int i=5;i>=1;i--){
        insert_elem(N,1,i);
    }
    out_by_number(N,5,2);
    return 0;
}