#include<stdio.h>
#define MAXV 100
#define INF 99999

typedef struct ALGraph{
    char vertex[MAXV][10];
    int vexnum,arcnum;
    int arcs[MAXV][MAXV];
}ALGraph;

void build_graph(ALGraph* G){
    for(int t=0;t<MAXV;t++){
        for(int u=0;u<MAXV;u++){
            G->arcs[t][u]=INF;
        }
        G->arcs[t][t]=0;
    }
    printf("请输入顶点数：");
    scanf("%d",&G->vexnum);
    printf("\n请输入边数：");
    scanf("%d",&G->arcnum);
    for(int i=0;i<G->vexnum;i++){
        sprintf(G->vertex[i],"v%d",i);
    }
    printf("请输入边和权：\n");
    for(int i=0;i<G->arcnum;i++){
        int a,b,weight;
        scanf("%d %d %d",&a,&b,&weight);
        G->arcs[a][b]=weight;
        G->arcs[b][a]=weight;
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
            if(G->arcs[i][j]==INF)
            printf("%4s","-");
            else printf("%4d",G->arcs[i][j]);
        }
        printf("\n");
    }
}

void prim(ALGraph* G,int u0){
    int lowcost[MAXV];//存顶点到树的最小候选权值
    int adjvex[MAXV];//存最小权对应的从树里出来的那个顶点编号
    int visited[MAXV]={0};//判断是否入树
    int total=0;
    //初始化
    for(int i=0;i<G->vexnum;i++){
        lowcost[i]=G->arcs[u0][i];//默认每个顶点到树的最小权值是到u0的值，下面更新会逐渐找到真的最小权
        adjvex[i]=u0;//上面已经默认到u0是最小权，这里就要存最小权对应的树中的那个顶点编号即u0
    }
    visited[u0]=1;
    //把剩下的n-1个顶点拉入树中
    for(int i=0;i<G->vexnum-1;i++){
        int min=INF;
        int k=-1;
        //选：找到最小权
        for(int j=0;j<G->vexnum;j++){
            if(!visited[j]&&lowcost[j]<min){
                min=lowcost[j];
                k=j;
            }
        }
        total+=lowcost[k];
        //未找到最小权说明未连通
        if(k==-1){
            printf("图未连通\n");
            return;
        }
        //k入树
        printf("边 %s - %s 权 %d\n",
            G->vertex[adjvex[k]],
            G->vertex[k],
            lowcost[k]);
        visited[k]=1;
        //更新：新顶点k入树，可能有更小的权可选，遍历arcs[k][i]那行
        for(int i=0;i<G->vexnum;i++){
            if(!visited[i]&&G->arcs[k][i]<lowcost[i]){
                lowcost[i]=G->arcs[k][i];
                adjvex[i]=k;
            }
        }
    }
    printf("prim的总权：%d\n",total);
}

int main(void){
    ALGraph G;
    build_graph(&G);
    print_graph(&G);
    printf("从v0开始：\n");
    prim(&G,0);
    return 0;
}