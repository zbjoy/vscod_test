#pragma once

#include <iostream>
#include "Class.h"

using namespace std;

class Manager
{
public:

    Manager(int n);

    ~Manager();

    Class* c;
    int numClass;
};