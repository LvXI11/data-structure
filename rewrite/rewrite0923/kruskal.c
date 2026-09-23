#include<stdio.h>
#define MAXV 100
#define MAXE 1000

typedef struct Edge{
    int u,v,w;
}Edge;

int parent[MAXV];
Edge edges[MAXE];

void init_parent(int n){
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

void shell_sort(Edge arr[],int n){
    int gap=n/2;
    for(;gap>=1;gap/=2){
        for(int i=gap;i<n;i++){
            Edge x=arr[i];
            int j=i-gap;
            while(j>=0&&arr[j].w>x.w){
                arr[j+gap]=arr[j];
                j-=gap;
            }
            arr[j+gap]=x;
        }
    }
}

void kruskal(int n,int e){
    shell_sort(edges,e);
    int total=0;
    int count=0;
    for(int i=0;i<e;i++){
        int u=edges[i].u;
        int v=edges[i].v;
        int w=edges[i].w;

        if(find(u)!=find(v)){
            count++;
            printf("边 %d %d 权 %d\n",u,v,w);
            total+=w;
            union_set(u,v);
        }

        if(count==n)break;
    }
}