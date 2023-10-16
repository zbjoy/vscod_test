#include "SeqQueue.h"

void iniQueue(SeqQueue* q)
{
    q->front = q->rear = 0;
}

int QueueEmpty(SeqQueue* q)
{
    if(q->front == q->rear)
    {
        return 1;
    }
    return 0;
}

int EnQueue(SeqQueue* q, BiTree* x)
{
    if((q->rear + 1) % MAXSIZE == q->front)
    {
        return 0;
    }

    q->data[q->rear] = *x;
    q->rear = (q->rear + 1) % MAXSIZE;

    return 1;
}

int DeQueue(SeqQueue* q, BiTree* x)
{
    if(QueueEmpty(q))
    {
        return 0;
    }

    *x = q->data[q->front];
    q->front = (q->front + 1) % MAXSIZE;
    return 1;
}

int GetQueueHead(SeqQueue* q, BiTree* x)
{
    if(QueueEmpty(q))
    {
        return 0;
    }
    
    *x = q->data[q->front];
    return 1;
}