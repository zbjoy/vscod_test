#include "orderFile.h"

//构造函数
OrderFile::OrderFile()
{
    ifstream ifs;
    ifs.open(ORDER_FILE, ios::in);

    string date; //日期
    string interval; //时间段
    string stuId; //学生编号
    string stuName; //学生姓名
    string roomId; //机房编号
    string status; //预约状态

    this->m_Size = 0; //预约记录个数

    while(ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
    {
        /*
        //测试代码
        cout << date << endl;
        cout << interval << endl;
        cout << stuId << endl;
        cout << stuName << endl;
        cout << roomId << endl;
        cout << status << endl;
        */

        string key;
        string value;
        map<string, string> tempM;

        int pos = date.find(":");
        if(pos != -1)
        {
            key = date.substr(0, pos);
            value = date.substr(pos + 1, date.size() - pos);
            tempM.insert(make_pair(key, value));
        }

        pos = interval.find(":");
        if(pos != -1)
        {
            key = interval.substr(0, pos);
            value = interval.substr(pos + 1, interval.size() - pos);
            tempM.insert(make_pair(key, value));
        }

        pos = stuId.find(":");
        if(pos != -1)
        {
            key = stuId.substr(0, pos);
            value = stuId.substr(pos + 1, stuId.size() - pos);
            tempM.insert(make_pair(key, value));
        }

        pos = stuName.find(":");
        if(pos != -1)
        {
            key = stuName.substr(0, pos);
            value = stuName.substr(pos + 1, stuName.size() - pos);
            tempM.insert(make_pair(key, value));
        }

        pos = roomId.find(":");
        if(pos != -1)
        {
            key = roomId.substr(0, pos);
            value = roomId.substr(pos + 1, roomId.size() - pos);
            tempM.insert(make_pair(key, value));
        }

        pos = status.find(":");
        if(pos != -1)
        {
            key = status.substr(0, pos);
            value = status.substr(pos + 1, status.size() - pos);
            tempM.insert(make_pair(key, value));
        }


        this->m_orderData.insert(make_pair(this->m_Size, tempM));
        this->m_Size++;
    }

    ifs.close();

}

//更新预约记录
void OrderFile::updateOrder()
{
    if(this->m_Size == 0)
    {
        return;
    }

    ofstream ofs;
    ofs.open(ORDER_FILE, ios::out | ios::trunc);
    for(int i = 0; i < this->m_Size; i++)
    {
        ofs << "date:" << this->m_orderData[i]["date"] << " ";
        ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
        ofs << "stuId:" << this->m_orderData[i]["stuId"] << " ";
        ofs << "stuName:" << this->m_orderData[i]["stuName"] << " ";
        ofs << "roomId:" << this->m_orderData[i]["roomId"] << " ";
        ofs << "status:" << this->m_orderData[i]["status"] << endl;
    }

    ofs.close();
}