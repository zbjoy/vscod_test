#include <stdio.h>

#include "BiTree.h" //怎么才能只把BiTree这个结构体在这个.h中声明

#define MAXSIZE 30

typedef struct SeqQueue
{
    BiTree data[MAXSIZE];
    int rear;
    int front;
}SeqQueue;

void iniQueue(SeqQueue* q);

int QueueEmpty(SeqQueue* q);

int EnQueue(SeqQueue* q, BiTree* x);

int DeQueue(SeqQueue* q, BiTree* x);

int GetQueueHead(SeqQueue* q, BiTree* x);
