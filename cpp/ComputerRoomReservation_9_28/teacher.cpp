#include "teacher.h"

//构造函数
Teacher::Teacher()
{

}

//有参构造
Teacher::Teacher(int empId, string name, string pwd)
{
    this->m_EmpId = empId;
    this->m_Name = name;
    this->m_Pwd = pwd;
}

//菜单界面
void Teacher::operMenu()
{
    cout << "\t\t-------------------------------------------------------" << endl;
    cout << "\t\t|                                                     |" << endl;
    cout << "\t\t|              1 . View all appointments              |" << endl;
    cout << "\t\t|                                                     |" << endl;
    cout << "\t\t|              2 . Review appointment                 |" << endl;
    cout << "\t\t|                                                     |" << endl;
    cout << "\t\t|              0 . Exit teacher menu                  |" << endl;
    cout << "\t\t|                                                     |" << endl;
    cout << "\t\t-------------------------------------------------------" << endl;
}

//查看所有预约
void Teacher::showAllOrder()
{
    
}

//审核预约
void Teacher::vaildOrder()
{

}