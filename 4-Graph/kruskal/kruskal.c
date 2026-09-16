#include<stdio.h>
#define MAXV 100
#define MAXE 1000

typedef struct{
    int u,v,weight;
}Edge;

Edge edges[MAXE];
int parent[MAXV];

void init_uf(int n){    //parent的下标是顶点自己，刚开始都是自己是自己的老大
    for(int i=0;i<n;i++)
    parent[i]=i;
}

int find(int x){
    if(parent[x]!=x)
    parent[x]=find(parent[x]);
    return parent[x];
}

void union_sets(int a, int b){
    int ra=find(a); int rb=find(b);
    if(ra!=rb) parent[ra]=rb;
}

void insert_sort(Edge arr[],int e){//插入排序
    for(int i=1;i<e;i++){
       Edge x=arr[i];
       int j=i-1;
       for(;j>=0&&x.weight<arr[j].weight;j--){
        arr[j+1]=arr[j];
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
        int weight=edges[i].weight;

        if(find(u)!=find(v)){
            printf("边 %d - %d 权 %d\n",u,v,weight);
            total+=weight;
            union_sets(u,v);
            count++;
            if(count==n-1) break;
        }
    }
    printf("最小生成树的总权：%d\n",total);
}

int main(void){
    int n, e;
    scanf("%d %d", &n, &e);          // 读顶点数、边数
    for(int i = 0; i < e; i++){
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight);
    }
    init_uf(n);                      // 并查集初始化
    kruskal(n, e);                   // 跑 Kruskal
    return 0;
}