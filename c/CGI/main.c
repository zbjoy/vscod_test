#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
//#include <getopt.h>
//#include <stdint-gcc.h>
//#include <wchar.h>
//#include <mmsystem.h>
//#include <cstring>
//#pragma comment(lib, "Winmm.lib")

char *gets_s1(char *str, int num)
{
    if (fgets(str,num, stdin) != 0)
    {
        size_t len = strlen(str);

        if (len > 0 && str[len-1] == 'n')

            str[len-1] = '\0';
        return str;
    }
    return 0;
}



int main()
{
    //创建一个管道
    HANDLE outPut[2];//句柄(管道的两端的)
    //管道的属性
    SECURITY_ATTRIBUTES la;
    la.nLength = sizeof(la);
    la.bInheritHandle = TRUE;
    la.lpSecurityDescriptor = 0; //0表示设置为默认值
    int ret = CreatePipe(&outPut[0], &outPut[1], &la, 0);
    if(ret == FALSE)
    {
        MessageBox(0, "create cgi pipe error!", 0, 0);
        return 1;
    }

    //创建子进程
    char cmd[] = "ping www.baidu.com";
    //子进程的启动属性
    STARTUPINFO si = { 0 };
    si.cb = sizeof(si);
    si.hStdOutput = outPut[1];
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    PROCESS_INFORMATION pi = { 0 };
    ret = CreateProcess(NULL, cmd, 0, 0, TRUE, 0, 0, 0, &si, &pi);
    if(ret == FALSE)
    {
        printf("CreateProcess is error\n");
        return 1;
    }

    char buff[1024];
    DWORD size;
    while(1)
    {
        //printf("Please enter : ");
        //gets_s(buff, sizeof(buff));
        //gets_s1(buff, sizeof(buff));
        //scanf("%s", buff);
        // int num = sizeof(buff);
        // while(num--)
        // {
        //     gets_s(buff, num);
        // }
        //gets(buff);

        //gets(buff);

        //WriteFile(outPut[1], buff, strlen(buff) + 1, &size, NULL);
        //printf("have writen %d byte\n", size);

        ReadFile(outPut[0], buff, sizeof(buff), &size, NULL);
        buff[size] = '\0';
        printf("have read %d byte: [%s]\n", size, buff);
    }
    return 0;
}