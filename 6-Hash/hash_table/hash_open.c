#include<stdio.h>

int table[11];
int used[11]={0};
int size=0;
void init_table(int n){
    for(int i=0;i<n;i++)
    table[i]=-1;
}

void hash_insert(int n,int key){
    int pos=key%n;
    if(table[pos]==-1){
        table[pos]=key;
        used[pos]=1;
        size++;
    }
    else{
        pos=(pos+1)%n;
        while(table[pos]!=-1){
            if(size==n){
                printf("表已满\n");
                return;
            }
            pos=(pos+1)%n;
        }
        table[pos]=key;
        used[pos]=1;
        size++;
    }

       
}

int hash_delete(int n,int key){
    int pos=key%n;
    if(!used[pos]) return 0;

    if(table[pos]==key){
        table[pos]=-1;
        size--;
        return 1;
    }
    else{
        int count=0;
        do{
            pos=(pos+1)%n;
            if(table[pos]==key){
                table[pos]=-1;
                size--;
                return 1;
            }
            count++;
        }while(count<n);
    }
    return 0;
}

int hash_search(int n,int key){
    int pos=key%n;
    if(!used[pos])return -1;

    if(table[pos]==key) return pos;
    else{
        int count=0;
        do{
            pos=(pos+1)%n;
            if(table[pos]==key)
            return pos;
            count++;
        }while(count<n);
    }
    return -1;
}

void print_table(int n){
    for(int j=0;j<n;j++)
    printf("%3d",used[j]);
    printf("\n");
    for(int i=0;i<n;i++)
    printf("%3d",table[i]);
    printf("\n");
}

int main(void){
    init_table(11);
    hash_insert(11,3);
    hash_insert(11,25);
    hash_insert(11,12);
    hash_insert(11,4);
    hash_insert(11,15);
    hash_insert(11,18);
    hash_insert(11,7);
    hash_insert(11,1);
    hash_insert(11,9);
    print_table(11);

    if(hash_delete(11,3)) printf("已删除%d\n",3);
    else printf("未找到%d\n",3);
    if(hash_search(11,3)!=-1) printf("查到了%d\n",3);
    else printf("未查到%d\n",3);
    hash_insert(11,36);
    print_table(11);

    if(hash_delete(11,12)) printf("已删除%d\n",12);
    else printf("未找到%d\n",12);
    if(hash_delete(11,25)) printf("已删除%d\n",25);
    else printf("未找到%d\n",25);
    print_table(11);
    return 0;
}