#include "includes.h"
#include "core.h"
#include "sock.h"
#include "online.h"
#include "database.h"

#define MAX_LISTEN 10 /** 服务器最大监听客户端数量 */
#define MAX_EVENTS 10 /** Epoll最大可检测事件 */

int main(void)
{
    /*#######################################打开数据库################################################*/
    /* 打开存放用户注册信息的数据库文件 */
    sqlite3 * db;                   
    if (Open_DataBase("./userlist.db", &db) != 0)
        errExit_Print("Open_DataBase.userlist.db");
    
    /* 打开存放单词数据的数据库 */
    sqlite3 * db_word;                   
    if (Open_DataBase("./word.db", &db_word) != 0)
        errExit_Print("Open_DataBase.word.db");
    /*################################################################################################*/

    /*--------------------------------------在线用户表-------------------------------------------------*/
    /* 创建用户在线表并初始化 */
    online_t * OnlineList;          
    OnlineList = Init_OnlineList(); 
    /*------------------------------------------------------------------------------------------------*/

    /*######################################变量声明###################################################*/
    /**消息表*/
    int nbytes;             //recv返回值
    size_t pack_size;       //消息包的大小
    pack_t recv_cli_pack;   //接收自Client的消息包
    memset(&recv_cli_pack, 0, sizeof(recv_cli_pack));

    /**通信表*/
    int sockfd;
    int accefd;
    struct sockaddr_in cli_addr;

    /**epoll表*/
    int epfd;               //epoll实例句柄 
    int ready;              //epoll_wait返回值：就绪状态的文件描述符数量
    int numOpenfds;         //epoll实例中监听的文件描述符数量
    struct epoll_event evlist[MAX_EVENTS]; //epoll_wait返回的文件描述符表
    /*################################################################################################*/

    /*-------------------------------------绑定服务器--------------------------------------------------*/
    //创建socket
    if (CreateSock(&sockfd) == -1)
        errExit("CreateSock");
    //绑定sockfd
    if (BindSock(sockfd, "127.0.0.1", 6698) == -1)
        errExit("BindSock");
    //监听sock
    if (ListenSock(sockfd, MAX_LISTEN) == -1)
        errExit("ListenSock");
    /*-----------------------------------------------------------------------------------------------*/

    /*#####################################创建epoll实例##############################################*/
    //创建epoll实例
    if (CreateEpoll(&epfd) == -1)
        errExit("CreateEpoll");
    //添加socket到epoll关注列表：关注项：EPOLLIN
    if (AddEpoll(epfd, sockfd) == -1)
        errExit("AddEpoll");
    /*###############################################################################################*/
    
    /** 准备工作 */
    numOpenfds = 1;
    pack_size = sizeof(pack_t);     /** 消息包的大小 */

    /*#######################################核心代码区#############################################*/
    /**epoll开始关注*/
    while (numOpenfds)
    {
        ready = epoll_wait(epfd, evlist, MAX_EVENTS, -1);
        if (ready == -1){
            if (errno == EINTR) /**被信号中断就重启epoll_wait*/
                continue;
            else
                errExit("epoll_wait");
        }
        printf("epoll_wait触发: ready = %d\n", ready);


        for (int i = 0; i < ready; i++)
        {
            if (evlist[i].events & EPOLLIN)
            {
                if (evlist[i].data.fd == sockfd){
                    /**sockfd接收客户端的连接*/
                    if (AcceptSock(sockfd, &accefd, &cli_addr) == -1)
                        errExit("AcceptSock");
                    /**打印连接的客户端的信息*/
                    printf("Client_IP: %s\n" "Client_Port: %d\n", 
                        inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
                    /**把客户端通信socket添加到epoll实例*/
                    if (AddEpoll(epfd, accefd) == -1)
                        errExit("AddEpoll");
                    else
                        numOpenfds++;
                }
                else{
                    nbytes = recv(evlist[i].data.fd, &recv_cli_pack, pack_size, 0);
                    if (nbytes == -1){
                        if (errno == 104) /**未知错误：104*/
                            continue;
                        else
                            errExit("recv");
                    }
                    else if (nbytes == 0){
                        printf("epoll 关闭客户端文件描述符 。\n");
                        /**客户端退出关闭文件描述符并在epoll关注列表删除*/
                        if (DelEpoll(epfd, evlist[i].data.fd) == -1)
                            errExit("DelEpoll");
                        printf("epoll 关闭客户端文件描述符 。\n");
                        
                        numOpenfds--;
                    }
                    else{
                        /**读取客户端消息包成功，处理消息*/
                        if (Handler_Msg(evlist[i].data.fd, &recv_cli_pack, OnlineList, db, db_word) == -1)
                            errExit("Handler_Msg");
                    }
                }
            }
        }
    }
    /*#################################################################################################*/
    return 0;
}