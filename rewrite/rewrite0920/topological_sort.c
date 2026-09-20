#include<stdio.h>
#define MAXV 100
#include<stdlib.h>

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
    int data[MAXV];
    int front,rear;
}Queue;

void init_queue(Queue* Q) {Q->front=Q->rear=0;}
void enqueue(Queue* Q,int v){Q->data[Q->rear++]=v;}
int queue_empty(Queue* Q) {return Q->front==Q->rear;}
int dequeue(Queue* Q) {if(queue_empty(Q)) return -1;return Q->data[Q->front++];}

void create_edge(ALGraph* G,int a,int b){
    ArcNode* new_edge=(ArcNode*)malloc(sizeof(ArcNode));
    if(!new_edge)return;
    new_edge->adjvex=b;
    new_edge->nextarc=G->vertex[a].firstarc;
    G->vertex[a].firstarc=new_edge;
}

void build_graph(ALGraph* G){
    printf("顶点数： ");
    scanf("%d",&G->vexnum);
    printf("边数：");
    scanf("%d",&G->arcnum);
    for(int i=0;i<G->vexnum;i++){
        sprintf(G->vertex[i].data,"v%d",i);
        G->vertex[i].firstarc=NULL;
    }
    printf("请输入边和权：\n");
    for(int j=0;j<G->arcnum;j++){
        int a,b,w;
        scanf("%d %d %d",&a,&b,&w);
        create_edge(G,a,b);
    }
}

void topological_sort(ALGraph* G){
    Queue Q;
    init_queue(&Q);
    int indegree[MAXV]={0};
    for(int i=0;i<G->vexnum;i++){
        ArcNode* p=G->vertex[i].firstarc;
        while(p){
            indegree[p->adjvex]++;
            p=p->nextarc;
        }
    }

    for(int j=0;j<G->vexnum;j++){
        if(!indegree[j]){
            enqueue(&Q,j);
        }
    }
    int count=0;
    while(!queue_empty(&Q)){
        int out=dequeue(&Q);
        count++;
        printf("%s ",G->vertex[out].data);
        ArcNode* q=G->vertex[out].firstarc;
        while(q){
            indegree[q->adjvex]--;
            if(!indegree[q->adjvex])
            enqueue(&Q,q->adjvex);
            q=q->nextarc;
        }
    }
    if(count<G->vexnum) printf("图有环只输出了%d个（应输出%d个）\n",count,G->vexnum);
    else printf("已全部按序输出（无环）\n");
}