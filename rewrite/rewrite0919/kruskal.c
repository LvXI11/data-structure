#include<stdio.h>
#define MAXV 100
#define MAXE 1000
typedef struct Edge{
    int u,v,w;
}Edge;

Edge edges[MAXE];
int parent[MAXE];

void init_uf(int n){
    for(int i=0;i<n;i++)
    parent[i]=i;
}

int find(int x){
    if(parent[x]!=x)
    parent[x]=find(parent[x]);
    return parent[x];
}

void union_set(int a,int b){
    int ra=find(a); int rb=find(b);
    if(ra!=rb) parent[ra]=rb;
}

void insert_sort(Edge arr[],int e){
    for(int i=0;i<e;i++){
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
    int count=0;
    int total=0;
    for(int i=0;i<e;i++){
        int u=edges[i].u;
        int v=edges[i].v;
        int w=edges[i].w;
        if(find(u)!=find(v)){
            printf("边 %d - %d 权 %d\n",u,v,w);
            total+=w;
            count++;
            union_set(u,v);
            if(count==n-1) break;
        }
    }
    printf("%d",total);
}