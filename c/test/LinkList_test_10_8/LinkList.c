#include "LinkList.h"

LinkList CreateListR(LinkList head)
{
    LinkList p;
    p = head;
    int i = 0;
    int n = 0;
    scanf("%d", &n);
    for(; i < n; i++)
    {
        p->next = (LinkList)malloc(sizeof(LNode));
        p = p->next;
        scanf("%d", &p->val);
    }
    p->next = NULL;
    return head;
}

int PrintList(LinkList head)
{
    while(head->next != NULL)
    {
        head = head->next;
        printf("%d\n", head->val);
    }

    return 1;
}

LinkList CreateListR_NoHeadNode(LinkList head)
{
    LinkList p = (LinkList)malloc(sizeof(LNode));
    p = head;
    int i = 0;
    int n = 0;
    scanf("%d", &n);
    for(; i < n; i++)
    {
        scanf("%d", &p->val);
        p->next = (LinkList)malloc(sizeof(LNode));
        if(i < n - 1)
        p = p->next;
    }
    p->next = NULL;
    return head;
}

int PrintList_NoHeadNode(LinkList head)
{
    while(head != NULL)
    {
        printf("%d\n", head->val);
        head = head->next;
    }

    return 1;
}