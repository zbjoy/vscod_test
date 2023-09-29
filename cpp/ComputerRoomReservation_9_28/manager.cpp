#include "manager.h"


//构造函数
Manager::Manager()
{

}

//有参构造
Manager::Manager(string name, string pwd)
{
    this->m_Name = name;
    this->m_Pwd = pwd;

    //初始化容器
    this->initVector();
}

//选择菜单
void Manager::operMenu()
{
    cout << "Welcom admin" << this->m_Name << "log on!" << endl;
    cout << "\t\t-------------------------------------------------------" << endl;
    cout << "\t\t|                                                     |" << endl;
    cout << "\t\t|              1 . Add account                        |" << endl;
    cout << "\t\t|                                                     |" << endl;
    cout << "\t\t|              2 . View account                       |" << endl;
    cout << "\t\t|                                                     |" << endl;
    cout << "\t\t|              3 . View the computer room             |" << endl;
    cout << "\t\t|                                                     |" << endl;
    cout << "\t\t|              4 . Clear appointment                  |" << endl;
    cout << "\t\t|                                                     |" << endl;
    cout << "\t\t|              0 . Exit manager menu                  |" << endl;
    cout << "\t\t|                                                     |" << endl;
    cout << "\t\t-------------------------------------------------------" << endl;
}

//添加账号
void Manager::addPerson()
{
    string fileName;
    string tip;
    string errorTip;
    ofstream ofs;
    int select = 0;

    while(true)
    {
        cout << "Please enter the type of account to add:" << endl;
        cout << "1. Add student" << endl;
        cout << "2. Add teacher" << endl;
        cout << "0. exit " << endl;
        
        cin >> select;

        if(select == 1)
        {
            fileName = STUDENT_FILE;
            tip = "Please enter student ID:";
            errorTip = "Student ID is duplicate, please re-enter!";
            break;
        }
        else if(select == 2)
        {
            fileName = TEACHER_FILE;
            tip = "Please enetr employ nomber:";
            errorTip = "Employee ID is duplicate, please re-enter!";
            break;
        }
        else if(select == 0)
        {
            cout << "Exit successful!" << endl;
            system("pause");
            system("cls");
            return;
        }
        else
        {
            cout << "Your enter is error, please enter again!" << endl;
            system("pause");
            system("cls");
        }
    }

    ofs.open(fileName, ios::out | ios::app);

    int id;
    string name;
    string pwd;

    while(true)
    {
        cout << tip << endl;
        cin >> id;

        bool isRepeat = this->checkRepeat(id, select);
        if(isRepeat)
        {
            //cout << "The ID you entered already exists, pease re-enter:" << endl;
            cout << errorTip << endl;
            continue;
        }
        else
        {
            break;
        }
    }

    cout << "Please enter name:" << endl;
    cin >> name;

    cout << "Please enter password:" << endl;
    cin >> pwd;

    ofs << id << " " << name << " " << pwd << " " << endl;
    cout << "Add successfully!!" << endl;
    this->initVector();

    system("pause");
    system("cls");

    ofs.close();
}

//初始化容器
void Manager::initVector()
{
    vStu.clear();
    vTea.clear();

    //读取学生文件中的信息
    ifstream ifs;
    ifs.open(STUDENT_FILE, ios::in);
    if(!ifs.is_open())
    {
        cout << "initVector():: student.txt file read failure" << endl;
        ifs.close();
        return;
    }

    Student tempS;

    while(ifs >> tempS.m_Id && ifs >> tempS.m_Name && ifs >> tempS.m_Pwd)
    {
        vStu.push_back(tempS);
    }
    //cout << "Now student number: " << vStu.size() << endl;
    ifs.close();


    //读取老师文件信息
    ifs.open(TEACHER_FILE, ios::in);
    if(!ifs.is_open())
    {
        cout << "initVector():: teacher.txt file read failure" << endl;
        ifs.close();
        return;
    }

    Teacher tempT;

    while(ifs >> tempT.m_EmpId && ifs >> tempT.m_Name && ifs >> tempT.m_Pwd)
    {
        vTea.push_back(tempT);
    }
    //cout << "Now teacher number: " << vTea.size() << endl;
    ifs.close();

    //读取机房文件
    ifs.open(COMPUTER_FILE, ios::in);
    if(!ifs.is_open())
    {
        cout << "initVector():: computerRoom.txt file read failure" << endl;
        ifs.close();
        return;
    }

    ComputerRoom TempC;

    while(ifs >> TempC.m_ComId && ifs >> TempC.m_MaxNum)
    {
        vCom.push_back(TempC);
    }

    //cout << "Now computerroom counts is " << vCom.size() << endl;
    ifs.close();

}

//检测重复
bool Manager::checkRepeat(int id, int type)
{
    if(type == 1)
    {
        for(vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
        {
            if(id == it->m_Id)
            {
                return true;
            }
        }
    }
    else
    {
        for(vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
        {
            if(id == it->m_EmpId)
            {
                return true;
            }
        }
    }

    return false;
}

//查看账号
void Manager::showPerson()
{

    while(true)
    {
        cout << "Please select the content to view" << endl;
        cout << "1.View student content" << endl;
        cout << "2.View teacher content" << endl;
        cout << "3.View all content" << endl;
        cout << "0.Exit" << endl;

        int select = 0;
        cin >> select;

        if(select == 1)
        {
            cout << "-----------------------------------------------" << endl;

            cout << "Student :" << endl;
            for(vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
            {
                cout << "Student ID:" << it->m_Id << "  Name:" << it->m_Name << "  Password:" << it->m_Pwd << endl; 
            }

            cout << "-----------------------------------------------" << endl;
            break;
        }
        else if(select == 2)
        {
            cout << "-----------------------------------------------" << endl;

            cout << "Teacher:" << endl;
            for(vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
            {
                cout << "Emplyee ID:" << it->m_EmpId <<"  Name:" << it->m_Name << "  Password:" << it->m_Pwd << endl;
            }

            cout << "-----------------------------------------------" << endl;
            break;
        }
        else if (select == 3)
        {
            cout << "-----------------------------------------------" << endl;

            cout << "Student :" << endl;
            for(vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
            {
                cout << "Student ID:" << it->m_Id << "  Name:" << it->m_Name << "  Password:" << it->m_Pwd << endl; 
            }

            cout << "-----------------------------------------------" << endl;

            cout << "Teacher:" << endl;
            for(vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
            {
                cout << "Emplyee ID:" << it->m_EmpId <<" Name:" << it->m_Name << " Password:" << it->m_Pwd << endl;
            }

            cout << "-----------------------------------------------" << endl;
            break;
        }
        else if(select == 0)
        {
            cout << "Exit successful!" << endl;
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
    
    system("pause");
    system("cls");
}

//查看机房信息
void Manager::showComputer()
{
    //int i = vCom.size();
    cout << "The computerroom information is as follows" << endl;
    for(vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
    {
        cout << "Machine room number:" << it->m_ComId << "   Maximum capacity of the computer room:" << it->m_MaxNum << endl;
    }

    system("pause");
    system("cls");
}

//清空预约记录
void Manager::clearFile()
{
    ofstream ofs;
    ofs.open(ORDER_FILE, ios::trunc);
    ofs.close();

    cout << "Clear successful!" << endl;
    system("pause");
    system("cls");
}