#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>

// 2. 分别以邻接矩阵和邻接表作为存储结构，实现以下图的基本操作：
// （1）增加一个新顶点v，InsertVex(G,v)；
// （2）删除顶点v 及其相关的边，DeleteVex(G,v)；
// （3）增加一条边(v,w)，InsertArc(G,v,w)；
// （4）删除一条边(v,w)，DeleteArc(G,v,w)。



/*     邻接矩阵     */

#define Arc 1
#define Edge 0
#define MAXSIZE 10
typedef char DataType;
typedef struct
{
    DataType vexs[MAXSIZE]; //图中顶点数组
    int edges[MAXSIZE][MAXSIZE]; //顶点相邻关系
    int numvexs; //图中顶点数目
    int numEdges; //图中边的数目

}Graph;

void Create_Graph(Graph* G, int ret)
{
    int i;
    int j;
    int k;
    int v1;
    int v2;

    printf("Please enter graph vexs and edges num: ");
    scanf("%d%d", &G->numvexs, &G->numEdges);
    fflush(stdin);
    for(i = 0;  i < G->numvexs; i++)
    {
        fflush(stdin);
        scanf("%c", &(G->vexs[i]));
        for(j = 0; j < G->numvexs; j++)
        {           
            G->edges[i][j] = 0;
        }
    }

    for(k = 0; k < G->numEdges; k++)
    {
        printf("v1, v2 = ");
        scanf("%d%d", &v1, &v2);
        G->edges[v1][v2] = 1;
        if(!ret)
        {
           G->edges[v2][v1] = 1; 
        }
    }
}

//添加顶点
void InsertVexs(Graph* G, char x)
{
    if(G->numvexs < MAXSIZE)
    {
        G->vexs[G->numvexs++] = x;
        int i = 0;
        for(; i < G->numvexs; i++)
        {
            G->edges[G->numvexs - 1][i] = 0;
            G->edges[i][G->numvexs - 1] = 0;
        }
    }
}

//添加边
void InsertEdges(Graph* G, char x1, char x2, int ret)
{
    //if(ret == 1 && G->numEdges <= G->numvexs * 2)
    //{
    int tempVexs1 = 0;
    int tempVexs2 = 0;
    for(tempVexs1 = 0; tempVexs1 < G->numvexs; tempVexs1++)
    {
        if(G->vexs[tempVexs1] == x1)
        {
            for(tempVexs2 = 0; tempVexs2 < G->numvexs; tempVexs2++)
            {
                if(G->vexs[tempVexs2] == x2)
                {
                    G->edges[tempVexs1][tempVexs2] = 1;
                    if(!ret)
                    {
                        G->edges[tempVexs2][tempVexs1] = 1;
                    }
                    G->numEdges++;
                }
            }
        }
    }
    //}
}

//输出相邻矩阵和顶点
void Print_Graph(const Graph const* G)
{
    printf("\n");
    int i = 0;
    printf(" ");
    for(; i < G->numvexs; i++)
    {
        printf("%c ", G->vexs[i]);
    }
    for(i = 0; i < G->numvexs; i++)
    {
        printf("\n%c ", G->vexs[i]);
        int j = 0;
        for(; j < G->numvexs; j++)
        {
            printf("%d ", G->edges[i][j]);
        }
    }
}


int main()
{
    Graph g;
    Create_Graph(&g, Arc);
    Print_Graph(&g);
    char temp = 'h';
    InsertVexs(&g, temp);
    Print_Graph(&g);
    InsertEdges(&g, g.vexs[3], g.vexs[1], Arc);
    Print_Graph(&g);
    return 0;
}