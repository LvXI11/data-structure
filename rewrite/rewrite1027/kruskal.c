#include<stdio.h>
#include<stdlib.h>
#define MAXV 100
#define MAXE 1000

typedef struct Edge{
    int u, v, w;
}Edge;

Edge edge[MAXE];
int parent[MAXV];

void init_parent(int n) {
    for(int i = 0;i < n; i++) {
        parent[i] = i;
    }
}

int find(int x) {
    if(parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_set(int a, int b) {
    int ra = find(a); int rb = find(b);
    if(ra != rb) parent[ra] = rb;
}

void insert_sort(int e) {
    for(int i = 1;i < e; i++) {
        Edge  x = edge[i];
        int j = i - 1;
        while(j >= 0 && edge[j].w > x.w) {
            edge[j + 1] = edge[j];
            j--;
        }
        edge[j + 1] = x;
    }
}

void kruskal(int n, int e) {
    insert_sort(e);
    int count = 0;
    int total = 0;

    for(int i = 0;i < e; i++) {
        int u = edge[i].u;
        int v = edge[i].v;
        int w = edge[i].w;

        if(find(u) != find(v)) {
            total += w;
            count++;
            printf("v%d v%d %d\n", u, v, w);
            union_set(u, v);
            if(count == n - 1)break;
        }
        
    }
    printf("total weight:%d\n", total);
}

int main(void) {
    int n = 6, e = 10;
    init_parent(n);

    // 按测试图填边
    Edge tmp[] = {
        {0,1,6},{0,2,1},{0,3,5},
        {1,2,5},{1,4,3},
        {2,3,5},{2,4,6},{2,5,4},
        {3,5,2},
        {4,5,6}
    };
    for (int i = 0; i < e; i++) edge[i] = tmp[i];

    kruskal(n, e);
    return 0;
}