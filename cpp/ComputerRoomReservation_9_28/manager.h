#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#include "Identity.h"
#include "student.h"
#include "teacher.h"
#include "globalFile.h"
#include "ComputerRoom.h"

class Manager :public Identity
{
public:

    //构造函数
    Manager();

    //有参构造
    Manager(string name, string pwd);

    //选择菜单
    void operMenu();

    //添加账号
    void addPerson();

    //查看账号
    void showPerson();

    //查看机房信息
    void showComputer();

    //清空预约记录
    void clearFile();

    //初始化容器
    void initVector();

    //检测重复
    bool checkRepeat(int id, int type);

    //学生容器
    vector<Student> vStu;

    //教师容器
    vector<Teacher> vTea;

    //机房容器
    vector<ComputerRoom> vCom;

};