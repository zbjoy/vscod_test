#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAMEMAX 10

typedef struct CircularList
{
    char Name[NAMEMAX];
    struct CircularList* next;
}CircularList;

int InsertByHead_CirList(CircularList* head, char x[]);

int printAll_CircularList(CircularList* head);