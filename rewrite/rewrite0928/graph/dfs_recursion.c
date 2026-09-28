#include<stdio.h>
#include<stdlib.h>
#define MAXV 100

typedef struct ArcNode{
    int adjvex;
    struct ArcNode* nextarc;
}ArcNode;

typedef struct VNode{
    char data[10];
    ArcNode* firstarc;
}VNode;

typedef struct ALGraph{
    VNode vertex[MAXV];
    int arcnum,vexnum;
}ALGraph;

void create_edge(ALGraph* G,int a,int b){
    ArcNode* new_arc=(ArcNode*)malloc(sizeof(ArcNode));
    if(!new_arc) return;
    new_arc->adjvex=b;
    new_arc->nextarc=G->vertex[a].firstarc;
    G->vertex[a].firstarc=new_arc;
}

void build_graph(ALGraph* G){
    printf("请输入顶点数和边数：\n");
    scanf("%d %d",&G->vexnum,&G->arcnum);
    for(int i=0;i<G->vexnum;i++){
        snprintf(G->vertex[i].data,sizeof(G->vertex[i].data),"v%d",i);
        G->vertex[i].firstarc=NULL;
    }
    printf("请输入边：\n");
    for(int j=0;j<G->arcnum;j++){
        int a,b;
        scanf("%d %d",&a,&b);
        create_edge(G,a,b);
        create_edge(G,b,a);
    }
}

void dfs(ALGraph* G,int v,int visited[]){
    if(visited[v]) return;
    visited[v]=1;
    printf("%3s ",G->vertex[v].data);
    for(ArcNode* p=G->vertex[v].firstarc;p;p=p->nextarc)
    dfs(G,p->adjvex,visited);
}