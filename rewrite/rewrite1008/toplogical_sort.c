#include<stdlib.h>
#include<stdio.h>
#define MAXV 100
#define INF 99999

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
    ArcNode* new_a = (ArcNode*)malloc(sizeof(ArcNode));
    if(!new_a) return;
    new_a->adjvex = b;
    new_a->nextarc = G->vertex[a].firstarc;
    G->vertex[a].firstarc = new_a;
}

void build_graph(ALGraph* G){

    printf("请输入顶点数和边数：\n");
    scanf("%d %d",&G->vexnum,&G->arcnum);
    for(int i = 0;i < G->vexnum; i++){
        snprintf(G->vertex[i].data,sizeof(G->vertex[i].data),"v%d",i);
        G->vertex[i].firstarc = NULL;
    }
    printf("请输入边和权:\n");
    for(int j = 0;j < G->arcnum; j++){
        int a,b;
        scanf("%d %d",&a,&b);
        create_edge(G,a,b);
    }
}

typedef struct Queue{
    VNode data[MAXV];
    int front,rear;
}Queue;

void init_queue(Queue* Q) {Q->front = Q->rear = 0;}
void enqueue(Queue* Q,VNode v) {Q->data[Q->rear++] = v;}
VNode dequeue(Queue* Q) {return Q->data[Q->front++];}
int queue_empty(Queue* Q) {return Q->front == Q->rear;}

void toplogical_sort(ALGraph* G){
    int count = 0;
    int indegree[MAXV] = {0};
    Queue Q;
    init_queue(&Q);

    for(int i = 0;i < G->vexnum; i++){
        ArcNode* p = G->vertex[i].firstarc;
        while(p){
            indegree[p->adjvex]++;
            p = p->nextarc;
        }
    }

    for(int j = 0;j < G->vexnum; j++){
            if(!indegree[j]){
                enqueue(&Q,G->vertex[j]);
            }
        }

    while(!queue_empty(&Q)){
            VNode v = dequeue(&Q);
            count++;
            printf("%3s",v.data);
            ArcNode* p = v.firstarc;
            while(p){
                indegree[p->adjvex]--;
                if(!indegree[p->adjvex]) enqueue(&Q,G->vertex[p->adjvex]);
                p = p->nextarc;
            }
        }

    if(count < G->vexnum) printf("图中有环，只输出了%d（应输出%d）\n",count,G->vexnum);
    else printf("图已输出完\n");
}