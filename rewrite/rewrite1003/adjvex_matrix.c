#include<stdio.h>
#include<stdlib.h>
#define MAXV 100
#define INF 9999999

typedef struct ALGraph{
    char vertex[MAXV][10];
    int arcnum,vexnum;
    int arcs[MAXV][MAXV];
}ALGraph;

void build_graph(ALGraph* G){
    for(int i=0;i<MAXV;i++){
        for(int j=0;j<MAXV;j++)
        G->arcs[i][j]=INF;
        G->arcs[i][i]=0;
    }
    printf("请输入顶点数和边数：");
    scanf("%d",&G->vexnum);
    scanf("%d",&G->arcnum);
    for(int i=0;i<G->vexnum;i++)
    snprintf(G->vertex[i],sizeof(G->vertex[i]),"v%d",i);
    printf("请输入边和权:\n");
    for(int i=0;i<G->arcnum;i++){
        int a,b,w;
        scanf("%d %d %d",&a,&b,&w);
        G->arcs[a][b]=G->arcs[b][a]=w;
    }
}

void print_grpah(ALGraph* G){
    printf("%4s","");
    for(int i=0;i<G->vexnum;i++)
    printf("%4s",G->vertex[i]);
    printf("\n");
    for(int i=0;i<G->vexnum;i++){
        printf("%4s",G->vertex[i]);
        for(int j=0;j<G->vexnum;j++){
            if(G->arcs[i][j]==INF) printf("%4s","-");
            else printf("%4d",G->arcs[i][j]);
        }
        printf("\n");
    }
}