#include<stdio.h>
#define MAXV 100
#define MAXE 1000

typedef struct Edge{
    int w,u,v;
}Edge;

Edge edges[MAXE];
int parent[MAXV];

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

void shell_sort(Edge arr[],int e){
    int gap=e/2;
    for(;gap>=1;gap/=2){
        for(int i=gap;i<e;i++){
            Edge x=arr[i];
            int j=i-gap;
            while(j>=0&&arr[j].w>x.w){
                arr[j+gap]=arr[j];
                j-=gap;
            };
            arr[j+gap]=x;
        }
    }
}

void kruskal(int n,int e){
    shell_sort(edges,e);
    int count=0;
    int total=0;

    for(int i=0;i<e;i++){
        int v=edges[i].v;
        int u=edges[i].u;
        int w=edges[i].w;

        if(find(u)!=find(v)){
            printf("边 %d %d 权 %d\n",u,v,w);
            union_set(u,v);
            total+=w;
            count++;
        }
        if(count==n-1) break;
    }
    printf("总权:%d\n",total);
}