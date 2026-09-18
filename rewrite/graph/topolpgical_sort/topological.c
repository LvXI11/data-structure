#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>

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
    VNode vertex [MAXV];
    int arcnum,vexnum;
}ALGraph;

typedef struct Queue{
    int data[MAXV];
    int front,rear;
}Queue;

void init_queue(Queue* Q) {Q->front=Q->rear=0;}
bool is_empty(Queue* Q) {return Q->front==Q->rear;}
void enqueue(Queue* Q,int v) {Q->data[Q->rear++]=v;}
int dequeue(Queue* Q) {return Q->data[Q->front++];}

void create_edge(ALGraph* G,int a,int b){
    ArcNode* new_node=(ArcNode*)malloc(sizeof(ArcNode));
    if(!new_node)return;
    new_node->adjvex=b;
    new_node->nextarc=G->vertex[a].firstarc;
    G->vertex[a].firstarc=new_node;
}

void build_graph(ALGraph* G){
    printf("请输入顶点数:");
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
    while(!is_empty(&Q)){
        int out=dequeue(&Q);
        count++;
        printf("%d ",out);
        ArcNode* q=G->vertex[out].firstarc;
        while(q){
            int v=q->adjvex;
            indegree[v]--;
            if(!indegree[v])
            enqueue(&Q,v);
            q=q->nextarc;
        }
    }
    if(count<G->vexnum) printf("图中有环，只输出了%d个顶点（应输出%d个）\n",count,G->vexnum);
    else printf("图已输出完（无环）\n");
}

int main(void){
    ALGraph G;
    build_graph(&G);
    topological_sort(&G);
}