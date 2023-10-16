#include <stdio.h>
#include <stdlib.h>

//#include "BiTree.h"
#include "SeqQueue.h"

void test01()
{
    BiTree root = (BiTree)malloc(sizeof(BiTreeNode));
    CreateBiTree(&root);
    int num1 = LeafNode_Num(root);
    printf("%d\n", num1);
}

void test02()
{
    BiTree root = (BiTree)malloc(sizeof(BiTreeNode));
    CreateBiTree(&root);
    int num2 = HeightBiTree_Num(root);
    printf("%d\n", num2);
}

int isCompleteBiTree(BiTree root)
{
    int isCom = 1;
    int temp = 0;
    SeqQueue sq;
    BiTree p = root;
    iniQueue(&sq);
    if(p != NULL)
    {
        EnQueue(&sq, &p);
        while(!QueueEmpty(&sq))
        {
            DeQueue(&sq, &p);
            if(p->lchild != NULL)
            {
                EnQueue(&sq, &(p->lchild));
            }
            else if(temp != 1)
            {
                temp = 1;
            }
            else
            {
                return 0;
            }

            if(p->rchild != NULL)
            {
                EnQueue(&sq, &(p->rchild));
            }
            else if(temp != 1)
            {
                temp = 1;
            }
            else
            {
                return 0;
            }
        }
    }

    return 1;
}

void test03()
{
    BiTree root = (BiTree)malloc(sizeof(BiTreeNode));
    CreateBiTree(&root);
    int ret = isCompleteBiTree(root);
    if(ret)
    {
        printf("Is complete binary tree\n");
    }
    else
    {
        printf("Is not complete binary tree\n");
    }
}

int main()
{
    test01();
    test02();
    test03();
    return 0;
}