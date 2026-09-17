#include<stdio.h>
#define MAXV 100
#define MAXE 1000

typedef struct{
    int u,v,w;
}Edge;

Edge edges[MAXE];
int parent[MAXV];

void init_uf(int n){//初始化，每个顶点都是自己的老大
    for(int i=0;i<n;i++)
    parent[i]=i;
}

int find(int x){//找老大，并顺手把自己挂到老大的根下,下次找老大的时候时间复杂度几乎接近O(1)
    if(parent[x]!=x){
        parent[x]=find(parent[x]);
    }
    return parent[x];
}

void union_set(int a,int b){//合并派
    int ra=find(a); int rb=find(b);
    if(ra!=rb) parent[ra]=rb;
}

void insert_sort(Edge arr[],int n){
    for(int i=1;i<n;i++){
        Edge x=arr[i];
        int j=i-1;
        while(j>=0&&arr[j].w>x.w){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=x;
    }
}

void kruskal(int n,int e){
    insert_sort(edges,e);
    
    int count=0; int total=0;
    for(int i=0;i<e;i++){
        int u=edges[i].u;
        int v=edges[i].v;
        int w=edges[i].w;

        if(find(u)!=find(v)){
            total+=w;
            union_set(u,v);
            count++;
            if(count==n-1) break;
        }
    }
    printf("最下生成树的总权：%d\n",total);
}