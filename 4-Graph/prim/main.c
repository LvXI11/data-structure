#include<stdio.h>
#include<stdlib.h>
#define MAXV 100
#define INF 9999
typedef struct ALGraph{
    char vertex[MAXV][10];
    int vexnum,arcnum;
    int arcs[MAXV][MAXV];
}ALGraph;

void build_ALGraph(ALGraph* G){
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
    for(int i=0;i<G->vexnum;i++) sprintf(G->vertex[i],"v%d",i);
    printf("请输入各边和权重：\n");
    for(int j=0;j<G->arcnum;j++){
        int a,b,weight;
        scanf("%d%d %d",&a,&b,&weight);
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
    for(int j=0;j<G->vexnum;j++){
        printf("%4s",G->vertex[j]);
        for(int k=0;k<G->vexnum;k++){
            if(G->arcs[j][k]==INF) printf("%4s","-");
            else printf("%4d",G->arcs[j][k]);
        }
        printf("\n");
    }
}

void prim(ALGraph* G,int u0){
    int lowcost[MAXV];      // 【数组1】每个顶点"到已进树区域"的最短候选边长
    int adjvex[MAXV];       // 【数组2】那条候选边"是从树里哪个顶点拉过来的
    int vistied[MAXV]={0};
    int weight_sum=0;
    //初始化
    for(int i=0;i<G->vexnum;i++){
        lowcost[i]=G->arcs[u0][i];
        adjvex[i]=u0;
    }
    lowcost[u0]=0;
    vistied[u0]=1;
    //把未进树的（n-1）个顶点收入树中
    for(int t=0;t<G->vexnum-1;t++){
        int min=INF;
        int k=-1;
        //找最小权值
        for(int j=0;j<G->vexnum;j++){
            if(!vistied[j]&&lowcost[j]<min){
                min=lowcost[j];
                k=j;
            }
        }
        //没找到
        if(k==-1){
            printf("图不连通\n");
            return;
        }
        //k进树
        printf("边 %s - %s 权 %d\n",
            G->vertex[adjvex[k]],
            G->vertex[k],
            lowcost[k]);
        weight_sum+=lowcost[k];
        vistied[k]=1;
        //更新：k 进树了，别人可能有了更便宜的接法
        for(int j=0;j<G->vexnum;j++){
            if(!vistied[j]&&G->arcs[k][j]<lowcost[j]){
                lowcost[j]=G->arcs[k][j];
                adjvex[j]=k;
            }
        }
    }
    printf("最小生成树总权值 = %d\n",weight_sum);
}

int main(void){
    ALGraph G;
    build_ALGraph(&G);
    printf("\n邻接矩阵：\n");
    print_graph(&G);
    printf("\n最小生成树（从 v0 开始）：\n");
    prim(&G,0);
    printf("\n");
    system("pause");
    return 0;
}