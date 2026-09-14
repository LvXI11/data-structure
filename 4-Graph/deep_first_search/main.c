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

// 固定的测试图（省得每次手敲输入）：
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
        add_node(G,a,b);          // 无向图：两个方向都要挂
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

/* ============ 以下是你写的部分 ============ */

// DFS 递归版：从顶点 v 出发深度优先遍历
void dfs(ALGraph* G,int v,int visited[]){
    if(visited[v]) return;
    visited[v]=1;
    for(ArcNode* p=G->vertex[v].firstarc;p;p=p->nextarc)
    dfs(G,p->adjacency,visited);
    printf("%s ",G->vertex[v].data);
}

/* ============ main ============ */

int main(void){
    ALGraph G;
    build_test_graph(&G);

    printf("邻接表：\n");
    print_graph(&G);

    int visited[MAXARC]={0};
    printf("\nDFS from v4: ");
    dfs(&G,0,visited);
    printf("\n");

    system("pause");        // ← 防止窗口一闪就关
    return 0;
}
