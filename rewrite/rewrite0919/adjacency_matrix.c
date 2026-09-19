#include<stdio.h>
#define MAXV 100
#define INF 99999
typedef struct ALGraph{
    char vertex[MAXV][10];
    int arcnum,vexnum;
    int arcs[MAXV][MAXV];
}ALGraph;

void build_graph(ALGraph* G){
    for(int i=0;i<MAXV;i++){
        for(int j=0;j<MAXV;j++){
            G->arcs[i][j]=INF;
        }
        G->arcs[i][i]=0;
    }
    printf("请输入顶点数：");
    scanf("%d",&G->vexnum);
    printf("请输入边数：");
    scanf("%d",&G->arcnum);
    for(int i=0;i<G->vexnum;i++){
        sprintf(G->vertex[i],"v%d",i);
    }
    printf("请输入边和权：\n");
    for(int t=0;t<G->arcnum;t++){
        int a,b,w;
        scanf("%d %d %d",&a,&b,&w);
        G->arcs[a][b]=G->arcs[b][a]=w;
    }
}