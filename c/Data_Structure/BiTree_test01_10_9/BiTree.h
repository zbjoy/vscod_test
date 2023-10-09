#include <stdio.h>
#include <stdlib.h>

typedef char DataType;
typedef struct Node
{
    DataType data;
    struct Node* lchild;
    struct Node* rchild;
}BiTreeNode, *BiTree;

void Initiate(BiTree* root, DataType x);

BiTree InsertLeftNode(BiTree curr, DataType x);

BiTree InsertRightNode(BiTree curr, DataType x);

BiTree DeleteLeftTree(BiTree curr);

BiTree DeleteRightTree(BiTree curr);

void CreateBiTree(BiTree* root);

int LeafNode_Num(BiTree root);