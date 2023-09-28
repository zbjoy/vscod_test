#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <string>

using namespace std;

#include "Identity.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"
#include "globalFile.h"

void mainMenu()
{
    cout << "**********************  Welcome to  ComputerRoom Reservation System   **************************" << endl;
    cout << endl;

    cout << "Please enter your identity:" << endl;
    cout << "\t\t---------------------------------------------------" << endl;
    cout << "\t\t|                                                 |" << endl;
    cout << "\t\t|          1 . Student representatives            |" << endl;
    cout << "\t\t|                                                 |" << endl;
    cout << "\t\t|          2 .         Teacher                    |" << endl;
    cout << "\t\t|                                                 |" << endl;
    cout << "\t\t|          3 .         Manager                    |" << endl;
    cout << "\t\t|                                                 |" << endl;
    cout << "\t\t|          0 .          Exit                      |" << endl;
    cout << "\t\t|                                                 |" << endl;
    cout << "\t\t---------------------------------------------------" << endl;
}

void ManagerMenu(Identity* &manager)
{
    
    Manager* man = (Manager*)manager;
    int select = 0;

    while(true)
    {
        //管理员菜单
        manager->operMenu();

        cout << "Please enter your select:";
        cin >> select;

        switch(select)
        {
        case 1: //添加账号
            man->addPerson(); 
            break;
        case 2: //查看账号
            man->showPerson();
            break;
        case 3: //查看机房
            man->showComputer();
            break;
        case 4: //清空预约
            man->clearFile();
            break;
        case 0: //退出管理员系统
            delete manager;
            cout << "Logged out successfully" << endl;
            system("pause");
            system("cls");
            return;
        default: //输入错误
            cout << "Your enter is error, please enter again" << endl;
            system("pause");
            system("cls");
            break;
        }
    }
}

void TeacherMenu(Identity* &teacher)
{

    Teacher* tea = (Teacher*)teacher;
    int select = 0;

    while(true)
    {           
        //教师菜单
        teacher->operMenu();

        cout << "Please enter your select:" << endl;
        cin >> select;

        switch(select)
        {
        case 1: //查看所有预约
            tea->showAllOrder();
            break;
        case 2: //审核预约
            tea->vaildOrder();
            break;
        case 0: //退出教师系统
            delete teacher;
            cout << "Logged out successfully" << endl;
            system("pause");
            system("cls");
            return;
        default:
            cout << "Your enter is error, please enter again" << endl;
            system("pause");
            system("cls");
            break;
        }
    }
}

void StudentMenu(Identity* &student)
{
    Student* stu = (Student*)student;
    int select = 0;
    
    while(true)
    {
        student->operMenu();

        cout << "Please enter your select:" << endl;
        cin >> select;

        switch(select)
        {
        case 1: //申请预约
            stu->applyOrder();
            break;
        case 2: //查看我的预约
            stu->showMyOrder();
            break;
        case 3: //查看全部预约
            stu->showAllOrder();
            break;
        case 4: //取消预约
            stu->cancelOrder();
            break;
        case 0: //退出系统
            delete student;
            cout << "Logged out successfully" << endl;
            system("pause");
            system("cls");
            return;
        default: //输入错误
            cout << "Your enter is error, please enter again" << endl;
            system("pause");
            system("cls");
            break;
        }
    }
}

