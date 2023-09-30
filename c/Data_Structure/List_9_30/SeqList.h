#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAMEMAX 10

typedef struct SeqList
{
    char Name[NAMEMAX];
    struct SeqList* next;
}SeqList;

int InsertByHead_SeqList(SeqList* head, char x[]);

int InsertByRear_SeqList(SeqList* head, char x[]);

int Delete_SeqList(SeqList* head, int pos);

int print_SeqList(SeqList* head, int pos);

int printAll_SeqList(SeqList* head);

#endif