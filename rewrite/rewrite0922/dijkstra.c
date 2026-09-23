#include<stdio.h>
#define INF 99999
#define MAXV 100

typedef struct ALGraph{
    char vertex[MAXV][10];
    int arcs[MAXV][MAXV];
    int arcnum,vexnum;
}ALGraph;

int arc[6][6] = {
/*        v0    v1    v2    v3    v4    v5 */
/*v0*/ {   0,    6,    1,  INF,    5,  INF },
/*v1*/ {   6,    0,    5,  INF,  INF,    3 },
/*v2*/ {   1,    5,    0,    5,  INF,    4 },
/*v3*/ { INF,  INF,    5,    0,  INF,    2 },
/*v4*/ {   5,  INF,  INF,  INF,    0,    6 },
/*v5*/ { INF,    3,    4,    2,    6,    0 },
};

void init(ALGraph* G){
    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            G->arcs[i][j]=arc[i][j];
        }
    }
    G->vexnum=6;
    G->arcnum=9;
}

void print_path(ALGraph* G,int path[],int v){
    if(path[v]==-1){
        printf("%s",G->vertex[v]);
        return;
    }
    print_path(G,path,path[v]);
    printf("->%s",G->vertex[v]);
}

void dijkstra(ALGraph* G,int u0){
    int dist[MAXV];
    int path[MAXV];
    int visited[MAXV]={0};

    for(int i=0;i<G->vexnum;i++){
        dist[i]=G->arcs[u0][i];
        path[i]= (i==u0) ? -1:u0;
    }
    visited[u0]=1;

    for(int i=0;i<G->vexnum-1;i++){
        int k=-1;
        int min=INF;
        for(int j=0;j<G->vexnum;j++){
            if(!visited[j]&&dist[j]<min){
                min=dist[j];
                k=j;
            }
        }
        if(k==-1)return;
        visited[k]=1;

        for(int t=0;t<G->vexnum;t++){
            if(!visited[t]&&dist[k]+G->arcs[k][t]<dist[t]){
                dist[t]=dist[k]+G->arcs[k][t];
                path[t]=k;
            }
        }
    }
    for(int i=0;i<G->vexnum;i++){
        print_path(G,path,0);
        printf(" %d",dist[i]);
    }
}

int main(void){
    ALGraph G;
    init(&G);
    dijkstra(&G,0);
    return 0;
}