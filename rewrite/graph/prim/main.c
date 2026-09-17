#include<stdio.h>
#define MAXV 100
#define INF 9999

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
    printf("\n请输入边数：");
    scanf("%d",&G->arcnum);
    for(int i=0;i<G->vexnum;i++){
        sprintf(G->vertex[i],"v%d",i);
    }
    printf("\n请输入边和权:\n");
    for(int j=0;j<G->arcnum;j++){
        int a,b,weight;
        scanf("%d %d %d",&a,&b,&weight);
        G->arcs[a][b]=weight;
        G->arcs[b][a]=weight;
    }
}

void print_graph(ALGraph* G){
    printf("\n邻接矩阵：\n");
    printf("%4s","");
    for(int i=0;i<G->vexnum;i++)
    printf("%4s",G->vertex[i]);
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
    int lowcost[MAXV];  //这两个数组的下标都代表顶点，所有lowcost是用来存该顶点的最小权值
    int adjvex[MAXV];   //adjvex存的是那个最小权值是从树里的哪个顶点连到本顶点的顶点名
    int visited[MAXV]={0};
    int weight_sum=0;
    //初始化
    for(int i=0;i<G->vexnum;i++){
        lowcost[i]=G->arcs[u0][i];//默认顶点i到u0为最小权值，下面的“选”会找到真正的最小值
        adjvex[i]=u0;
    }
    visited[u0]=1;
    //把剩余的n-1个顶点拉进树里面
    for(int i=0;i<G->vexnum-1;i++){
        int min=INF;
        int k=-1;
        //找最小权值的边
        for(int j=0;j<G->vexnum;j++){
            if(!visited[j]&&lowcost[j]<min){
                min=lowcost[j];
                k=j;
            }
        }
        weight_sum+=lowcost[k];
        //k入树
        printf("边 %s - %s 权 %d\n",
            G->vertex[adjvex[k]],
            G->vertex[k],
            lowcost[k]);
            visited[k]=1;
        //更新：看看k入树后有没有其他更小权可替换
        for(int t=0;t<G->vexnum;t++){
            if(!visited[t]&&G->arcs[k][t]<lowcost[t]){
                lowcost[t]=G->arcs[k][t];
                adjvex[t]=k;
            }
        }
    }
    printf("最小树的总权：%d\n",weight_sum);
}

int main(void){
    ALGraph G;
    build_graph(&G);
    print_graph(&G);
    printf("最小树从v0开始：\n");
    prim(&G,0);
    return 0;
}