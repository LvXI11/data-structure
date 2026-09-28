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
        create_edge(G,b,a);
    }
}

typedef struct Stack{
    VNode data[MAXV];
    int top;
}Stack;

void init_stack(Stack* S) {S->top=-1;}
void push(Stack* S,VNode v) {S->data[++S->top]=v;}
int is_empty(Stack* S) {return S->top==-1;}
VNode pop(Stack* S) {return S->data[S->top--];}

void dfs(ALGraph* G,int v,int visited[]){
    Stack S;
    init_stack(&S);
    push(&S,G->vertex[v]);
    visited[v]=1;
    while(!is_empty(&S)){
        VNode p=pop(&S);
        printf("%3s ",p.data);
        for(ArcNode* q=p.firstarc;q;q=q->nextarc){
            int x=q->adjvex;
            if(!visited[x]){
                visited[x]=1;
                push(&S,G->vertex[x]);
            }
        }
    }
}