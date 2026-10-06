#include<stdio.h>
#define MAXV 100
#define MAXE 1000

typedef struct Edge{
    int u,v,w;
}Edge;

Edge edge[MAXE];
int parent[MAXV];

void init_parent(int n){
    for(int i = 0;i < n; i++)
    parent[i] = i;
}

int find(int x){
    if(parent[x] != x)
    parent[x] = find(parent[x]);
    return parent[x];
}

void union_set(int a,int b){
    int ra = find(a); int rb = find(b);
    if(ra != rb) parent[ra] = rb;
}

void select_sort(Edge arr[],int e){
    for(int i = 0;i < e; i++){
        int min = i;
        for(int j = i+1;j < e; j++){
            if(arr[min].w > arr[j].w){
                min = j;
            }
        }
        Edge temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

void kruskal(int n, int e){
    select_sort(edge,e);
    int count = 0;
    int total = 0;

    for(int i = 0;i < e; i++){
        int u = edge[i].u;
        int v = edge[i].v;
        int w = edge[i].w;

        if(find(u) != find(v)){
            count++;
            total += w;
            printf("edge:%d - %d weight:%d\n",u,v,w);
            union_set(u,v);
        }
        
        if(count == n-1) break;
    }

    printf("total weight:%d\n",total);
}