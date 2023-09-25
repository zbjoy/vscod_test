#include <iostream>
using namespace std;

    //获取参数方式 cin
    //int x =0;
    //cin >> x;

    //结果输出使用 cout
    //cout<<"1";

 	// 请在此添加你的代码
    /********** Begin ********/

class Student
{
public:

    int score;
};

class Manager
{
public:

    Manager(int n);

    ~Manager();

    Student* s;

};

Manager::Manager(int n)
{
    s = new Student[n];
}

Manager::~Manager()
{
    delete[] s;
    s = NULL;
}

int main()
{
    int num;
    cin >> num;
    Manager m(num);
    int tempScore;

    for(int i = 0; i < num; i++)
    {
        cin >> tempScore;
        //cin.clear();
        m.s[i].score = tempScore;
    }

    int pos;
    cin >> pos;

    cout << m.s[pos-1].score << endl;
}