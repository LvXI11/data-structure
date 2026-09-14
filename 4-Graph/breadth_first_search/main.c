#include<stdio.h>
#include<stdlib.h>

#define MAXARC 100

typedef struct ArcNode{
    int adjacency;
    struct ArcNode* nextarc;
}ArcNode;

typedef struct VNode{
    char data[10];
    ArcNode* firstarc;
}VNode;

typedef struct ALGraph{
    VNode vertex[MAXARC];
    int arcnum,vexnum;
}ALGraph;

/* ============ 以下是样板，我写好了，你不用动 ============ */

// 头插：把 b 挂到 a 的邻居链表最前面
int add_node(ALGraph* G,int a,int b){
    ArcNode* new_node=(ArcNode*)malloc(sizeof(ArcNode));
    if(!new_node) return 0;
    new_node->adjacency=b;
    new_node->nextarc=G->vertex[a].firstarc;
    G->vertex[a].firstarc=new_node;
    return 1;
}

// 固定的测试图：
//   5 个顶点 v0..v4，6 条边 (0,1)(0,3)(1,2)(1,4)(2,3)(2,4)
void build_test_graph(ALGraph* G){
    G->vexnum=5;
    G->arcnum=6;
    for(int i=0;i<5;i++){
        sprintf(G->vertex[i].data,"v%d",i);
        G->vertex[i].firstarc=NULL;
    }
    int edges[6][2]={{0,1},{0,3},{1,2},{1,4},{2,3},{2,4}};
    for(int i=0;i<6;i++){
        int a=edges[i][0], b=edges[i][1];
        add_node(G,a,b);
        add_node(G,b,a);
    }
}

// 打印邻接表（核对用）
void print_graph(ALGraph* G){
    for(int i=0;i<G->vexnum;i++){
        printf("%s:",G->vertex[i].data);
        for(ArcNode* p=G->vertex[i].firstarc;p;p=p->nextarc)
            printf(" %d",p->adjacency);
        printf("\n");
    }
}

/* ---------- 队列（数组版，够用） ---------- */
// BFS 里队列最多同时装着全部顶点，所以开 MAXARC 就绝对不会溢出。
// 用 head / tail 两个下标，不用 malloc，比链式队列省事。

typedef struct{
    int data[MAXARC];
    int head;      // 出队位置
    int tail;      // 入队位置
}Queue;

void init_queue(Queue* Q){
    Q->head=0;
    Q->tail=0;
}

int is_empty(Queue* Q){
    return Q->head==Q->tail;
}

void enqueue(Queue* Q,int v){
    Q->data[Q->tail++]=v;
}

int dequeue(Queue* Q){
    return Q->data[Q->head++];
}

/* ============ 以下是你写的部分 ============ */

// BFS：从顶点 v 出发广度优先遍历
// 对照你写对的层序遍历骨架：
//     into_elem(Q,T);
//     while(!is_empty(Q)){
//         p=out_elem(Q);  print(p);
//         if(p->lchild) into_elem(Q,p->node->lchild);
//         if(p->node->rchild) into_elem(Q,p->node->rchild);
//     }
// 图版只需要把"左/右孩子"换成"顺着邻居链表把每个邻居都看一遍"。
void bfs(ALGraph* G,int v,int visited[]){
    if(visited[v])return;
    Queue Q;
    init_queue(&Q);
    enqueue(&Q,v);
    visited[v]=1;
    while(!is_empty(&Q)){
        int p=dequeue(&Q);
        printf("%s ",G->vertex[p].data);
        for(ArcNode* q=G->vertex[p].firstarc;q;q=q->nextarc){
            int w=q->adjacency;
            if(!visited[w]){
                visited[w]=1;
                enqueue(&Q,w);
            }
        }
    }
}

/* ============ main ============ */

int main(void){
    ALGraph G;
    build_test_graph(&G);

    printf("邻接表：\n");
    print_graph(&G);

    int visited[MAXARC]={0};
    printf("\nBFS from v0: ");
    bfs(&G,0,visited);
    printf("\n");

    system("pause");
    return 0;
}
