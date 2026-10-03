#include<stdio.h>
#include<stdlib.h>
#define MAXV 100

typedef struct ArcNode{
    int adjvex;
    int weight;
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

void create_edge(ALGraph* G,int a,int b,int w){
    ArcNode* new_e=(ArcNode*)malloc(sizeof(ArcNode));
    if(!new_e) return;
    new_e->adjvex=b;
    new_e->weight=w;
    new_e->nextarc=G->vertex[a].firstarc;
    G->vertex[a].firstarc=new_e;
}

void build_graph(ALGraph* G){
    printf("请输入顶点数和边数：");
    scanf("%d",&G->vexnum);
    scanf("%d",&G->arcnum);
    for(int i=0;i<G->vexnum;i++){
        snprintf(G->vertex[i].data,sizeof(G->vertex[i].data),"v%d",i);
        G->vertex[i].firstarc=NULL;
    }
    printf("请输入边和权:\n");
    for(int i=0;i<G->arcnum;i++){
        int a,b,w;
        scanf("%d %d %d",&a,&b,&w);
        create_edge(G,a,b,w);
        create_edge(G,b,a,w);
    }
}

void print_grpah(ALGraph* G){
    for(int i=0;i<G->vexnum;i++){
        printf("%4s",G->vertex[i].data);
        ArcNode* p=G->vertex[i].firstarc;
        while(p){
            printf("%4d",p->adjvex);
            p=p->nextarc;
        }
        printf("\n%4s","权");
        p=G->vertex[i].firstarc;
        while(p){
            printf("%4d",p->weight);
            p=p->nextarc;
        }
        printf("\n");
    }
}

void free_graph(ALGraph* G){
    for(int i=0;i<G->vexnum;i++){
        ArcNode* p=G->vertex[i].firstarc;
        while(p){
            ArcNode* del=p;
            p=p->nextarc;
            free(del);
        }
        G->vertex[i].firstarc=NULL;
    }
}