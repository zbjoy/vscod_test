#include <iostream>

class Sample
{
public:
    Sample(){};

    Sample(int a)
    {
        x = a;
    }

    Sample(Sample& a)
    {
        x = a.x++;
        //x++;
    }

    void disp()
    {
        std::cout << x++;
    }

private:
    int x;
};

void fun(Sample& s1, Sample s2)
{
    s1.disp();
    s2.disp();
}

int main()
{
    Sample s1(2), s2 = s1;
    fun(s2, s1);
    s1.disp();
    s2.disp();
    return 0;
}