#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAXSIZE 100

int main()
{
    time_t rawtime;
    time(&rawtime);
    struct tm* timeinfo = localtime(&rawtime);
    
    struct tm fileTime;

    char* passWord = "6642587";
    char* passWord_Enter = (char*)malloc(MAXSIZE * sizeof(char));

    FILE* pfread;
    pfread = fopen("time.txt", "rb");

    if(pfread == NULL)
    {
        //printf("The file is not find\n");
        fclose(pfread);
    }
    else
    {
        fread(&fileTime, sizeof(struct tm), 1, pfread);
        if(fileTime.tm_year == timeinfo->tm_year)
        {
            if(fileTime.tm_mon == timeinfo->tm_mon)
            {
                if(fileTime.tm_mday == timeinfo->tm_mday)
                {
                    if(fileTime.tm_hour == timeinfo->tm_hour)
                    {
                        int isEnough = timeinfo->tm_min - fileTime.tm_min;
                        if(isEnough >= 5)
                        {
                            fclose(pfread);
                            FILE* fwrite = fopen("time.txt", "w");
                            fclose(fwrite);
                            fwrite = NULL;
                        }
                        else
                        {
                            printf("Sorry,please enter after %d minutes\n", 5 - isEnough);
                            fclose(pfread);
                            system("pause");
                            exit(0);
                        }
                    }
                }
            }
        }
    }

    //printf("%d", timeinfo->tm_year);
    //printf("%d", timeinfo->tm_year);

    int i = 2;
    int error = 0;
    printf("Please enter your password:");
    for(; i >= 0; i--)
    {
        scanf("%s", passWord_Enter);
        if(!strcmp(passWord, passWord_Enter))
        {
            printf("Welcome to this system\n");
            error = 0;
            break;
        }
        else
        {
            if(i != 0)
            {
                printf("Your enter is error, please enter again(You have %d times):", i);
                error = 1;
            }
        }
    }
    
    if(error == 1)
    {
        printf("Sorry, you need to try again after 5 minutes\n");
        time_t rawtime1;
        time(&rawtime1);
        struct tm* nowTime;
        nowTime = localtime(&rawtime1);

        FILE* pfwrite = fopen("time.txt", "wb");
        fwrite(nowTime, sizeof(struct tm), 1, pfwrite);
        fclose(pfwrite);
        pfwrite = NULL;
        system("pause");
        exit(0);
    }
    // else
    // {
    //     FILE* fwrite = fopen("time.txt", "w");
    //     fclose(fwrite);
    //     fwrite = NULL;
    // }
    
    /*----------------------------------------------------------------------------------
     ----------------------------          系统内容          --------------------------
    -----------------------------------------------------------------------------------*/

    return 0;
}