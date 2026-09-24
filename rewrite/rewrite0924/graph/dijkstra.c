#include<stdio.h>
#define MAXV 100
#define INF 99999
typedef struct ALGraph{
    char vertex[MAXV][10];
    int arcs[MAXV][MAXV];
    int arcnum,vexnum;
}ALGraph;

void build_graph(ALGraph* G){
    for(int i=0;i<MAXV;i++){
        for(int j=0;j<MAXV;j++){
            G->arcs[i][j]=INF;
        }
        G->arcs[i][i]=0;
    }
    printf("输入顶点数:");
    scanf("%d",&G->vexnum);
    printf("输入边数:");
    scanf("%d",&G->arcnum);
    for(int i=0;i<G->vexnum;i++){
        sprintf(G->vertex[i],"v%d",i);
    }
    printf("请输入边和权:\n");
    for(int j=0;j<G->arcnum;j++){
        int a,b,w;
        scanf("%d %d %d",&a,&b,&w);
        G->arcs[a][b]=G->arcs[b][a]=w;
    }
}

void print_path(ALGraph* G,int path[],int v){
    if(path[v]==-1){
        printf("%3s",G->vertex[v]);
        return;
    }
    print_path(G,path,path[v]);
    printf("->%3s",G->vertex[v]);
}

void dijkstra(ALGraph* G,int u0){
    int dist[MAXV];
    int path[MAXV];
    int visited[MAXV]={0};

    for(int i=0;i<G->vexnum;i++){
        dist[i]=G->arcs[u0][i];
        path[i]= (i==u0) ? -1 : u0;
    }
    visited[u0]=1;

    for(int j=0;j<G->vexnum-1;j++){
        int min=INF;
        int k=-1;
        for(int m=0;m<G->vexnum;m++){
            if(!visited[m]&&dist[m]<min){
                min=dist[m];
                k=m;
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
        print_path(G,path,i);
        printf(" %d\n",dist[i]);
    }
}