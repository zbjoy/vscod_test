#include "BiTree.h"

void Initiate(BiTree* root, DataType x)
{
    *root = (BiTree)malloc(sizeof(BiTreeNode));
    (*root)->data = x;
    (*root)->lchild = NULL;
    (*root)->rchild = NULL;
}

BiTree InsertLeftNode(BiTree curr, DataType x)
{
    if(curr == NULL)
    {
        return NULL;
    }
    BiTree s = (BiTree)malloc(sizeof(BiTreeNode));
    s->data = x;
    s->lchild = curr->lchild;
    s->rchild = NULL;
    curr->lchild = s;
    return curr->lchild;
}

BiTree InsertRightNode(BiTree curr, DataType x)
{
    if(curr == NULL)
    {
        return NULL;
    }
    BiTree s = (BiTree)malloc(sizeof(BiTreeNode));
    s->data = x;
    s->rchild = curr->rchild;
    s->lchild = NULL;
    curr->rchild = s;
    return curr->rchild;
}

BiTree DeleteLeftTree(BiTree curr)
{

}

BiTree DeleteRightTree(BiTree curr)
{

}

void CreateBiTree(BiTree* root)
{
    BiTree p;
    Initiate(root, 'A');
    p = InsertLeftNode(*root, 'B');
    p = InsertRightNode(p, 'D');
    p = InsertRightNode(p, 'G');
    p = InsertRightNode(*root, 'C');
    InsertLeftNode(p, 'E');
    InsertRightNode(p, 'F');
}

int LeafNode_Num(BiTree root)
{
    static int num = 0;
    if(root == NULL)
    {
        return num;
    }
    else if(root->lchild == NULL && root->rchild == NULL)
    {
        num++;
        return num;
    }
    else
    {
        LeafNode_Num(root->lchild);
        LeafNode_Num(root->rchild);
        return num;
    }
}

int HeightBiTree_Num(BiTree root)
{
    static int MaxNum = 0;
    static int Num = 0;

    if(root == NULL)
    {
        return MaxNum;
    }
    else if(root->lchild != NULL)
    {
        Num++;
        HeightBiTree_Num(root->lchild);
    }
    else if(root->lchild == NULL)
    {
        if(root->rchild == NULL)
        {
            Num++;
            if(MaxNum < Num)
            {
                MaxNum = Num;
            }
            Num--;
            return MaxNum;
        }
        else
        {
            Num++;
            HeightBiTree_Num(root->rchild);
        }
    }
}

// int isCompleteBiTree(BiTree root)
// {
//     // static int isCom = 1;
//     // static int temp = 0;

//     // if(root == NULL)
//     // {
//     //     return isCom;
//     // }
//     // else if(root->lchild == NULL && temp == 0)
//     // {
//     //     temp = 1;
//     // }

//     // return isCom;
// }