#pragma once

#include <iostream>
#include <string>

using namespace std;

enum
{
    NAMEMAX = 15
};

class Speaker
{
public:

    string m_Name;

    float m_Score[2];
};