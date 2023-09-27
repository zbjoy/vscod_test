#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void getTimeChar(char* nowtime, char** year, char** month, char** day, char** hour, char** minute, char** seconds)
{
    int start = 0;
    int pos = 0;

    while(nowtime[pos] != '\0' && nowtime[pos] != ' ')
    {
        pos++;
    }
    nowtime[pos] = '\0';
    *year = &nowtime[start];
    pos++;
    start = pos;

    while(nowtime[pos] != '\0' && nowtime[pos] != ' ')
    {
        pos++;
    }
    nowtime[pos] = '\0';
    *month = &nowtime[start];
    pos++;
    start = pos;

    while(nowtime[pos] != '\0' && nowtime[pos] != ' ')
    {
        pos++;
    }
    nowtime[pos] = '\0';
    *day = &nowtime[start];
    pos++;
    start = pos;

    while(nowtime[pos] != '\0' && nowtime[pos] != ':')
    {
        pos++;
    }
    nowtime[pos] = '\0';
    *hour = &nowtime[start];
    pos++;
    start = pos;

    while(nowtime[pos] != '\0' && nowtime[pos] != ':')
    {
        pos++;
    }
    nowtime[pos] = '\0';
    *minute = &nowtime[start];
    pos++;
    start = pos;

    while(nowtime[pos] != '\0' && nowtime[pos] != ' ')
    {
        pos++;
    }
    nowtime[pos] = '\0';
    *seconds = &nowtime[start];
    pos++;
    start = pos;
}

int main()
{
    char* passWord = "6642587";
    char* passWord_Entered = (char*)malloc(100 * sizeof(char));
    char* timeData;
    int i = 3;
    int error = 0;

    char* year = (char*)malloc(100 * sizeof(char));
    char* month = (char*)malloc(100 * sizeof(char));
    char* day = (char*)malloc(100 * sizeof(char));
    char* hourTime = (char*)malloc(100 * sizeof(char));

    FILE* pfread; //打开文件读出时间
    pfread = fopen("time.txt", "rb");

    int fileTrue = 0;
    int len = 0;
    if(NULL != pfread)
    {
        //fseek(pfread, 0, SEEK_END);
        //len = ftell(pfread);
        //fseek(pfread, 0, SEEK_SET);
        len = 1;
    }

    if(len > 0)
    {
        fileTrue = 1;
    }

    if(fileTrue)
    {
        fscanf(pfread, "%s%s%s%s", year, month, day, hourTime);
        //fscanf(pfread, "%s%s%s%s%s", lastyear, lastmonth, lastday, lasttime);
        fclose(pfread);

        //char* xhourTime = hourTime;

        int start = 0;
        int pos = 0;

        while(hourTime[pos] != '\0' && hourTime[pos] != ':')
        {
            pos++;
        }
        //hourTime[pos] = '\0';
        int hourPos = pos;
        char* hour = &hourTime[start];
        pos++;
        start = pos;


        while(hourTime[pos] != '\0' && hourTime[pos] != ':')
        {
            pos++;
        }
        //hourTime[pos] = '\0';
        int minutePos = pos;
        char* minute = &hourTime[start];
        pos++;
        start = pos;

        while(hourTime[pos] != '\0' && hourTime[pos] != ' ')
        {
            pos++;
        }
        hourTime[pos] = '\0';
        hourTime[hourPos] = '\0';
        hourTime[minutePos] = '\0';
        char* seconds = &hourTime[start];
        pos++;
        start = pos;

        char* nowYear = (char*)malloc(100 * sizeof(char));
        char* nowMonth = (char*)malloc(100 * sizeof(char));
        char* nowDay = (char*)malloc(100 * sizeof(char));
        char* nowHour = (char*)malloc(100 * sizeof(char));
        char* nowMinute = (char*)malloc(100 * sizeof(char));
        char* nowSeconds = (char*)malloc(100 * sizeof(char));

        time_t temprawtime;
        time(&temprawtime);
        struct tm* temptimeinfo = localtime(&temprawtime);
        char* tempnowtime = asctime(temptimeinfo);

        getTimeChar(tempnowtime, &nowYear, &nowMonth, &nowDay, &nowHour, &nowMinute, &nowSeconds);

        if(!strcmp(year, nowYear))
        {
            if(!strcmp(month, nowMonth))
            {
                if(!strcmp(day, nowDay))
                {
                    if(!strcmp(hour, nowHour))
                    {
                        if(strcmp(minute, nowMinute))
                        {
                            printf("minute::%s\n", minute);
                            printf("nowMinute::%s\n", nowMinute);
                            fclose(pfread);
                        }
                    }
                }
            }
        }

        

        // printf("You need a later time to try\n");
        // system("pause");
        // exit(0);

        

        
    }
    else
    {
        fclose(pfread);
    }



    //getTimeChar(timeData, &year, &month, &day, &hour, minute, seconds);



    for(i = 2; i >= 0; i--)//输入密码
    {
        printf("Please enter your password:");
        scanf("%s", passWord_Entered);
        if(!strcmp(passWord, passWord_Entered))
        {
            printf("Welcom to this sytem!!!\n");
            error = 0;
            break;
        }
        else
        {
            if(i != 0)
            {
                printf("Password is error, please enter again(You have %d times chance):", i);
                error = 1;
            }
        }
    }

    if(error == 1)//如果密码为错，则时间记入time.txt，为下次判断做依据
    {
        printf("I'm sorry that you can't enter the system after 5 minutes\n");
        time_t rawtime;
        time(&rawtime);
        struct tm* timeinfo = localtime(&rawtime);
        char* nowtime = asctime(timeinfo);

        FILE* pfwrite; //打开文件记入时间
        pfwrite = fopen("time.txt", "wb");

        fprintf(pfwrite, "%s", nowtime);

        fclose(pfwrite);
        pfwrite = NULL;

        system("pause");
        exit(0);
    }
    else
    {
        FILE* pfreadt; //打开文件删除时间
        pfreadt = fopen("time.txt", "w");
        fclose(pfreadt);
    }


    return 0;
}