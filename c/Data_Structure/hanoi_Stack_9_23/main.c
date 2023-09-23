#include <stdio.h>
#include "SeqStack.h"

void hanoi(int n, char A, char B, char C)
{
    if(n == 1)
    {
        printf("%c-->%c\n", A, C);
    }
    else
    {
        hanoi(n-1, A, C, B);
        printf("%c-->%c\n", A, C);
        hanoi(n-1, B, A, C);
    }
}

void hanoi_Stack(int n, char X, char Y, char Z)
{
    datatype e;
    datatype temp;
    char t;
    e.n = n;
    e.X = X;
    e.Y = Y;
    e.Z = Z;
    SeqStack s;
    Init_SeqStack(&s);
    Push_SeqStack(&s, &e);
    while(!Empty_SeqStack(&s))
    {
        GetTop_SeqStack(&s, &temp);
        while(temp.n > 1)
        {
            e.n = temp.n - 1;
            e.X = temp.X;
            e.Y = temp.Z;
            e.Z = temp.Y;
            Push_SeqStack(&s, &e);
            GetTop_SeqStack(&s, &temp);
        }

        printf("%c-->%c\n", temp.X, temp.Z);
        Pop_SeqStack(&s, &temp);
        GetTop_SeqStack(&s, &temp);
        if(!Empty_SeqStack(&s))
        {
            printf("%c-->%c\n", temp.X, temp.Z);
            Pop_SeqStack(&s, &temp);
            e.n = temp.n - 1;
            //Push_SeqStack(&s, &e);
            t = temp.X;
            e.X = temp.Y;
            e.Y = t;

            e.Z = temp.Z;

            Push_SeqStack(&s, &e);
        }
    }
}

int main()
{
    hanoi(3, 'A', 'B', 'C');
    printf("\n");
    hanoi_Stack(3, 'A', 'B', 'C');
    return 0;
}