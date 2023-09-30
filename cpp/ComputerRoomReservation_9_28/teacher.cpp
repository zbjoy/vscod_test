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
    OrderFile of;
    if(of.m_Size == 0)
    {
        cout << "No appointment record" << endl;
        system("pause"); //暂停
        system("cls");
        return;
    }

    for(int i = 0; i < of.m_Size; i++)
    {
        cout << "Student name:" << of.m_orderData[i]["stuName"];
        cout << "  Student ID:" << of.m_orderData[i]["stuId"];
        cout << "  Appoint date:" << of.m_orderData[i]["date"];
        cout << "  Interval:" << (of.m_orderData[i]["interval"] == "1" ? "Morning" : "Afternoon");
        cout << "  Computer ID:" << of.m_orderData[i]["roomId"];
        string status = "   Status:";

        // 1、审核中  2、已预约  -1、预约失败  0、取消预约
        if(of.m_orderData[i]["status"] == "1")
        {
            status += "In review";
        }
        else if(of.m_orderData[i]["status"] == "2")
        {
            status += "Reserved";
        }
        else if(of.m_orderData[i]["status"] == "0")
        {
            status += "Cancel reservation";
        }
        else if(of.m_orderData[i]["status"] == "-1")
        {
            status += "Appointment failed";
        }

        cout << status << endl;
    }

    system("pause");
    system("cls");
}

//审核预约
void Teacher::vaildOrder()
{
    OrderFile of;
    if(of.m_Size == 0)
    {
        cout << "No appointment record" << endl;
        system("pause"); //暂停
        system("cls");
        return;
    }

    int index = 1;
    vector<int> v;
    for(int i = 0; i < of.m_Size; i++)
    {
        if(of.m_orderData[i]["status"] == "1")
        {
            cout << index++ << ":   ";
            cout << "Student name:" << of.m_orderData[i]["stuName"];
            cout << "  Student ID:" << of.m_orderData[i]["stuId"];
            cout << "  Appoint date:" << of.m_orderData[i]["date"];
            cout << "  Interval:" << (of.m_orderData[i]["interval"] == "1" ? "Morning" : "Afternoon");
            cout << "  Computer ID:" << of.m_orderData[i]["roomId"];
            cout << "  Status:" << "In review" << endl;
            v.push_back(i);
        }
    }



    while(true)
    {
        cout << "Please select witch you want to review(0. Exit):" << endl;

        int select = 0;
        cin >> select;
        if(select >= 1 && select <= v.size())
        {
            cout << "Student name:" << of.m_orderData[v[select - 1]]["stuName"];
            cout << "  Student ID:" << of.m_orderData[v[select - 1]]["stuId"];
            cout << "  Appoint date:" << of.m_orderData[v[select - 1]]["date"];
            cout << "  Interval:" << (of.m_orderData[v[select - 1]]["interval"] == "1" ? "Morning" : "Afternoon");
            cout << "  Computer ID:" << of.m_orderData[v[select - 1]]["roomId"];
            cout << "  Status:" << "In review" << endl;

            while(true)
            {
                cout << "Please enter your select: " << endl;
                cout << "1. Reserved" << endl;
                cout << "2. Appointment failed" << endl;
                cout << "0. Exit" << endl;

                int tempSelect = 0;
                cin >> tempSelect;
                if(tempSelect == 1)
                {
                    of.m_orderData[v[select - 1]]["status"] = "2";
                }
                else if(tempSelect == 2)
                {
                    of.m_orderData[v[select - 1]]["status"] = "-1";
                }
                else if(tempSelect == 0)
                {
                    cout << "Exit success!" << endl;
                    system("pause");
                    system("cls");
                    return;
                }
                else
                {
                    cout << "Your enter is error, please enter again!" << endl;
                    system("pause");
                    continue;  
                }

                of.updateOrder();
                cout << "View successful!!!" << endl;
                system("pause");
                system("cls");
                return;
            }

        }
        else if(select == 0)
        {
            cout << "Exit success!" << endl;
            system("pause");
            system("cls");
            return;
        }
        else
        {
            cout << "Your enter is error, please enter again!" << endl;
            system("pause"); 
        }
    }
}