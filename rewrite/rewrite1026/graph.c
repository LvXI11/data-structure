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
    int arcnum, vexnum;
}ALGraph;

void create_edge(ALGraph* G, int a, int b) {
    ArcNode* new_node = (ArcNode*)malloc(sizeof(ArcNode));
    if(!new_node) return;
    new_node->adjvex = b;
    new_node->nextarc = G->vertex[a].firstarc;
    G->vertex[a].firstarc = new_node;
}

void build_graph(ALGraph* G) {
    G->vexnum = 6;
    G->arcnum = 6;

    // 顶点：名字就叫 "0" 到 "5"
    for (int i = 0; i < G->vexnum; i++) {
        G->vertex[i].firstarc = NULL;          // ★ 必须置空，否则是垃圾指针
        sprintf(G->vertex[i].data, "v%d", i);
    }

    // 边
    create_edge(G, 0, 1);
    create_edge(G, 0, 2);
    create_edge(G, 1, 3);
    create_edge(G, 2, 3);
    create_edge(G, 3, 4);
    create_edge(G, 4, 5);
}

void dfs(ALGraph* G, int* visited, int v) {
    if(visited[v]) return;
    visited[v] = 1;

    printf("%s ", G->vertex[v].data);
    for(ArcNode* p = G->vertex[v].firstarc;p; p = p->nextarc) {
        int w = p->adjvex;
        if(!visited[w]) {
            dfs(G, visited, w);
        }
    }
}

typedef struct Queue{
    int data[MAXV];
    int front, rear;
}Queue;

void init_queue(Queue* Q) { Q->front = Q->rear = 0; }
void enqueue(Queue* Q, int v) { Q->data[Q->rear++] = v; }
int dequeue(Queue* Q) { return Q->data[Q->front++]; }
int queue_empty(Queue* Q) { return Q->front == Q->rear; }

void bfs(ALGraph* G, int* visited, int v) {
    Queue Q;
    init_queue(&Q);
    enqueue(&Q, v);
    visited[v] = 1;
    while(!queue_empty(&Q)) {
        int index = dequeue(&Q);
        printf("%s ", G->vertex[index].data);
        for(ArcNode* p =G->vertex[index].firstarc;p; p = p->nextarc) {
            int w = p->adjvex;
            if(!visited[w]) {
                visited[w] = 1;
                enqueue(&Q,w);
            }
        }
    }
}

void toplogical_sort(ALGraph* G) {
    int indegree[MAXV] = {0};
    int count = 0;
    Queue Q;
    init_queue(&Q);

    for(int i = 0;i < G->vexnum; i++) {
        ArcNode* p = G->vertex[i].firstarc;
        while(p) {
            indegree[p->adjvex]++;
            p = p->nextarc;
        }
    }

    for(int i = 0;i < G->vexnum; i++) {
        if(!indegree[i]) {
            enqueue(&Q, i);
        }
    }

    while(!queue_empty(&Q)) {
        int v = dequeue(&Q);
        printf("%s ", G->vertex[v].data);
        count++;
        ArcNode* q = G->vertex[v].firstarc;
        while(q) {
            indegree[q->adjvex]--;
            if(!indegree[q->adjvex]) {
                enqueue(&Q, q->adjvex);
            }
            q = q->nextarc;
        }
    }

    if(count < G->vexnum) printf("图中有环，输出%d（应该输出%d）\n", count, G->vexnum);
    else printf("图已输出完，无环\n");

}

int main(void) {
    ALGraph G;
    build_graph(&G);

    int v1[6] = {0};                       // ★ 每次都清零，dfs/bfs 各用一份
    printf("DFS:  ");
    dfs(&G, v1, 0);
    printf("\n");

    int v2[6] = {0};
    printf("BFS:  ");
    bfs(&G, v2, 0);
    printf("\n");

    printf("拓扑: ");
    toplogical_sort(&G);
    printf("\n");

    return 0;
}