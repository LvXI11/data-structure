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
    }
}

typedef struct Queue{
    VNode data[MAXV];
    int front,rear;
}Queue;

void init_queue(Queue* Q) {Q->front=Q->rear=0;}
void enqueue(Queue* Q,VNode v) {Q->data[Q->rear++]=v;}
int is_empty(Queue* Q) {return Q->front==Q->rear;}
VNode dequeue(Queue* Q) {return Q->data[Q->front++];}

void toplogical_sort(ALGraph* G){
    int n=G->vexnum;
    int indegree[MAXV]={0};
    int count=0;
    for(int i=0;i<n;i++){
        ArcNode* p=G->vertex[i].firstarc;
        while(p){
            int v=p->adjvex;
            indegree[v]++;
            p=p->nextarc;
        }
    }

    Queue Q;
    init_queue(&Q);
    for(int j=0;j<n;j++){
        if(!indegree[j]){
            enqueue(&Q,G->vertex[j]);
        }
    }

    while(!is_empty(&Q)){
        VNode out=dequeue(&Q);
        count++;
        printf("%3s ",out.data);
        ArcNode* p=out.firstarc;
        while(p){
            int x=p->adjvex;
            indegree[x]--;
            if(!indegree[x]) enqueue(&Q,G->vertex[x]);
            p=p->nextarc;
        }
    }
    if(count==n) printf("已输出完\n");
    else printf("图中有环未输出完，只输出了%d（应输出%d）\n",count,G->vexnum);
}