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
                    return;
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
    printf("  ");
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

/*    邻接表    */
#define NMAX 100


typedef struct node1
{
    int adjvex;
    struct node1* next;
}EdgeNode;

typedef struct vnode
{
    DataType vertex;
    EdgeNode* firstedge;
}VertexNode;

typedef struct
{
    VertexNode Adjlist[MAXSIZE];
    int numVexs;
    int numEdges;
}LKGraph;

void CreateGraph1(LKGraph* G, int ret)
{
    printf("Please enter graph vertex nums: ");
    scanf("%d", &G->numVexs);
    printf("Please enter graph edgenode nums: ");
    scanf("%d", &G->numEdges);
    int i = 0;

    printf("Please enter vertex nodes:\n");
    for(; i < G->numVexs; ++i)
    {
        fflush(stdin);
        scanf("%c", &G->Adjlist[i]);
        G->Adjlist[i].firstedge = NULL;
    }

    printf("Please enter edge nodes:\n");

    int j = 0;
    int v1;
    int v2;
    for(; j < G->numEdges; ++j)
    {
        printf("v1, v2 = ");
        scanf("%d%d", &v1, &v2);

        EdgeNode* p = (EdgeNode*)malloc(sizeof(EdgeNode));

        p->adjvex = v2;
        p->next = G->Adjlist[v1].firstedge;
        G->Adjlist[v1].firstedge = p;

        if(!ret)
        {
            p = (EdgeNode*)malloc(sizeof(EdgeNode));
            
            p->adjvex = v1;
            p->next = G->Adjlist[v2].firstedge;
            G->Adjlist[v2].firstedge = p;
        }
    }

}

//插入顶点
void InsertVertes1(LKGraph* G, DataType data,  int ret)
{
    if(G->numVexs < MAXSIZE)
    {
        VertexNode s;
        s.vertex = data;
        s.firstedge = NULL;

        G->Adjlist[G->numVexs++] = s; 
    }
}

//插入边
void InsertEdges1(LKGraph* G, char x1, char x2, int ret)
{
    int i = 0;
    int j = 0;

    for(; i < G->numVexs; i++)
    {
        if(G->Adjlist[i].vertex == x1)
        {
            for(; j < G->numVexs; j++)
            {
                if(G->Adjlist[j].vertex == x2)
                {
                    EdgeNode* s = (EdgeNode*)malloc(sizeof(EdgeNode));

                    s->adjvex = j;
                    s->next = G->Adjlist[i].firstedge;
                    G->Adjlist[i].firstedge = s;

                    if(!ret)
                    {
                        s = (EdgeNode*)malloc(sizeof(EdgeNode));

                        s->adjvex = i;
                        s->next = G->Adjlist[j].firstedge;
                        G->Adjlist[j].firstedge = s;
                    }
                    return;
                }
            }
            
        }
    }
}

void Print_LKGraph(LKGraph* G)
{
    int i = 0;
    for(; i < G->numVexs; i++)
    {
        printf("%d  %c: ", i, G->Adjlist[i].vertex);
        while(G->Adjlist[i].firstedge != NULL)
        {
            printf("%c ", G->Adjlist[(G->Adjlist[i].firstedge)->adjvex].vertex);
            G->Adjlist[i].firstedge = G->Adjlist[i].firstedge->next;
        }
        printf("\n");
    }
}

/*    邻接矩阵    */
void test01()
{
    Graph g;
    Create_Graph(&g, Arc);
    Print_Graph(&g);
    char temp = 'i';
    InsertVexs(&g, temp);
    Print_Graph(&g);
    InsertEdges(&g, g.vexs[3], g.vexs[1], Arc);
    Print_Graph(&g);
}
/*    邻接表    */
void test02()
{
    LKGraph g;
    CreateGraph1(&g, Edge);
    Print_LKGraph(&g);
}

int main()
{
    //test01(); //邻接矩阵
    test02(); //邻接表
    return 0;
}