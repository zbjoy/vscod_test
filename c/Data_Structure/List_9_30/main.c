#include <stdio.h>
#include <stdlib.h>

#include "SeqList.h"
#include "Circular_List.h"

void test01() //头插法单链表
{
    SeqList* head = (SeqList*)malloc(sizeof(SeqList));
    head->next = NULL;
    InsertByHead_SeqList(head, " world");
    InsertByHead_SeqList(head, "hello");
    print_SeqList(head, 1);

    Delete_SeqList(head, 1);
    print_SeqList(head, 1);
    printAll_SeqList(head);
}

void test02() //尾插法单链表
{
    SeqList* head = (SeqList*)malloc(sizeof(SeqList));
    head->next = NULL;
    InsertByRear_SeqList(head, "hello");
    InsertByRear_SeqList(head, " world");
    printAll_SeqList(head);
}

void test03() //循环链表
{
    CircularList* head = (CircularList*)malloc(sizeof(CircularList));
    head->next = head;

    InsertByHead_CirList(head, " world");
    InsertByHead_CirList(head, "hello");

    printAll_CircularList(head);
}

int main()
{
    test01(); //头插法单链表
    printf("\n\n");
    test02(); //尾插法单链表
    printf("\n\n");
    test03(); //循环链表
    return 0;
}