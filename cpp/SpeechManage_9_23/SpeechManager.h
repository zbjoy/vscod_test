#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
#include <numeric>
#include <fstream>

using namespace std;

#include "Speaker.h"

class SpeechManager
{
public:

    SpeechManager();

    void InitTemplate();

    void InitSpeaker();

    void menu();

    void SpeechDraw();

    void SpeechContest();

    void ShowScore();

    void saveSpeech();

    void loadSpeech();

    void showRecord();

    void startSpeech();

    void deleteRecord();

    void exit_SpeechManager();
   
    static int m_Index;

private:

    //Speaker m_Speaker[12];

    vector<int> v1;

    vector<int> v2;

    vector<int> vVictor;

    map<int, Speaker> m_Speaker;

    map<int, vector<string>> m_Record;

    bool fileIsEmpty;

};

//int SpeechManager::m_Index = 0;