#include "SpeechManager.h"

int SpeechManager::m_Index = 0;

SpeechManager::SpeechManager()
{
    InitTemplate();

    InitSpeaker();
}

void SpeechManager::InitTemplate()
{
    v1.clear();
    v2.clear();
    vVictor.clear();
    m_Speaker.clear();
}

void SpeechManager::InitSpeaker()
{
    m_Index = 0;
    string nameSeed = "ABCDEfGHIjKL";
    string name;
    int tempNum;
    Speaker tempSpeaker;
    for(int i = 0; i < 12; i++)
    {
        name = "speaker_";
        tempNum = 1001;
        name += nameSeed[i];
        //m_Speaker[i].m_Name = name;
        //m_Speaker[i].m_Score[m_Index] = 0.0f;
        //m_Speaker[i].m_Score[0] = 0.0f;
        //cout << m_Speaker[i].m_Name << endl;
        tempNum += i;
        tempSpeaker.m_Name = name;
        tempSpeaker.m_Score[m_Index] = 0.0f;
        v1.push_back(tempNum);
        m_Speaker.insert(make_pair(tempNum, tempSpeaker));
    }
}

void SpeechManager::menu()
{
    cout << "******************************************************" << endl;
    cout << "********  Welcome to the Speech Competition   ********" << endl;
    cout << "********     1.Start speech competition       ********" << endl;
    cout << "********     2.View past records              ********" << endl;
    cout << "********     3.Clean competition record       ********" << endl;
    cout << "********     0.Exit the competition program   ********" << endl;
    cout << "******************************************************" << endl;
}

void SpeechManager::SpeechDraw()
{
    vector<int> v;
    v.clear();

    int temp = 0;

    if(m_Index == 0)
    {
        v = v1;
    }
    else
    {
        v = v2;
    }

    random_shuffle(v.begin(),v.end());  //random_shuffle在c++14以后已经被弃用  shuffle怎么用？？？
    //shuffle(v.begin(),v.end(),vector<int>);
    //shuffle(v.begin(),v.end(),rand());

    cout << "-------------------The " << m_Index + 1<< " draw start---------------------"<< endl << endl;
    cout << "The first order of drawing lots is:" << endl;
    for(vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        if(temp++ == 6)
        {
            cout << endl << endl;
            cout << "The second order of drawing lots is:";
            cout << endl;
        }
        cout << *it << " ";
    }
    cout << endl;

    cout << "End of the " << m_Index + 1 << " round of drawing lots" << endl <<endl;
    cout << "--------------------------------------------------------" << endl << endl;

    if(m_Index == 0)
    {
        v1 = v;
    }
    else
    {
        v2 = v;
    }

    system("pause");
}

void SpeechManager::SpeechContest()
{
    cout << "-------------------The " << m_Index + 1<< " contest officially start---------------------"<< endl << endl;

    vector<int> v;
    multimap<float, int, greater<float>> groupScore; 

    if(m_Index == 0)
    {
        v = v1;
    }
    else
    {
        v = v2;
    }

    deque<float> d;
    float tempScore;
    int num = 0;

    for(vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        num++;
        for(int i = 0; i < 10; i++)
        {
            tempScore = (rand()%401 + 600) / 10.0f;
            d.push_back(tempScore);
        }

        sort(d.begin(), d.end(), greater<float>());
        d.pop_back();
        d.pop_front();

        float sum = accumulate(d.begin(), d.end(), 0.0f);
        float avg = sum / (float)d.size();
        d.clear();

        m_Speaker[*it].m_Score[m_Index] = avg;
        groupScore.insert(make_pair(avg, *it));

        if(num % 6 == 0)
        {
            cout << "The " << m_Index + 1 << " group of ranking" << endl;
            //for(multimap<float, int, greater<float>()>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
            for(multimap<float, int, greater<float>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
            {
                cout << "number:" << it->second 
                    << " name:" << m_Speaker[it->second].m_Name 
                    << " score:" << m_Speaker[it->second].m_Score[m_Index] << endl;
            }

            int count = 0;
            //for(multimap<float, int, greater<float>()>::iterator it = groupScore.begin(); it != groupScore.end() && count++ < 3; it++)
            for(multimap<float, int, greater<float>>::iterator it = groupScore.begin(); it != groupScore.end() && count++ < 3; it++)
            {
                if(m_Index == 0)
                {
                    v2.push_back(it->second);
                }
                else
                {
                    vVictor.push_back(it->second);
                }
            }
            groupScore.clear();
            cout << endl;
        }

    }

    cout << "---------------------The " << m_Index + 1 << " contest end-----------------------" << endl;
    system("pause");
    
}

void SpeechManager::ShowScore()
{
    cout << "The information of the " << m_Index + 1 << " round promotion contestants is as follows" << endl;

    vector<int> v;
    v.clear();
    
    if(m_Index == 0)
    {
        v = v2;
    }
    else
    {
        v = vVictor;
    }

    for(vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << "number:" << *it << " name:" << m_Speaker[*it].m_Name << " score:" << m_Speaker[*it].m_Score[m_Index] << endl;
    }

    cout << endl;

    system("pause");
}

void SpeechManager::startSpeech()
{
    SpeechDraw();

    SpeechContest();

    ShowScore();

    m_Index++;

    SpeechDraw();

    SpeechContest();

    ShowScore();


    cout << "This competition is over !!!" << endl;
    system("pause");

    InitTemplate();

    InitSpeaker();

}

void SpeechManager::exit_SpeechManager()
{
    cout << "Goodbye!See you later" << endl;
    system("pause");
    exit(0);
}