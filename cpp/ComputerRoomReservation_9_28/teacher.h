#pragma once

#include <iostream>

using namespace std;

#include "Identity.h"

class Teacher :public Identity
{
public:

    //构造函数
    Teacher();

    //有参构造
    Teacher(int empId, string name, string pwd);

    //菜单界面
    void operMenu();

    //查看所有预约
    void showAllOrder();

    //审核预约
    void vaildOrder();

    int m_EmpId; //教师编号
};

