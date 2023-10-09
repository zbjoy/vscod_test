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