//4.请编写冒泡排序函数BubbleSort()实现对一个整型顺序表的降序排列，并在函数中输出排序的各趟结果。

#include <stdio.h>

#define MAXLEN 100

void BubbleSort(int SeqList[], int length)
{
    int i = 0;
    int j = 0;
    for(i = 0; i < length - 1; i++)
    {
        for(j = 0; j < length - i - 1; j++)
        {
            if(SeqList[j] < SeqList[j+1])
            {
                int temp = SeqList[j];
                SeqList[j] = SeqList[j + 1];
                SeqList[j + 1] = temp;
            }
        }
        printf("BubbleSort(%d):", i + 1);
        int temp = length;
        while(temp)
        {
            printf("%d ", SeqList[length - temp--]);
        }
        printf("\n");
    }
}

int main()
{
    int SeqList[MAXLEN];
    int length = 0;
    int i = 0;
    printf("Please enter length:");
    scanf("%d", &length);
    while(i < length)
    {
        int temp = 0;
        printf("Please enter your num:");
        scanf("%d", &temp);
        SeqList[i++] = temp;
    }

    BubbleSort(SeqList, length);

    return 0;
}