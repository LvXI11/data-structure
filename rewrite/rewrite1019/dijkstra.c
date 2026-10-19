#include<stdlib.h>
#define MAXV 100
#define INF 99999
#include<stdio.h>

typedef struct ALGraph {
    char vertex[MAXV][10];
    int vexnum, arcnum;
    int arcs[MAXV][MAXV];    
}ALGraph;

void print_path(ALGraph* G, int *path, int v) {
    if(path[v] == -1) {
        printf("%s ", G->vertex[v]);
        return;
    }
    print_path(G, path, path[v]);
    printf("%s", G->vertex[v]);
}

void dijkstra(ALGraph* G, int u0) {
    int dist[MAXV];
    int path[MAXV];
    int visited[MAXV] = {0};

    for(int i = 0;i < G->vexnum; i++) {
        dist[i] = G->arcs[u0][i];
        path[i] = i == u0 ? -1 : u0;
    }
    visited[u0] = 1;

    for(int i = 0;i < G->vexnum - 1; i++) {
        int min = INF;
        int k = -1;

        for(int j = 0;j < G->vexnum; j++) {
            if(visited[j] != 1 && dist[j] < min) {
                min = dist[j];
                k = j;
            }
        }
        if(k == -1) return;
        visited[k] = 1;

        for(int t = 0;t < G->vexnum; t++) {
            if(visited[t] != 1 && dist[k] + G->arcs[k][t] < dist[t]) {
                dist[t] = dist[k] + G->arcs[k][t];
                path[t] = k;
            }
        }
    }

    for(int k = 0;k < G->vexnum; k++) {
        print_path(G, path, k);
        printf(" %d\n", dist[k]);
    }
}