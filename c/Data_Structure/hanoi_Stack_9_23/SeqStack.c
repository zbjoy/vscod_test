#include "SeqStack.h"

void Init_SeqStack(SeqStack* s)
{
    s->top = -1;
}

int Push_SeqStack(SeqStack* s, DataType* px)
{
    if(s->top == DATAMAX - 1)
    {
        return 0;
    }

    s->top++;
    s->data[s->top] = *px;
    return 1;
}

int Pop_SeqStack(SeqStack* s, DataType* px)
{
    if(Empty_SeqStack(s))
    {
        return 0;
    }

    *px = s->data[s->top];
    s->top--;
    return 1;
}

int Empty_SeqStack(SeqStack* s)
{
    if(s->top == -1)
    {
        return 1;
    }

    return 0;
}

int GetTop_SeqStack(SeqStack* s, DataType* px)
{
    if(Empty_SeqStack(s))
    {
        return 0;
    }

    *px = s->data[s->top];
    return 1;
}