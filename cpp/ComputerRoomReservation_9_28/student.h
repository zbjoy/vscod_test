#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

#include "Identity.h"
#include "computerRoom.h"
#include "globalFile.h"
#include "orderFile.h"

class Student :public Identity
{
public:

    //默认构造函数
    Student();

    //有参构造函数
    Student(int id, string name, string pwd);

    //菜单界面
    void operMenu();

    //申请预约
    void applyOrder();

    //查看我的预约
    void showMyOrder();

    //查看所有预约
    void showAllOrder();

    //取消预约
    void cancelOrder();

    //学生学号
    int m_Id;

    //机房信息容器
    vector<ComputerRoom> vCom;

};