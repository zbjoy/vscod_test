#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    time_t rawtime;
    time(&rawtime);
    //printf("%s\n", rawtime);
    struct tm* timeinfo = localtime(&rawtime);
    printf("%s\n", asctime(timeinfo));

    time_t start0;
    time_t end0;
    time(&start0);
    //Sleep(5000);
    time(&end0);
    printf("%f seconds\n", difftime(end0, start0));

    clock_t start_t1;
    clock_t end_t1;
    start_t1 = clock();
    //Sleep(5000);
    end_t1 = clock();
    printf("%f seconds\n", (double)(end_t1 - start_t1) / CLOCKS_PER_SEC);

    char* nowTime = asctime(timeinfo);
    printf("%s\n", nowTime);

    char* tempTime = nowTime;
    char* nowMonth; 
    int start = 0;
    int pos = 0;
    while(tempTime[pos] != ' ')
    {
        pos++;
    }
    tempTime[pos] = '\0';

    tempTime = &tempTime[pos+1];
    printf("%s\n", tempTime);
    printf("%s\n",nowTime); 

    return 0;
}