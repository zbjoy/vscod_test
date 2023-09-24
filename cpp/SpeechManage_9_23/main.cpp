#include <iostream>
#include <time.h>

using namespace std;

#include "SpeechManager.h"

int main()
{
    srand((unsigned int)time(NULL));
    int select = 0;
    SpeechManager sm;
    while(true)
    {
        sm.menu();
        cout << "please enter the number you want to select:" ;
        cin >> select;
        switch(select)
        {
        case 1:
            sm.startSpeech();
            break;
        case 2:
            sm.showRecord();
            break;
        case 3:
            sm.deleteRecord();
            break;
        case 0:
            sm.exit_SpeechManager();
            break;
        }
    }
    return 0;
}