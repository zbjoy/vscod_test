#include <stdio.h>
#include <stdlib.h>

#include "BiTree.h"

int main()
{
    BiTree root = (BiTree)malloc(sizeof(BiTreeNode));
    CreateBiTree(&root);
    int num1 = LeafNode_Num(root);
    printf("%d\n", num1);
    return 0;
}