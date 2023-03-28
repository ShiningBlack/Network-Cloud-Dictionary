#ifndef _CORE_H_
#define _CORE_H_
#include "includes.h"
#include "online.h"
#include "database.h"



//extern int sockfd;
#define LEN 32
#define MSG 256

/**消息包结构体*/
typedef struct pack{
    int  echo;              /**成功失败*/
    int  type;              /**消息类型*/
    char username[LEN];     
    char password[LEN];
    char msg[MSG];          /**消息*/
}pack_t;

/**数据包类型*/
#define LOGIN_APPL   100 //登录申请消息
#define RGTER_APPL   101 //注册申请消息
#define SEARC_APPL   102 //查询单词发送

#define LOGIN_ECHO   200 //服务器回复的登录消息
#define RGTER_ECHO   201 //服务器回复的注册消息
#define SEARC_ECHO   202 //服务器回复的查询单词消息

/**服务器回复*/
#define ECHO_SUC     0
#define ECHO_ERR     1

/**登录消息宏*/
#define USER_NOEXIST  "User does not exist"  //此用户不存在   
#define USER_PASSERR  "Wrong user password"  //用户密码错误
#define USER_ONLINE   "This user is online"  //此用户已在线
#define USER_LOGSUC   "User login successful"//用户登录成功

/**注册消息宏*/
#define USER_EEXIST   "This user already exists" //此用户已存在
#define USER_REGERR   "User registration failed" //用户注册失败
#define USER_REGSUC   "User registration is successful" //用户注册成功

/**查询消息*/
#define USER_SEARCH   "search msg"

/**下线消息*/
#define USER_OFFLINE  404
/**服务器根据把不同的消息类型来处理消息*/

void errExit(char *str);
void errExit_Print(char *str);

char *s_gets(char buf[], int len);
int Send_Msg_Client(int fd, int echo, int type, char *msg);

int Handler_Msg(int fd, pack_t *recv_cli_pack,  online_t *OnlineList, sqlite3 * db, sqlite3 * db_word);
#endif