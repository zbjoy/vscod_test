#include <iostream>
#include "Class.h"
#include "Manager.h"

using namespace std;

// 统计多个班级的所有学生的C++课程成绩。

// 要求：

// 动态分配和释放空间；
// 输入第一行为班级数N；
// 然后输入N行，第 i 行的第一个数表示第 i 个班有多少人（记为ni），第i行后ni个数分别表示第 i 班第0号学员到第ni -1号学员的C++成绩， 班级和人员的编号都从0开始；
// 最后，输入整数x和y，程序输出第x号班第y号人的成绩。
// 效果如下：
// 输入：

// 3
// 2 90 100
// 3 91 92 93
// 4 100 99 96 95
// 1 1

// 输出：92 

int main()
{
    int n;
    int tempScore;
    cin>>n;
    Manager m(n);

    for(int i = 0; i < n; i++)
    {
        int x;
        cin>>x;
        m.c[i].student = new Student[x];
        for(int j = 0; j < x; j++)
        {
            cin>>tempScore;
            m.c[i].student[j].score = tempScore;
        }
    }

    int posClass;
    int posStudent;
    cin>>posClass;
    cin>>posStudent;
    cout << m.c[posClass].student[posStudent].score << endl;

    return 0;
}