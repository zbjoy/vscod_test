#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node* next;
}LNode, *LinkList;

LinkList CreateListR(LinkList head);

int PrintList(LinkList head);

LinkList CreateListR_NoHeadNode(LinkList head);

int PrintList_NoHeadNode(LinkList head);