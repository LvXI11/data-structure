#include<stdio.h>
#include<stdlib.h>
#define MAXV 100
#define INF 9999

typedef struct ALGraph{
    char vertex[MAXV][10];
    int arcnum,vexnum;
    int arcs[MAXV][MAXV];
}ALGraph;

void build_graph(ALGraph* G){
    for(int i = 0;i < MAXV; i++){
        for(int j = 0;j < MAXV; j++)
            G->arcs[i][j] = INF;
        G->arcs[i][i] = 0;
    }
    printf("请输入顶点个数和边的个数：\n");
    scanf("%d %d",&G->vexnum,&G->arcnum);
    for(int i = 0;i < G->vexnum; i++)
        snprintf(G->vertex[i],sizeof(G->vertex[i]),"v%d",i);
    printf("请输入边和权：\n");
    for(int j = 0;j < G->arcnum; j++){
        int a,b,w;
        scanf("%d %d %d",&a,&b,&w);
        G->arcs[a][b] = G->arcs[b][a] = w;
    }
}

void print_path(ALGraph* G,int v,int path[]){
    if(path[v] == -1){
        printf("%3s",G->vertex[v]);
        return;
    }
    print_path(G,path[v],path);
    printf("%3s",G->vertex[v]);
}

void dijkstra(ALGraph* G,int u0){
    int dist[MAXV];
    int path[MAXV];
    int visited[MAXV] = {0};

    for(int i = 0;i < G->vexnum; i++){
        dist[i] = G->arcs[u0][i];
        path[i] = u0 == i ? -1 : u0;
    }
    visited[u0] = 1;

    for(int j = 0;j < G->vexnum - 1; j++){
        int m = -1;
        int min = INF;

        for(int k = 0;k < G->vexnum; k++){
            if(!visited[k] && dist[k] < min){
                min = dist[k];
                m = k;
            }
        }

        if(m == -1) return;
        visited[m] = 1;

        for(int t = 0;t < G->vexnum; t++){
            if(!visited[t] && G->arcs[m][t] + dist[m] < dist[t]){
                dist[t] = G->arcs[m][t] + dist[m];
                path[t] = m;
            }
        }
    }

    for(int i = 0;i < G->vexnum; i++){
        print_path(G,i,path);
        printf(" %d",dist[i]);
    }
}

int main(void){
    ALGraph G;
    build_graph(&G);
    dijkstra(&G,0);
    return 0;
}