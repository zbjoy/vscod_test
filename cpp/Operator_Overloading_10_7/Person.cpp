#include "Person.h"

Person::Person()
{

}

Person::Person(char* name, int age)
{
    int len = strlen(name);
    m_Name = new char[len + 1];

    strcpy_s(m_Name, len + 1, name);
    m_Age = age;
}

Person& Person::operator=(Person& peo)
{
    if(this == &peo)
    {
        return *this;
    }

    delete[] m_Name;

    int len = strlen(peo.m_Name);
    
}

Person::~Person()
{

}