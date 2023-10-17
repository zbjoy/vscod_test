#include<stdio.h>
#include<stdlib.h>

typedef struct BiTNode              //定义二叉树结点数据类型
{
    char data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

BiTree InsertLeftNode(BiTree curr, char x)
{
    if(!curr)
    {
        return NULL;
    }
    BiTree s = (BiTree)malloc(sizeof(BiTNode));
    s->data = x;
    s->lchild = curr->lchild;
    s->rchild = NULL;
    curr->lchild = s;
    return curr->lchild;
}

BiTree InsertRightNode(BiTree curr, char x)
{
    if(!curr)
    {
        return NULL;
    }
    BiTree s = (BiTree)malloc(sizeof(BiTNode));
    s->data = x;
    s->rchild = curr->rchild;
    s->lchild = NULL;
    curr->rchild = s;
    return curr->rchild;
}

BiTree p = NULL;
int ret = 0;

void InOrder(BiTree root, char e)
{
    if(root)
    {
        InOrder(root->lchild, e);

        if(root->data > e)
        {
            p = root;
            return;
        }
        else if(root->data == e)
        {
            ret = 1;
            return;
        }

        InOrder(root->rchild, e);
    }
}

int InsertBST(BiTree *T,char e)//插入值为e的结点，使中序遍历仍为升序
{

    InOrder(*T, e);

    if(ret == 1)
    {
        return 0;
    }

    if(p == NULL)
    {
        BiTree temp = *T;
        while(temp->rchild != NULL)
        {
            temp = temp->rchild;
        }
        InsertRightNode(temp, e);
        return 1;
    }

    if(p->lchild == NULL)
    {
        InsertLeftNode(p, e);
        return 1;
    }

    p = p->lchild;
    while(p->rchild)
    {
        p = p->rchild;
    }
    InsertRightNode(p, e);
    return 1;
    
}

void PreOrderCreate(struct BiTNode **p)//先序遍历创建二叉树

{
    char a;
    scanf("%c",&a);
    if(a=='#') *p=NULL; //当接收到的结点值为’#’时，递归过程结束
    else
    {
        *p=(struct BiTNode*)malloc(sizeof(struct BiTNode));
       (*p)->data=a;
       PreOrderCreate(&(*p)->lchild);
       PreOrderCreate(&(*p)->rchild);
    }
}

void InOrderTraverse(BiTree T)//中序遍历后二叉树
{

    if(!T)
        return;
    InOrderTraverse(T->lchild);
    printf("%c ", T->data);
    InOrderTraverse(T->rchild);
}

int main()

{
    BiTree root=NULL;
    char ch;
    PreOrderCreate(&root);
    getchar();
    scanf("%c",&ch);
    InsertBST(&root,ch);
    InOrderTraverse(root);
    printf("\n");
    return 0;
}