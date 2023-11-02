#include <stdio.h>

#include <winsock2.h>
#pragma comment(lib, "WS2_32.lib")

#define PRINTF(str) printf("[%s - %d]"#str"=%s", __func__, __LINE__, str);
// void PRINTF(const char* str)
// {
//     printf("[%s - %d]%s", __func__, __LINE__, str);

// }


void error_die(const char* str)
{
    perror(str);
    exit(1);
}

/*  
    实现网络的初始化
    返回值是套接字(服务器的套接字)
    参数： port   
*/
int startup(unsigned short* port)
{
    // 1. 网络通信的初始化(Linux不需要)
    WSADATA data;
    int ret = WSAStartup(MAKEWORD(1, 1), &data);
    if(ret)//如果返回值为0初始化成功
    {
        
        //return INVALID_SOCKET;

        error_die("WASStartup()");
    }

    int server_Socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(server_Socket == -1)
    {
        //exit(1);

        //打印错误数据
        error_die("socket failed");
    }

    //设置端口可复用(端口复用)
    int opt = 1;
    ret = setsockopt(server_Socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));
    if(ret == -1)
    {
        error_die("setsockopt");
    }

    //配置服务器网络地址号
    struct sockaddr_in server_Addr;
    memset(&server_Addr, 0, sizeof(server_Addr));
    server_Addr.sin_family = AF_INET;
    server_Addr.sin_port = htons(*port);
    server_Addr.sin_addr.s_addr = htonl(INADDR_ANY);//0;

    //绑定套接字
    ret = bind(server_Socket, (struct sockaddr*)&server_Addr, sizeof(server_Addr));
    if(ret < 0)
    {
        error_die("bind");
    }

    // 动态分配端口
    int nameLen = sizeof(server_Addr);
    if(*port == 0)
    {
        ret = getsockname(server_Socket, (struct sockaddr*)&server_Addr, &nameLen);
        if(ret < 0)
        {
            error_die("getsockname");
        }

        *port = server_Addr.sin_port;

    }

    //创建一个监听队列
    ret = listen(server_Socket, 5);
    if(ret < 0)
    {
        error_die("liten");
    }

    return server_Socket;
}

//从指定的客户端套接字sock， 读取一行数据， 保存到buff中
//返回实际读到的字节数
int get_Line(int sock, char* buff, int size)
{
    char c = 0;
    int i = 0;

    //  \r\n
    while(i < size - 1 && c != '\n')
    {
        int n = recv(sock, &c, 1, 0);

        if(n > 0)
        {
            if(c == '\r')
            {
                n = recv(sock, &c, 1, MSG_PEEK);
                if(n > 0 && c == '\n')
                {
                    recv(sock, &c, 1, 0);
                }
                else
                {
                    c = '\n';
                }
                
            }
            buff[i++] = c;
        }
        else
        {
            c = '\n';
            //break;
        }

    }

    buff[i] = 0; // '\0'
    return i;
}

void unimplement(int client)
{
    //向指定套接字， 发送一个提示还没有实现的错误页面
}

//处理用户请求的线程函数
DWORD WINAPI accept_Request(LPVOID arg)
{
    char buff[1024]; //1k

    int client = (SOCKET)arg; //客户端套接字

    //读取一行数据
    int numChars = get_Line(client, buff, sizeof(buff));
    PRINTF(buff);
    //printf("[%s - %d]%s", __func__, __LINE__, buff);
    //printf("read: %s\n", buff);

    char method[255];
    int j = 0;
    int i = 0;
    while(!isspace(buff[j]) && i < sizeof(method) - 1)
    {
        method[i++] = buff[j++];
    }

    method[i] = 0;

    PRINTF(method);

    //检查请求的方法， 本服务器是否支持
    if(strcmp(method, "GET") && strcmp(method, "POST"))
    {
        //向浏览器返回一个错误页面
        unimplement(client);

        return 0;
    }

    //解析资源文件路径
    //www.haha.com/nhao/test.html
    //GET /nhao/test.html HTTP/1.1\n
    char url[255]; //存放请求的资源的完整路径
    i = 0;
    //j = 0;
    while(isspace(buff[j]) && j < sizeof(buff))
    {
        j++;
    }

    while(!isspace(buff[j]) && i < sizeof(url) - 1 && j < sizeof(buff))
    {
        url[i++] = buff[j++];
    }

    url[i] = 0;
    PRINTF(url);


    return 0;
}

int main(void)
{
    unsigned short port = 80;
    int server_Socket = startup(&port);
    printf("httpd Server is starting, listening %d port...", port);

    struct sockaddr_in client_Addr;
    int client_Addr_Len = sizeof(client_Addr);

    while(1)
    {
        //阻塞式等待用户通过浏览器发起访问
        int client_Sock = accept(server_Socket, (struct sockaddr*)&client_Addr, &client_Addr_Len);
        if(client_Sock == -1)
        {
            error_die("accept");
        }


        DWORD threadId = 0;
        //创建一个新线程
        CreateThread(0, 0, accept_Request, (void*)client_Sock, 0, &threadId);
    }

    closesocket(server_Socket);

    return 0;
}