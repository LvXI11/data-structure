#include<stdio.h>
#include<stdlib.h>

#define MAX_EDGE 100

typedef struct{
    char vertex[MAX_EDGE][10];
    int vernum,arcnum;
    int arcs[MAX_EDGE][MAX_EDGE];
}Graph;

void create_graph(Graph* G){//创建图：输入内容才能确定图
    for(int x=0;x<MAX_EDGE;x++){
        for(int y=0;y<MAX_EDGE;y++){
            G->arcs[x][y]=0;
        }
    }
    printf("请输入顶点数：");
    scanf("%d",&G->vernum);
    printf("\n请输入边数：");
    scanf("%d",&G->arcnum);
    printf("\n请依次输入顶点：\n");
    for(int i=0;i<G->vernum;i++){
        scanf("%s",G->vertex[i]);
    }
    printf("请输入边的两个端点：\n");
    for(int j=0;j<G->arcnum;j++){
        int a,b;
        scanf("%d %d",&a,&b);
        G->arcs[a][b]=1;
        G->arcs[b][a]=1;
    }
}

void print_graph(Graph* G){
    printf("\n");
    printf("%4s","");
    for(int t=0;t<G->vernum;t++)
    printf("%4s",G->vertex[t]);
    printf("\n");
    for(int i=0;i<G->vernum;i++){
        printf("%4s",G->vertex[i]);
        for(int j=0;j<G->vernum;j++){
            printf("%4d",G->arcs[i][j]);
        }
        printf("\n");
    }
}

int get_degree(Graph* G,int i){
   int degree=0;
   for(int t=0;t<G->vernum;t++){
    if(G->arcs[i][t]) degree++;
   }
   return degree;
}

int main(void){
    Graph G;
    create_graph(&G);
    print_graph(&G);
    printf("请输入要查找度的位置：");
    int i;
    scanf("%d",&i);
    printf("\n度为：%d\n",get_degree(&G,i));

    system("pause");
    return 0;
}
