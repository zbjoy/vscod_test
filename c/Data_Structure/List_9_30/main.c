#include <stdio.h>
#include <stdlib.h>

#include "SeqList.h"

int main()
{
    SeqList* head = (SeqList*)malloc(sizeof(SeqList));
    head->next = NULL;
    Push_SeqList(head, "hello");
    Push_SeqList(head, " world");
    print_SeqList(head, 1);

    Delete_SeqList(head, 1);
    print_SeqList(head, 1);
    return 0;
}