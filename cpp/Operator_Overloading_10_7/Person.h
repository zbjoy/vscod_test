#include <iostream>
#include <string.h>

using namespace std;

class Person
{
public:

    Person();

    Person(char* name, int age);

    Person& operator=(Person& peo);

    ~Person();

private:

    char* m_Name;

    int m_Age;
};