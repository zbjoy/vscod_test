#include "Circular_List.h"

int InsertByHead_CirList(CircularList* head, char x[])
{
    CircularList* c = (CircularList*)malloc(sizeof(CircularList));
    strcpy(c->Name, x);
    
    c->next = head->next;
    head->next = c;

    return 1;
}

int printAll_CircularList(CircularList* head)
{
    CircularList* c = (CircularList*)malloc(sizeof(CircularList));
    c = head->next;
    while(c != head)
    {
        printf("%s", c->Name);
        c = c->next;
    }

    return 1;
}