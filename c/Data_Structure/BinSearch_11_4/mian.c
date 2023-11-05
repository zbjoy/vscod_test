//3.编写折半查找函数BinSearch，实现在一个按学号降序排列的学生信息顺序表上查找指定学号学生的功能。
//  请在以下代码基础上完成BinSearch函数的编写及在主函数对BinSearch函数的调用。

#include<stdio.h>
#define MAXLEN 100
typedef struct 
{    
    int num;
    char name[10];
    int age;
}DataType;

typedef struct 
{    
    DataType list[MAXLEN];
    int length;
}SeqList;

int BinSearch(SeqList *L, int tnum, int left, int right);

int main()
{    
    int i,n,tnum;
    SeqList a;
    scanf("%d",&a.length);
    for(i=1;i<=a.length;i++)
    scanf("%d%s%d",&a.list[i].num, a.list[i].name,&a.list[i].age);
    scanf("%d",&tnum);
    //此处添加调用BinSearch函数实现按照学号进行查找的语句
    int ret = BinSearch(&a, tnum, 1, a.length);
    if(ret == -1)
    {
        printf("Can not found!\n");
    }
    else
    {
        printf("The student is:\nnum:%-5dname:%-10sage:%-5d\n", a.list[ret].num, a.list[ret].name, a.list[ret].age);
    }

    return 0;
}

int BinSearch(SeqList *L, int tnum, int left, int right)
{
    if(left > right)
    {
        return -1;
    }
    
    int mid = (left + right) / 2;
    if(L->list[mid].num == tnum)
    {
        return mid;
    }
    else
    {
        if(L->list[mid].num > tnum)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
        return BinSearch(L, tnum, left, right);
    }
    

    return -1;
}