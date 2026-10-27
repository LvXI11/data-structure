#include<stdio.h>
#include<stdlib.h>
#define MAXV 100
#define INF 99999

typedef struct ALGraph{
    char veterx[MAXV][10];
    int arcnum, vexnum;
    int arcs[MAXV][MAXV];
}ALGraph;

void prim(ALGraph* G, int u0) {
    int lowcost[MAXV];
    int adjvex[MAXV];
    int visited[MAXV] = {0};
    int total = 0;

    for(int i = 0;i < G->vexnum; i++) {
        lowcost[i] = G->arcs[u0][i];
        adjvex[i] = u0;
    }
    visited[u0] = 1;

    for(int i = 0;i < G->vexnum; i++) {
        int min = INF;
        int k = -1;

        for(int j = 0;j < G->vexnum; j++) {
            if(!visited[j] && lowcost[j] < min) {
                min = lowcost[j];
                k = j;
            }
        }

        if(k == -1) return;
        total += lowcost[k];

        printf("%s %s %d\n", G->veterx[adjvex[k]], G->veterx[k], lowcost[k]);
        visited[k] = 1;
        for(int t = 0;t < G->vexnum; t++) {
            if(!visited[t] && G->arcs[k][t] < lowcost[t]) {
                lowcost[t] = G->arcs[k][t];
                adjvex[t] = k;
            }
        }
    }
    printf("total weight:%d\n", total);
}

void print_path(ALGraph* G,int* path, int v) {
    if(path[v] == -1) {
        printf("%s ", G->veterx[v]);
        return;
    }

    print_path(G, path, path[v]);
    printf("%s ", G->veterx[v]);
}

void dijkstra(ALGraph* G, int u0) {
    int dist[MAXV];
    int path[MAXV];
    int visited[MAXV] = {0};

    for(int i = 0;i < G->vexnum; i++) {
        dist[i] = G->arcs[u0][i];
        path[i] = (i == u0 ? -1 : u0);
    }
    visited[u0] = 1;

    for(int i = 0;i < G->vexnum - 1; i++) {
        int min = INF;
        int k = -1;

        for(int j = 0;j < G->vexnum; j++) {
            if(!visited[j] && dist[j] < min) {
                min = dist[j];
                k = j;
            }
        }

        if(k == -1) return;
        visited[k] = 1;

        for(int t = 0;t < G->vexnum; t++) {
            if(!visited[t] && G->arcs[k][t] + dist[k] < dist[t]) {
                dist[t] = G->arcs[k][t] + dist[k];
                path[t] = k;
            }
        }
    }

    for(int k = 0;k < G->vexnum; k++) {
        print_path(G, path, k);
        printf("%d\n", dist[k]);
    }
}

void build_graph(ALGraph* G) {
    G->vexnum = 6; G->arcnum = 10;
    for (int i = 0; i < 6; i++) {
        sprintf(G->veterx[i], "%d", i);
        for (int j = 0; j < 6; j++)
            G->arcs[i][j] = (i == j) ? 0 : INF;
    }
    int e[10][3] = {{0,1,6},{0,2,1},{0,3,5},{1,2,5},{1,4,3},
                    {2,3,5},{2,4,6},{2,5,4},{3,5,2},{4,5,6}};
    for (int i = 0; i < 10; i++) {
        int a = e[i][0], b = e[i][1], w = e[i][2];
        G->arcs[a][b] = w; G->arcs[b][a] = w;      // ★ 无向图，两个方向都要填
    }
}

int main(void) {
    ALGraph G;
    build_graph(&G);
    printf("=== Prim ===\n");
    prim(&G, 0);
    printf("=== Dijkstra ===\n");
    dijkstra(&G, 0);
    return 0;
}