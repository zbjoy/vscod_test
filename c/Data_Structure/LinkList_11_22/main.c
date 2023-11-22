#include <stdio.h>
#include <stdlib.h>

//1、单链表的创建 
//2、头插法建立单链表
//3、尾插法建立单链表
//4、单链表插入和删除 

// 1
typedef int DataType;
typedef struct Node
{
    DataType data;
    struct Node* next;
}LNode, *LinkList;

//单链表的数据打印
//(有头结点)
void PrintList_HeadNode(LinkList head)
{
    if(!head)
    {
        return;
    }
    else
    {
        head = head->next;
    }
    while(head)
    {
        printf("data is %d\n", head->data);
        head = head->next;
    }
}
//(无头结点)
void PrintList(LinkList head)
{
    while(head)
    {
        printf("data is %d\n", head->data);
        head = head->next;
    }
}

// 2 (有头结点)
int CreateListF_HeadNode(LinkList head)
{
    int n;
    printf("Please enter the number of nodes:");
    scanf("%d", &n);
    int i = 0;
    for(int i = 0; i < n; i++)
    {
        printf("please enter %d data:", i + 1);
        LinkList s = (LinkList)malloc(sizeof(LNode));
        scanf("%d", &s->data);
        s->next = head->next;
        head->next = s;
    }
    return 1;
}

// 2 (无头结点)
LinkList CreateListF(LinkList head)
{
    int n;
    printf("Please enter the number of nodes:");
    scanf("%d", &n);
    int i = 0;
    for(int i = 0; i < n; i++)
    {
        printf("please enter %d data:", i + 1);
        LinkList s = (LinkList)malloc(sizeof(LNode));
        scanf("%d", &s->data);
        s->next = head;
        head = s;
    }
    return head;
}

// 3 (有头结点)
int CreateListR_HeadNode(LinkList head)
{
    LinkList t = head;
    int n;
    printf("Please enter the number of nodes:");
    scanf("%d", &n);
    int i = 0;
    for(int i = 0; i < n; i++)
    {
        printf("please enter %d data:", i + 1);
        LinkList s = (LinkList)malloc(sizeof(LNode));
        scanf("%d", &s->data);
        t->next = s;
        t = s;
    }
    t->next = NULL;
    return 1;
}

// 3 (无头结点)
LinkList CreateListR(LinkList head)
{
    LinkList t = head;
    int n;
    printf("Please enter the number of nodes:");
    scanf("%d", &n);
    int i = 0;
    for(int i = 0; i < n; i++)
    {
        printf("please enter %d data:", i + 1);
        LinkList s = (LinkList)malloc(sizeof(LNode));
        scanf("%d", &s->data);
        if(i == 0)
        {
            head = s;
        }
        else
        {
            t->next = s;
        }
        t = s;
    }
    t->next = NULL;
    return head;
}

// 4 (插入)
int InsertList_HeadNode(LinkList head,DataType data, int pos)
{
    while(head && --pos)
    {
        head = head->next;
    }

    if(!head)
    {
        return 0;
    }
    else
    {
        LinkList s = (LinkList)malloc(sizeof(LNode));
        s->data = data;
        s->next = head->next;
        head->next = s;
        return 1;
    }
}

// 4 (删除)
int DeletList_HeadNode(LinkList head, int pos)
{
    while(head && --pos)
    {
        head = head->next;
    }

    if(!head)
    {
        return 0;
    }
    else
    {
        LinkList t = head->next;
        head->next = t->next;
        free(t);
        return 1;
    }
}

void test01() //有头结点链表的创建(头插法)
{
    LinkList head = (LinkList)malloc(sizeof(LNode));
    head->next = NULL;
    CreateListF_HeadNode(head);
    PrintList_HeadNode(head);
}

void test02() //无头结点链表的创建(头插法)
{
    LinkList head = NULL;
    head = CreateListF(head);
    PrintList(head);
}

void test03() //有头结点链表的创建(尾插法)
{
    LinkList head = (LinkList)malloc(sizeof(LNode));
    head->next = NULL;
    CreateListR_HeadNode(head);
    PrintList_HeadNode(head);
}

void test04() //无头结点链表的创建(尾插法)
{
    LinkList head = NULL;
    head = CreateListR(head);
    PrintList(head);
}

void test05() //有头结点链表的插入
{
    LinkList head = (LinkList)malloc(sizeof(LNode));
    head->next = NULL;
    CreateListR_HeadNode(head);
    PrintList_HeadNode(head);

    printf("\n\n");

    InsertList_HeadNode(head, 5, 1);
    PrintList_HeadNode(head);
}

void test06() //有头结点链表的删除
{
    LinkList head = (LinkList)malloc(sizeof(LNode));
    head->next = NULL;
    CreateListR_HeadNode(head);
    PrintList_HeadNode(head);

    printf("\n\n");

    DeletList_HeadNode(head, 1);
    PrintList_HeadNode(head);
}

int main()
{
    //test01();
    //test02();
    //test03();
    //test04();
    //test05();
    test06();
    return 0;
}