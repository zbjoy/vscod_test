#include "student.h"

//默认构造函数
Student::Student()
{

}

//有参构造函数
Student::Student(int id, string name, string pwd)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_Pwd = pwd;
}

//菜单界面
void Student::operMenu()
{
    cout << "Welcom student" << this->m_Name << "log on!" << endl;
    cout << "\t\t-------------------------------------------------------" << endl;
    cout << "\t\t|                                                     |" << endl;
    cout << "\t\t|              1 . Apply for an appointment           |" << endl;
    cout << "\t\t|                                                     |" << endl;
    cout << "\t\t|              2 . View my appointments               |" << endl;
    cout << "\t\t|                                                     |" << endl;
    cout << "\t\t|              3 . View all sppointments              |" << endl;
    cout << "\t\t|                                                     |" << endl;
    cout << "\t\t|              4 . Cancel reservation                 |" << endl;
    cout << "\t\t|                                                     |" << endl;
    cout << "\t\t|              0 . Exit student menu                  |" << endl;
    cout << "\t\t|                                                     |" << endl;
    cout << "\t\t-------------------------------------------------------" << endl;
}

//申请预约
void Student::applyOrder()
{

}

//查看我的预约
void Student::showMyOrder()
{

}

//查看所有预约
void Student::showAllOrder()
{

}

//取消预约
void Student::cancelOrder()
{

}
