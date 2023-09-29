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

    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);

    ComputerRoom tempC;

    while(ifs >> tempC.m_ComId && ifs >> tempC.m_MaxNum)
    {
        this->vCom.push_back(tempC);
    }

    ifs.close();
}

//菜单界面
void Student::operMenu()
{
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
    cout << "The computer room is open from Monday to Friday" << endl;
    cout << "Please enter the time for applying:" << endl;
    cout << "1. Monday" << endl;
    cout << "2. Tuesday" << endl;
    cout << "3. Wednesday" << endl;
    cout << "4. Thursday" << endl;
    cout << "5. Friday" << endl;

    int date = 0; //日期
    int interval = 0; //时间段
    int room = 0; //机房编号

    while(true)
    {
        cout << "Please enter your select:";
        cin >> date;

        if(date >= 1 && date <= 5)
        {
            break;
        }
        else
        {
            cout << "Your enter is error, please enter again" << endl;
            system("pause");
            continue;
        }
    }

    cout << "Please enter the time period to make an appointment" << endl;
    cout << "1. Morning" << endl;
    cout << "2. Afternoon" << endl;

    while(true)
    {
        cout << "Please enter your select:";
        cin >> interval;
        
        if(interval == 1 || interval == 2)
        {
            break;
        }
        else
        {
            cout << "Your enter is error, please enter again" << endl;
            system("pause");
            continue;
        }

    }

    cout << "Please select a computer room" << endl;
    for(int i = 0; i < vCom.size(); i++)
    {
        cout << "The capacity of Machine Room " << vCom[i].m_ComId << " is:" << vCom[i].m_MaxNum << endl;
    }

    while(true)
    {
        cout << "Please select which computer you select(Please enter computer number:)";
        cin >> room;

        if(room >= 1 && room <= vCom.size())
        {
            break;
        }
        else
        {
            cout << "Your enter is error, please enter again" << endl;
            system("pause");
            continue;
        }
    }

    cout << "Appointment successful, under review!" << endl;

    ofstream ofs;
    ofs.open(ORDER_FILE, ios::app);

    ofs << "date:" << date << " ";
    ofs << "interval:" << interval << " ";
    ofs << "stuId:" << this->m_Id << " ";
    ofs << "stuName:" << this->m_Name << " ";
    ofs << "roomId:" << room << " ";
    ofs << "status:" << 1 << endl;

    ofs.close();

    system("pause");
    system("cls");

}

//查看我的预约
void Student::showMyOrder()
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
        if(atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id)
        {
            cout << "Appoint date:" << of.m_orderData[i]["date"];
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
    }

    system("pause");
    system("cls");

}

//查看所有预约
void Student::showAllOrder()
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
}

//取消预约
void Student::cancelOrder()
{
    OrderFile of;
    if(of.m_Size == 0)
    {
        cout << "No appointment record" << endl;
        system("pause");
        system("cls");
        return;
    }

    cout << "Records that are under review or have been successfully booked can be cancelled. Please enter the cancelled record" << endl;

    vector<int> v;
    int index = 1;
    for(int i = 0; i < of.m_Size; i++)
    {
        if(atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id)
        {
            if(of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
            {
                v.push_back(i);
                cout << index++ << ":  ";

                cout << "Appoint date:" << of.m_orderData[i]["date"];
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

                cout << status << endl;
            }
        }
    }

    int select = 0;

    while(true)
    {
        cout << "Please select witch appoint you want to cancel(0. Exit): ";
        cin >> select;
        if(select >= 0 && select <= v.size())
        {
            if(select == 0)
            {
                break;
            }
            else
            {
                of.m_orderData[v[select - 1]]["status"] = "0";
                of.updateOrder();
                cout << "Appointmnt cancelled" << endl;
                break;
            }

        }
        else
        {
            cout << "Your enter is error, please enter again!" << endl;
        }
    }

    system("pause");
    system("cls");


}
