#include<stdio.h>
#define MAXV 100
#define INF 99999

typedef struct ALGraph{
    char vertex[MAXV][10];
    int arcnum,vexnum;
    int arcs[MAXV][MAXV];
}ALGraph;

void prim(ALGraph* G,int u0){
    int lowcost[MAXV];//存该顶点到树的最小权值
    int adjvex[MAXV];//存当前该顶点的最小权是从树中哪个顶点连过来的顶点编号
    int visited[MAXV]={0};//入树被标记
    int total=0;

    for(int i=0;i<G->vexnum;i++){
        lowcost[i]=G->arcs[u0][i];
        adjvex[i]=u0;
    }
    visited[u0]=1;
    //吧n-1个顶点拉入树中
    for(int i=0;i<G->vexnum-1;i++){
        int min=INF;
        int k=-1;
        for(int j=0;j<G->vexnum;j++){
            if(!visited[j]&&lowcost[j]<min){
                min=lowcost[j];
                k=j;
            }
        }
        if(k==-1){
            printf("图不连通");
            return;
        }
        total+=lowcost[k];
        //k入树
        printf("边 %s - %s 权 %d\n",
            G->vertex[adjvex[k]],
            G->vertex[k],
            lowcost[k]);
        visited[k]=1;
        //更新：k入树后可能有最小权出现
        for(int t=0;t<G->vexnum;t++){
            if(!visited[t]&&G->arcs[k][t]<lowcost[t]){
                lowcost[t]=G->arcs[k][t];
                adjvex[t]=k;
            }
        }
    }
    printf("总权:%d\n",total);
}