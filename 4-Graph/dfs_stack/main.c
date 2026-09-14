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

int add_node(ALGraph* G,int a,int b){
    ArcNode* new_node=(ArcNode*)malloc(sizeof(ArcNode));
    if(!new_node) return 0;
    new_node->adjacency=b;
    new_node->nextarc=G->vertex[a].firstarc;
    G->vertex[a].firstarc=new_node;
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
    int edges[6][2]={{0,1},{0,3},{1,2},{1,4},{2,3},{2,4}};
    for(int i=0;i<6;i++){
        int a=edges[i][0], b=edges[i][1];
        add_node(G,a,b);
        add_node(G,b,a);
    }
}

void print_graph(ALGraph* G){
    for(int i=0;i<G->vexnum;i++){
        printf("%s:",G->vertex[i].data);
        for(ArcNode* p=G->vertex[i].firstarc;p;p=p->nextarc)
            printf(" %d",p->adjacency);
        printf("\n");
    }
}

/* ---------- 栈（数组版） ---------- */
// DFS 深度最多 = 顶点数，所以开 MAXARC 绝对不会溢出。

typedef struct{
    int data[MAXARC];
    int top;
}Stack;

void init_stack(Stack* S){
    S->top=0;
}

int is_empty(Stack* S){
    return S->top==0;
}

void push(Stack* S,int v){
    S->data[S->top++]=v;
}

int pop(Stack* S){
    return S->data[--S->top];
}

/* ============ 以下是你写的部分 ============ */

// DFS 非递归版（用栈）
//
// 对照你刚写对的 BFS —— 两者几乎一模一样，只差"栈"还是"队列"：
//
//   BFS 里你怎么写的：              这个函数就怎么写：
//   ------------------------------  ------------------------------
//   Queue Q; init_queue(&Q);        Stack S; init_stack(&S);
//   enqueue(&Q,v); visited[v]=1;    push(&S,v);   visited[v]=1;
//   while(!is_empty(&Q)){           while(!is_empty(&S)){
//       p=dequeue(&Q);                  p=pop(&S);
//       print(p);                       print(p);
//       for 邻居 q:                     for 邻居 q:
//           if(!visited[q])                 if(!visited[q])
//               visited[q]=1,                   visited[q]=1,
//               enqueue(&Q,q);                  push(&S,q);
//   }                               }
//
// 也就是说：把 BFS 里的 enqueue/dequeue 换成 push/pop，别的都不用改。
void dfs_stack(ALGraph* G,int v,int visited[]){
    Stack S;
    init_stack(&S);
    push(&S,v);
    visited[v]=1;
    while(!is_empty(&S)){
        int p=pop(&S);
        printf("%s ",G->vertex[p].data);
        for(ArcNode* q=G->vertex[p].firstarc;q;q=q->nextarc){
            int w=q->adjacency;
            if(!visited[w]){
                visited[w]=1;
                push(&S,w);
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
    printf("\nDFS(栈) from v0: ");
    dfs_stack(&G,0,visited);
    printf("\n");

    system("pause");
    return 0;
}
