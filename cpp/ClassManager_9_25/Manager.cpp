#include "Manager.h"

Manager::Manager(int n)
{
    c = new Class[n];
    //this->numClass = n;
}

Manager::~Manager()
{
    delete[] c;
    c = NULL;
}