#include "core.h"

/**
*   @处理数据包函数
*   @功能：处理用户的登录、注册、查询、退出
*   @参数：
*       fd：通信套接字
*       recv_cli_pack：接收消息的数据包
*       OnlineList：在线用户表
*       db：已注册用户的数据库
*       db_word：单词数据库
*/
int Handler_Msg(int fd, pack_t *recv_cli_pack, online_t *OnlineList, sqlite3 * db, sqlite3 * db_word)
{
    switch (recv_cli_pack->type)
    {
        case LOGIN_APPL:
            /**根据用户名<usernaem>检测数据库中是否有此用户*/
            if (Check_UserExist(db, recv_cli_pack->username) == -1){
                /**给客户端发送登陆失败消息*/
                Send_Msg_Client(fd, ECHO_ERR, LOGIN_ECHO, USER_NOEXIST);
                printf("用户不存在\n");
                return 0;
            }
            printf("用户存在\n");
            /**检查数据库中<username>和<password>是否对应*/
            if (Check_UserPass(db, recv_cli_pack->username, recv_cli_pack->password) == -1){
                Send_Msg_Client(fd, ECHO_ERR, LOGIN_ECHO, USER_PASSERR);
                printf("用户密码错误\n");
                return 0;                
            }
            printf("密码正确\n");
            /**检查在线用户表中此用户<username>是否在线*/
            if (Check_UserOnline(OnlineList, recv_cli_pack->username) == 0){
                Send_Msg_Client(fd, ECHO_ERR, LOGIN_ECHO, USER_ONLINE);
                printf("此用户在线\n");
                return 0;                 
            }
            /**登录成功，把用户增加到在线用户表*/
            if (Add_OnlineList(OnlineList, recv_cli_pack->username, fd) == -1)
                errExit("Add_OnlineList");
            printf("登陆成功\n");
            /**发送登录成功信息给客户端*/
            if (Send_Msg_Client(fd, ECHO_SUC, LOGIN_ECHO, USER_LOGSUC) == -1)
                return 0;
            break;
        case RGTER_APPL:
            printf("1\n");
            /**根据用户名<usernaem>检测数据库中是否有此用户: 已经存在*/
            if (Check_UserExist(db, recv_cli_pack->username) == 1){
                fprintf(stderr, "Check_UserExist\n");
                Send_Msg_Client(fd, ECHO_ERR, RGTER_ECHO, USER_EEXIST);
                fprintf(stderr, "Send Check_UserExist Success\n");
                return 0;
            }
            printf("2\n");
            /**把用户数据添加到到用户注册数据库*/
            if (Add_User(db, recv_cli_pack->username, recv_cli_pack->password) == -1){
                Send_Msg_Client(fd, ECHO_ERR, RGTER_ECHO, USER_REGERR);
                return 0;
            }
            printf("3\n");
            /**发送用户注册成功消息给客户端*/
            if (Send_Msg_Client(fd, ECHO_SUC, RGTER_ECHO, USER_REGSUC) == -1)
                return 0;
            printf("4\n");
            break;
        case SEARC_APPL:
            struct pack pack_search;
            /**把数据包发送给数据库查询函数：写入数据*/
            pack_search = Inquire_Database(db_word, recv_cli_pack->msg);
            /**发送查询成功消息给客户端*/
            if (Send_Msg_Client(fd, pack_search.echo, pack_search.type, pack_search.msg) == -1)
                return 0;
            break;
        case USER_OFFLINE:
            /**用户下线，删除在线用户*/
            if (Del_OnlineList(OnlineList, fd) == -1)
                errExit("Del_OnlineList");
            printf("%s offline.\n", recv_cli_pack->username);
            break;
        default:
            break;
    }
    /**处理完数据包清空*/
    memset(recv_cli_pack, 0, sizeof(*recv_cli_pack));
    return 0;
}

/**
*   @作者：ShiningBlack
*   @功能：发送一个消息包给客户端
*   @返回值：
*       成功：0 
*       失败：-1
*   @参数：
*       fd：通信套接字描述符
*       echo：成功消息 or 失败消息
*       type：服务器消息类型
*       msg：消息内容
*/
int Send_Msg_Client(int fd, int echo, int type, char *msg)
{
    pack_t pack;

    pack.echo = echo;
    pack.type = type;

    strcpy(pack.msg, msg);

    if (send(fd, &pack, sizeof(pack), 0) == -1)
        return -1;
    else
        return 0;
}
/**读取stdin函数*/
char *s_gets(char buf[], int len)
{
    char *find;
    char *ret_val;

    ret_val = fgets(buf, len, stdin);
    if (ret_val){
        find = strchr(buf, '\n');
        if (find)
            *find = '\0';
        else
            while (getchar() != '\n')
                continue;
    }
    return ret_val;
}

/**错误处理函数*/
void errExit(char *str)
{
    perror(str);
    exit(-1);
}
void errExit_Print(char *str)
{
    fprintf(stderr, "%s\n", str);
    exit(-1);
}