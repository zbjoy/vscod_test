#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void getTimeChar(char* nowtime, char** nowyear, char** nowmonth, char** nowday, char** nowhour, char** nowminute, char** nowseconds)
{
    //printf("%s\n", nowtime);

    int start = 0;
    int pos = 0;
    while(nowtime[pos] != ' ' && nowtime[pos] != '\0')
    {
        pos++;
    }
    nowtime[pos] = '\0';
    char* year = &nowtime[start];
    start = pos + 1;
    pos++;
    
    while(nowtime[pos] != ' ' && nowtime[pos] != '\0')
    {
        pos++;
    }
    nowtime[pos] = '\0';
    char* month = &nowtime[start];
    start = pos + 1;
    pos++;

    while(nowtime[pos] != ' ' && nowtime[pos] != '\0')
    {
        pos++;
    }
    nowtime[pos] = '\0';
    char* day = &nowtime[start];
    start = pos + 1;
    pos++; 

    while(nowtime[pos] != ':' && nowtime[pos] != '\0')
    {
        pos++;
    }
    nowtime[pos] = '\0';
    char* hour = &nowtime[start];
    start = pos + 1;
    pos++;

    while(nowtime[pos] != ':' && nowtime[pos] != '\0')
    {
        pos++;
    }
    nowtime[pos] = '\0';
    char* minute = &nowtime[start];
    start = pos + 1;
    pos++;

    while(nowtime[pos] != ' ' && nowtime[pos] != '\0')
    {
        pos++;
    }
    nowtime[pos] = '\0';
    char* seconds = &nowtime[start];
    start = pos + 1;
    pos++;

    *nowyear = year;
    *nowmonth = month;
    *nowday = day;
    *nowhour = hour;
    *nowminute = minute;
    *nowseconds = seconds;
}

int main()
{
    char* year;
    char* month;
    char* day;
    char* hour;
    char* minute;
    char* seconds;
    //char* nowtime;

    

    // printf("%s\n", year);
    // printf("%s\n", month);
    // printf("%s\n", day);
    // printf("%s\n", hour);
    // printf("%s\n", minute);
    // printf("%s\n", seconds);

    time_t rawtime;
    time(&rawtime);
    struct tm* timeinfo = localtime(&rawtime);
    char* nowtime = asctime(timeinfo);

    getTimeChar(nowtime, &year, &month, &day, &hour, &minute, &seconds);

    FILE* pfwrite;
    pfwrite = fopen("time.txt", "wb");
    fprintf(pfwrite, "%s", nowtime);
    fclose(pfwrite);

    //char* lastTime = (char*)malloc(100 * sizeof(char));
    char* lastyear = (char*)malloc(100 * sizeof(char));
    char* lastmonth = (char*)malloc(100 * sizeof(char));
    char* lastday = (char*)malloc(100 * sizeof(char));
    char* lasttime = (char*)malloc(100 * sizeof(char));
    //char* lasthour = (char*)malloc(100 * sizeof(char));
    //char* lastminute = (char*)malloc(100 * sizeof(char));
    //char* lastseconds = (char*)malloc(100 * sizeof(char));
    FILE* pfread;
    pfread = fopen("time.txt", "rb");
    fscanf(pfread, "%s%s%s%s%s", lastyear, lastmonth, lastday, lasttime);
    fclose(pfread);


    if(strcmp(year, lastyear))
    {
        printf("buxinagdeng\n");
    }
    else{
        printf("xiangdeng\n");
    }
    // printf("%s\n", lastyear);
    // printf("%s\n", lastmonth);
    // printf("%s\n", lastday);
    // printf("%s\n", lasthour);
    // printf("%s\n", lastminute);
    // printf("%s\n", lastseconds);
    return 0;
}