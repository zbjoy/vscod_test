#include <stdio.h>

#include "LinkList.h"

int main()
{
    // LinkList head = (LinkList)malloc(sizeof(LNode));
    // CreateListR(head);
    // PrintList(head);
    LinkList head1 = (LinkList)malloc(sizeof(LNode));
    CreateListR_NoHeadNode(head1);
    PrintList_NoHeadNode(head1);
    return 0;
}