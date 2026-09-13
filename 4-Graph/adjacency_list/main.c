#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

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
    int vexnum,arcnum;
}ALGraph;

bool add_node(ALGraph*G,int a,int b){
    ArcNode* new_node=(ArcNode*)malloc(sizeof(ArcNode));
    if(!new_node)return false;
    new_node->adjvex=b;
    new_node->nextarc=G->vertex[a].firstarc;
    G->vertex[a].firstarc=new_node;
    return true;
}

void creat_graph(ALGraph* G){
     printf("请输入顶点数：");
     scanf("%d",&G->vexnum);
     printf("请输入边数：");
     scanf("%d",&G->arcnum);
     printf("请输入各顶点名：\n");
     for(int i=0;i<G->vexnum;i++){
        scanf("%s",G->vertex[i].data);
        G->vertex[i].firstarc=NULL;
     }
     printf("请输入边的两端点：\n");
     for(int j=0;j<G->arcnum;j++){
        int a,b;
        scanf("%d %d",&a,&b);
        if(!add_node(G,a,b)){
            printf("内存分配失败\n");
            exit(EXIT_FAILURE);
        }
        if(!add_node(G,b,a)){
            printf("内存分配失败\n");
            exit(EXIT_FAILURE);
        }
     }
}

void print_graph(ALGraph* G){
    for(int i=0;i<G->vexnum;i++){
        printf("%s:",G->vertex[i].data);
        ArcNode* p=G->vertex[i].firstarc;
        while(p){
            printf("%d ",G->vertex[i].firstarc->adjvex);
            p=p->nextarc;
        }
    }
}

void destroy_graph(ALGraph* G){
    for(int i=0;i<G->vexnum;i++){
        ArcNode* p=G->vertex[i].firstarc;
        while(p){
            ArcNode* del=p;
            p=p->nextarc;
            free(del);
        }
        G->vertex[i].firstarc->nextarc=NULL;
    }
}
int main(void){
    ALGraph G;
    creat_graph(&G);
    print_graph(&G);
    destroy_graph(&G);
    system("pause");
    return 0;
}