//登录功能
void LoginIn(string fileName, int type)
{
    FILE* pfread;

    if(type == 1) //读取学生时间文件
    {
        pfread = fopen(TIME_STUDENT_FILE, "rb");
    }
    else if(type == 2) //读取教师时间文件
    {
        pfread = fopen(TIME_TEACHER_FILE, "rb");
    }
    else //读取管理员时间文件
    {
        pfread = fopen(TIME_ADMIN_FILE, "rb");
    }

    if(pfread != NULL)
    {
        struct tm tempTime;
        fread(&tempTime, sizeof(struct tm), 1, pfread);

        time_t tempRawTime;
        time(&tempRawTime);
        struct tm* nowTime = localtime(&tempRawTime);

        if(tempTime.tm_year == nowTime->tm_year)
        {
            if(tempTime.tm_mon == nowTime->tm_mon)
            {
                if(tempTime.tm_mday == nowTime->tm_mday)
                {
                    if(tempTime.tm_hour == nowTime->tm_hour)
                    {
                        int num = 0;
                        num = nowTime->tm_min - tempTime.tm_min;
                        if(num <= 5)
                        {
                            cout << "You need after " << 5 - num << " minutes to try again!" << endl;
                            system("pause");
                            system("cls");
                            return;
                        }
                        fclose(pfread);
                        pfread = NULL;
                    }
                }
            }
        }
    }
    else
    {
        fclose(pfread);
        pfread = NULL;
    }

    Identity* person = NULL;

    ifstream ifs;
    ifs.open(fileName, ios::in);

    //文件不存在
    if(!ifs.is_open())
    {
        cout << fileName << "File does not exist!!!" << endl;
        ifs.close();
        return;
    }

    int id = 0;
    string name;
    string pwd;

    for(int i = 2; i >= 0; i--)
    {
        if(type == 1) //学生登录
        {
            cout << "Please enter your student ID:" << endl;
            cin >> id;
        }
        else if(type == 2) //教师登录
        {
            cout << "Please enter your employee ID:" << endl;
            cin >> id;
        }

        cout << "Please enter your username:" << endl;
        cin >> name;

        cout << "Please enter your password:" << endl;
        cin >> pwd;

        if(type == 1)
        {
            //学生登录验证
            int fId;
            string fName;
            string fPwd;
            while(ifs >> fId && ifs >> fName && ifs >> fPwd)
            {
                if(id == fId && name == fName && pwd == fPwd)
                {
                    cout << "Student verification login successful" << endl;
                    system("pause");
                    system("cls");
                    person = new Student(id, name, pwd);

                    //学生界面
                    StudentMenu(person);

                    return;
                }
            }
        }
        else if(type == 2)
        {
            //教师登录验证
            int fId;
            string fName;
            string fPwd;
            while(ifs >> fId && ifs >> fName && ifs >> fPwd)
            {
                if(id == fId && name == fName && pwd == fPwd)
                {
                    cout << "Teacher verification login successful" << endl;
                    system("pause");
                    system("cls");
                    person = new Teacher(id, name, pwd);

                    //教师界面
                    TeacherMenu(person);

                    return;
                }
            }
        }
        else
        {
            //管理员登录验证
            string fName;
            string fPwd;
            while(ifs >> fName && ifs >> fPwd)
            {
                if(name == fName && pwd == fPwd)
                {
                    cout << "Manager verification login successful" << endl;
                    system("pause");
                    system("cls");
                    person = new Manager(name, pwd);

                    //管理员界面
                    ManagerMenu(person);

                    return;
                }
            }
        }

        if(i != 0)
        {
            cout << "Your enter is error, please enter again(You have "<< i << "times accounts):" <<endl;
        }
        else
        {
            cout << "Failed to verify login, please try after 5 minutes!" << endl;

            time_t rawtime;
            time(&rawtime);

            struct tm* timeinfo = localtime(&rawtime);

            FILE* pfwrite;

            if(type == 1) //存入学生时间文件
            {
                pfwrite = fopen(TIME_STUDENT_FILE, "wb");
            }
            else if(type == 2) //存入教师时间文件
            {
                pfwrite = fopen(TIME_TEACHER_FILE, "wb");
            }
            else //存入管理员时间文件
            {
                pfwrite = fopen(TIME_ADMIN_FILE, "wb");
            }

            fwrite(timeinfo, sizeof(struct tm), 1, pfwrite);
            fclose(pfwrite);
            pfwrite = NULL;

            system("pause");
            system("cls");

            return;
        }
    }

    

}



int main()
{
    //system("chap 65001");
    int select = 0;
    //ComputerManager cm;
    while(true)
    {
        mainMenu();
        cout << "Please enter your select:";
        cin >> select;
        switch(select)
        {
        case 1: //学生身份
            LoginIn(STUDENT_FILE, 1);
            break;
        case 2: //教师身份
            LoginIn(TEACHER_FILE, 2);
            break;
        case 3: //管理员身份
            LoginIn(ADMIN_FILE, 3);
            break;
        case 0: //退出系统
            cout << "Welcome to use again" << endl;
            system("pause");
            exit(0);
            //break;
        default:
            cout << "Your enter is error, please enter again:" << endl;
            system("pause");
            system("cls");
        }
    }
    return 0;
}