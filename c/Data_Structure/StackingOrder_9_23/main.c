#include <stdio.h>
#include <stdlib.h>
#include "SeqStack.h"

int JudgeSerial(char str[], int n)
{
    SeqStack s;
    Init_SeqStack(&s);

    char temp[6] = "ABCDE"; // 判断按照ABCDE的顺序入栈是否可以按str[]中的顺序出栈

    int i = 0;
    int count = 0;
    char top;

    for(;i < n && count < 5; i++)
    {
        GetTop_SeqStack(&s, &top);
        while(str[i] != top)
        {
            Push_SeqStack(&s, &temp[count]);
            printf("%c入栈\n", temp[count++]);
            GetTop_SeqStack(&s, &top);
        }

        Pop_SeqStack(&s, &top);
        printf("%c出栈\n", top);
    }

    return Empty_SeqStack(&s);
}

int main()
{
    system("chcp 65001");
    char str[10];
    int n = 5;

    scanf("%s", &str);

    if(JudgeSerial(str, n))
    {
        printf("%s是一个正确的出栈序列\n", str);
    }
    else
    {
        printf("%s不是一个正确的出栈序列\n", str);
    }

    return 0;
}