#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAMEMAX 10

typedef struct SeqList
{
    char Name[NAMEMAX];
    struct SeqList* next;
}SeqList;

int Push_SeqList(SeqList* head, char x[]);

int Delete_SeqList(SeqList* head, int pos);

int print_SeqList(SeqList* head, int pos);