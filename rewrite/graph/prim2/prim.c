#include<stdio.h>
#define MAXV 100
#define INF 9999
typedef struct ALGraph{
    char vertex[MAXV][10];
    int vexnum,arcnum;
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
    scanf("%d",&G->vexnum);\
    for(int i=0;i<G->vexnum;i++){
        sprintf(G->vertex[i],"v%d",i);
    }
    printf("请输入边数：");
    scanf("%d",&G->arcnum);
    printf("请输入各边和权：\n");
    for(int j=0;j<G->arcnum;j++){
        int a,b,w;
        scanf("%d %d %d",&a,&b,&w);
        G->arcs[a][b]=G->arcs[b][a]=w;
    }
}

void print_graph(ALGraph* G){
    printf("%4s","");
    for(int i=0;i<G->vexnum;i++){
        printf("%4s",G->vertex[i]);
    }
    printf("\n");
    for(int i=0;i<G->vexnum;i++){
        printf("%4s",G->vertex[i]);
        for(int j=0;j<G->vexnum;j++){
            printf("%4d",G->arcs[i][j]);
        }
        printf("\n");
    }
}

void prim(ALGraph* G,int u0){
    int lowcost[MAXV];
    int adjvex[MAXV];
    int visited[MAXV]={0};
    int total=0;

    for(int i=0;i<G->vexnum;i++){
        lowcost[i]=G->arcs[u0][i];
        adjvex[i]=u0;
    }
    visited[u0]=1;

    for(int i=0;i<G->vexnum-1;i++){
        int min=INF;
        int k=-1;
        for(int j=0;j<G->vexnum;j++){
            if(!visited[j]&&lowcost[j]<min){
                min=lowcost[j];
                k=j;
            }
        }
        if(k==-1)return;
        total+=lowcost[k];

        printf("边 %s - %s 权 %d\n",
            G->vertex[adjvex[k]],
            G->vertex[k],
            lowcost[k]);
        visited[k]=1;

        for(int t=0;t<G->vexnum;t++){
            if(!visited[t]&&G->arcs[k][t]<lowcost[t]){
                lowcost[t]=G->arcs[k][t];
                adjvex[t]=k;
            }
        }
    }
    printf("总权：%d",total);
}