#include <stdio.h>

enum
{
    DATAMAX = 7
};

typedef struct 
{
    int n;
    char X;
    char Y;
    char Z;
}datatype;

typedef datatype DataType;
typedef struct 
{
    DataType data[DATAMAX];
    int top;
}SeqStack;

void Init_SeqStack(SeqStack* s);

int Push_SeqStack(SeqStack* s, DataType* px);

int Pop_SeqStack(SeqStack* s, DataType* px);

int Empty_SeqStack(SeqStack* s);

int GetTop_SeqStack(SeqStack* s, DataType* px);