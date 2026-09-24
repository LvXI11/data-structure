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
        create_edge(G,b,a);
    }
}

typedef struct Stack{
    VNode data[20];
    int top;
}Stack;

void init_stack(Stack* S) {S->top=-1;}
int is_empty(Stack* S) {return S->top==-1;}
void push(Stack* S,VNode e) {S->data[++S->top]=e;}
VNode pop(Stack* S) {return S->data[S->top--];}

void dfs_stack(ALGraph* G,int v,int visited[]){
    Stack S;
    init_stack(&S);
    push(&S,G->vertex[v]); visited[v]=1;
    while(!is_empty(&S)){
        VNode p=pop(&S);
        printf("%3s ",p.data);
        for(ArcNode* q=p.firstarc;q;q=q->next){
            int x=q->adjvex;
            if(!visited[x]){
                visited[x]=1;
                push(&S,G->vertex[x]);
            }
        }
    }
}