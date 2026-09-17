#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

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

typedef struct Queue{
    int vertex[MAXV];
    int front,rear;
}Queue;

void init_queue(Queue* Q){
    Q->front=Q->rear=0;
}

bool is_empty(Queue* Q){
    return Q->front==Q->rear;
}

bool is_full(Queue* Q){
    return (Q->rear+1)%MAXV==Q->front;
}

void enqueue(Queue* Q,int v){
    if(is_full(Q))return;
    Q->vertex[Q->rear]=v;
    Q->rear=(Q->rear+1)%MAXV;
}

int dequeue(Queue* Q){
    if(is_empty(Q))return -1;
    int out=Q->vertex[Q->front];
    Q->front=(Q->front+1)%MAXV;
    return out;
}

void create_node(ALGraph* G,int a,int b){
    ArcNode* new_node=(ArcNode*)malloc(sizeof(ArcNode));
    if(!new_node) return;
    new_node->adjvex=b;
    new_node->nextarc=G->vertex[a].firstarc;
    G->vertex[a].firstarc=new_node;
}

void build_graph(ALGraph* G){
    printf("请输入顶点数：");
    scanf("%d",&G->vexnum);
    printf("请输入边数：");
    scanf("%d",&G->arcnum);
    for(int i=0;i<G->vexnum;i++){
        sprintf(G->vertex[i].data,"v%d",i);
        G->vertex[i].firstarc=NULL;
    }
    printf("请输入边：\n");
    for(int j=0;j<G->arcnum;j++){
        int a,b;
        scanf("%d %d",&a,&b);
        create_node(G,a,b);
    }
}

void topological_sort(ALGraph* G){
    Queue Q;
    init_queue(&Q);
    int indegree[MAXV]={0};
    for(int i=0;i<G->vexnum;i++){   //遍历每个顶点，看该顶点入到哪个顶点，被入 的那个顶点的indegree+1
        ArcNode* p=G->vertex[i].firstarc;
        while(p){
            indegree[p->adjvex]++;
            p=p->nextarc;
        }
    }
    for(int j=0;j<G->vexnum;j++){//入度为0，直接入队，准备被输出
        if(!indegree[j]){
            enqueue(&Q,j);
        }
    }
    int count=0;
    while(!is_empty(&Q)){
        int out=dequeue(&Q);
        printf("%s ",G->vertex[out].data);//输出
        count++;
        ArcNode* p=G->vertex[out].firstarc;
        while(p){                       //输出顶点，遍历该顶点的入度顶点并indegree-1                           
            indegree[p->adjvex]--;
            if(!indegree[p->adjvex]) //入度为0，又入队
            enqueue(&Q,p->adjvex);
            p=p->nextarc;
        }
    }
    printf("\n");
    if(count<G->vexnum)//图里有环，入度都不为0，都在等入度为0的那个出现，所有有环顶点不可能全部被输出
        printf("图中有环，只输出了%d个顶点（共有%d个顶点）\n",count,G->vexnum);
    else printf("拓扑排序完成（无环）\n");
}

int main(void){
    ALGraph G;
    build_graph(&G);              // 读入顶点数/边数/边，建表
    topological_sort(&G);
    return 0;
}