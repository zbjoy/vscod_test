// 1．编写在以T为根结点的二叉树中查找值为x的双亲结点函数void SearchParent(struct BTNode *t,char x)。在主函数中利用
//先序遍历算法创建二叉树，之后输入需查找双亲的结点值x,再调用该函数查找x的双亲，双亲结点指针由全局指针变量p传回给主函数
//，最后在主函数中输出该结点的双亲结点。当二叉树是空树或者x就处于根结点或者在二叉树不存在x结点时，双亲指针均为空指针，
//否则p指向双亲结点。在主函数中双亲指针为空时均输出#，否则输出该双亲结点的值。
// 注意：二叉树结点数据为单个字母字符。当输入字符“#”时表示不需要创建结点。已给出主要函数，请补全SearchParents()函数。

#include<stdio.h>
#include<stdlib.h>

struct BTNode
{      
    char data;
    struct BTNode *lchild;
    struct BTNode *rchild;
};

void PreOrderCreate(struct BTNode **p)//先序遍历创建二叉树
{       
    char a;
    scanf("%c",&a);
    if(a=='#') 
        *p=NULL;
    else
    {      
        *p=(struct BTNode*)malloc(sizeof(struct BTNode));
        (*p)->data=a;
        PreOrderCreate(&(*p)->lchild);
        PreOrderCreate(&(*p)->rchild);
    }
}

struct BTNode *p=NULL;

void SearchParents(struct BTNode *t,char x)//此处添加查找二叉树指定结点的双亲结点函数
{
    if(t != NULL)
    {
        if(t->lchild != NULL)
        {
            if(t->lchild->data == x)
            {
                p = t;
                return;
            }
        }
        else if(t->rchild != NULL)
        {
            if(t->rchild->data == x)
            {
                p = t;
                return;
            }
        }

        SearchParents(t->lchild, x);
        SearchParents(t->rchild, x);
    }

}

int main()

{      
    struct BTNode *t;
    char x;
    PreOrderCreate(&t);
    getchar();
    scanf("%c",&x);
    SearchParents(t,x);
    if(p==NULL) 
        printf("#");
    else
        printf("%c",p->data);
}