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

/* ================= 以下全是样板，不用你动 ================= */

int add_node(ALGraph* G,int a,int b){          // 无向图：两个方向各调一次
    ArcNode* n=(ArcNode*)malloc(sizeof(ArcNode));
    if(!n) return 0;
    n->adjvex=b;
    n->nextarc=G->vertex[a].firstarc;
    G->vertex[a].firstarc=n;
    return 1;
}

// 固定的测试图：5 个顶点 v0..v4，6 条边 (0,1)(0,3)(1,2)(1,4)(2,3)(2,4)
void build_test_graph(ALGraph* G){
    G->vexnum=5;
    G->arcnum=6;
    for(int i=0;i<5;i++){
        sprintf(G->vertex[i].data,"v%d",i);
        G->vertex[i].firstarc=NULL;
    }
    int e[6][2]={{0,1},{0,3},{1,2},{1,4},{2,3},{2,4}};
    for(int i=0;i<6;i++){
        add_node(G,e[i][0],e[i][1]);
        add_node(G,e[i][1],e[i][0]);
    }
}

void print_graph(ALGraph* G){
    for(int i=0;i<G->vexnum;i++){
        printf("%s:",G->vertex[i].data);
        for(ArcNode* p=G->vertex[i].firstarc;p;p=p->nextarc)
            printf(" %d",p->adjvex);
        printf("\n");
    }
}

/* ---------- 栈（数组版，给 dfs_stack 用） ---------- */
typedef struct{
    int data[MAXV];
    int top;
}Stack;

void init_stack(Stack* S){ S->top=0; }
int  stack_empty(Stack* S){ return S->top==0; }
void push(Stack* S,int v){ S->data[S->top++]=v; }
int  pop(Stack* S){ return S->data[--S->top]; }

/* ---------- 队列（普通数组版，给 bfs 用） ---------- */
typedef struct{
    int data[MAXV];
    int front,rear;
}Queue;

void init_queue(Queue* Q){ Q->front=Q->rear=0; }
int  queue_empty(Queue* Q){ return Q->front==Q->rear; }
void enqueue(Queue* Q,int v){ Q->data[Q->rear++]=v; }
int  dequeue(Queue* Q){ return Q->data[Q->front++]; }

/* ================= 以下是你写的部分 ================= */

// DFS 递归版
void dfs(ALGraph* G,int v,int visited[]){
    if(visited[v]) return;
    visited[v]=1;
    printf("%s ",G->vertex[v].data);
    for(ArcNode* p=G->vertex[v].firstarc;p;p=p->nextarc)
    dfs(G,p->adjvex,visited);
}


void dfs_stack(ALGraph* G,int v,int visited[]){
    if(visited[v]) return;
    Stack S;
    init_stack(&S);
    push(&S,v);
    visited[v]=1;
    while(!stack_empty(&S)){
        int u=pop(&S);
        printf("%s ",G->vertex[u].data);
        for(ArcNode* p=G->vertex[u].firstarc;p;p=p->nextarc){
            if(!visited[p->adjvex]){
                visited[p->adjvex]=1;
                push(&S,p->adjvex);
            }
        }
    } 
}

void bfs(ALGraph* G,int v,int visited[]){
    if(visited[v])return;
    Queue Q;
    init_queue(&Q);
    enqueue(&Q,v);
    visited[v]=1;
    while(!queue_empty(&Q)){
        int u=dequeue(&Q);
        printf("%s ",G->vertex[u].data);
        for(ArcNode* p=G->vertex[u].firstarc;p;p=p->nextarc){
            if(!visited[p->adjvex]){
                visited[p->adjvex]=1;
                enqueue(&Q,p->adjvex);
            }
        }
    }
}

/* ================= main ================= */

int main(void){
    ALGraph G;
    build_test_graph(&G);

    printf("邻接表：\n");
    print_graph(&G);

    int visited[MAXV];

    for(int i=0;i<MAXV;i++) visited[i]=0;
    printf("\nDFS(递归) from v0: ");
    dfs(&G,0,visited);
    printf("\n");

    for(int i=0;i<MAXV;i++) visited[i]=0;
    printf("DFS(栈)   from v0: ");
    dfs_stack(&G,0,visited);
    printf("\n");

    for(int i=0;i<MAXV;i++) visited[i]=0;
    printf("BFS       from v0: ");
    bfs(&G,0,visited);
    printf("\n");

    system("pause");
    return 0;
}
