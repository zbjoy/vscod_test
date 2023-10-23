#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char error[100];
int errorLen = 0;
int n = 0;


int isError(char x)
{
    int temp = 0;
    while (temp < errorLen)
    {
        if (error[temp] == x)
        {
            return 1;
        }
        temp++;
    }

    return 0;
}

typedef struct node
{
    char data;
    struct node* lchild;
    struct node* rchild;
}BSTNode;

BSTNode** nBST;

char pre[10];
char in[10];

BSTNode* insertRightNode(BSTNode* curr, char x)
{
    BSTNode* s = (BSTNode*)malloc(sizeof(BSTNode));
    if (s == NULL)
    {
        return NULL;
    }

    s->data = x;
    s->lchild = curr->lchild;
    s->rchild = NULL;

    curr->lchild = s;

    return s;
}

BSTNode* insertLeftNode(BSTNode* curr, char x)
{
    BSTNode* s = (BSTNode*)malloc(sizeof(BSTNode));
    if (s == NULL)
    {
        return NULL;
    }

    s->data = x;
    s->rchild = curr->lchild;
    s->lchild = NULL;

    curr->rchild = s;

    return s;
}

int isLeft(char* s, char d)
{
    int len = strlen(s); //
    if (len == 0)
    {
        return 0;
    }

    int temp = 0;
    while (temp < len)
    {
        if (s[temp] == d)
        {
            break;
        }
        temp++;
    }

    if (temp != 0 && temp < len)
    {
        if(!isError(s[temp - 1]))
        return 1;
    }

    return 0;
}

int isRight(char* s, char d)
{
    int len = strlen(s); //
    if (len == 0)
    {
        return 0;
    }

    int temp = 0;
    while (temp < len)
    {
        if (s[temp] == d)
        {
            break;
        }
        temp++;
    }

    if (temp >= 0 && temp <= len - 1)
    {
        if (!isError(s[temp + 1]))
        return 1;
    }

    return 0;
}

char* tempPre;

//int ret = 0;

BSTNode* BSTCreate_PreIn(BSTNode** curr, char* pre, char* in)
{
    int ret = 0;
    if (pre == NULL)
    {
        return *curr;
    }

    if(n == 0)
    {
        nBST = curr;
    }

    (*curr)->data = *pre;
    error[errorLen++] = *pre;
    n++;

    if (isLeft(in, *pre) && isRight(in, *pre))
    {
        ret = 1;
    }

    //(*curr)->lchild = (BSTNode*)malloc(sizeof(BSTNode));
    //(*curr)->rchild = (BSTNode*)malloc(sizeof(BSTNode));
    //(*curr)->lchild->lchild = NULL;
    //(*curr)->lchild->rchild = NULL;
    //(*curr)->rchild->lchild = NULL;
    //(*curr)->rchild->rchild = NULL;

    if (isLeft(in, *pre))
    {
        (*curr)->lchild = (BSTNode*)malloc(sizeof(BSTNode));
        (*curr)->lchild->lchild = NULL;
        (*curr)->lchild->rchild = NULL;
        // n++;
        BSTCreate_PreIn(&((*curr)->lchild), pre + 1, in);
    }

    if (isRight(in, *pre))
    {
        if (ret)
        {
            // if(nBST != curr)
            // {
            //     pre = tempPre + n;
            // }
            // else
            {
                //pre += n + 1;
                pre = tempPre + n - 1;
                //n = -1;
                ret = 0;
            }
            
        }
        (*curr)->rchild = (BSTNode*)malloc(sizeof(BSTNode));
        (*curr)->rchild->lchild = NULL;
        (*curr)->rchild->rchild = NULL;
        // n++;
        BSTCreate_PreIn(&((*curr)->rchild), pre + 1, in);

    }

    printf("%c ", ((*curr)->data));
    return *curr;
}



int main()
{
    gets(pre);
    tempPre = pre;
    gets(in);
    BSTNode* curr = (BSTNode*)malloc(sizeof(BSTNode));
    curr->lchild = NULL;
    curr->rchild = NULL;
    BSTCreate_PreIn(&curr, pre, in);
}
