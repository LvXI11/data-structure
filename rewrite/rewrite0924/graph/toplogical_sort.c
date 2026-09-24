#include<stdio.h>
#include<stdlib.h>
#define MAXV 100

typedef struct ArcNode{
    int adjvex;
    struct ArcNode* next;
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
    ArcNode* new_node=(ArcNode*)malloc(sizeof(ArcNode));
    if(!new_node)return;
    new_node->adjvex=b;
    new_node->next=G->vertex[a].firstarc;
    G->vertex[a].firstarc=new_node;
}

void build_graph(ALGraph* G){
    printf("输入顶点数:");
    scanf("%d",&G->vexnum);
    printf("输入边数:");
    scanf("%d",&G->arcnum);
    for(int i=0;i<G->vexnum;i++){
        sprintf(G->vertex[i].data,"v%d",i);
        G->vertex[i].firstarc=NULL;
    }
    printf("请输入边:\n");
    for(int j=0;j<G->arcnum;j++){
        int a,b;
        scanf("%d %d",&a,&b);
        create_edge(G,a,b);
    }
}

typedef struct Queue{
    VNode data[100];
    int front,rear;
}Queue;

void init_queue(Queue* Q) {Q->front=Q->rear=0;}
int is_empty(Queue* Q) {return Q->front==Q->rear;}
void enqueue(Queue* Q,VNode e) {Q->data[Q->rear++]=e;}
VNode dequeue(Queue* Q) {return Q->data[Q->front++];}

void toplogical_sort(ALGraph* G){
    int indegree[MAXV]={0};
    for(int i=0;i<G->vexnum;i++){
        ArcNode* p=G->vertex[i].firstarc;
        while(p){
            int x=p->adjvex;
            indegree[x]++;
            p=p->next;
        }
    }

    Queue Q;
    init_queue(&Q);
    for(int j=0;j<G->vexnum;j++){
        if(!indegree[j]){
            enqueue(&Q,G->vertex[j]);
        }
    }

    int count=0;
    while(!is_empty(&Q)){
        VNode p=dequeue(&Q);
        printf("%3s ",p.data);
        count++;
        ArcNode* q=p.firstarc;
        while(q){
            int x=q->adjvex;
            indegree[x]--;
            if(!indegree[x]) enqueue(&Q,G->vertex[x]);
            q=q->next;
        }
    }
    if(count<G->vexnum) printf("图中有环，只输出了%d（应输出%d）\n",count,G->vexnum);
    else printf("图连完，无环\n");
}