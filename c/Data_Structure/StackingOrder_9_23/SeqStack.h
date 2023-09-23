#include <stdio.h>

enum
{
    DATAMAX = 100
};

typedef char DataType;
typedef struct
{
    DataType data[DATAMAX];
    int top;
}SeqStack;

void Init_SeqStack(SeqStack* s);

int Push_SeqStack(SeqStack* s, DataType* px);

int Pop_SeqStack(SeqStack* s, DataType* px);

int Empty_SeqStack(SeqStack* s);

int GetTop_SeqStack(SeqStack* s,DataType* px);