#ifndef PROTOCOL_H_
#define PROTOCOL_H_

//extern int sockfd;
#define LEN 32
#define MSG 256

/* 服务器回复 */
#define ECHO_SUC     0
#define ECHO_ERR     1

/* 数据包类型 */
#define LOGIN_APPL   100   // 登录申请消息
#define RGTER_APPL   101   // 注册申请消息
#define SEARC_APPL   102   // 查询单词发送

#define LOGIN_ECHO   200   // 服务器回复的登录消息
#define RGTER_ECHO   201   // 服务器回复的注册消息
#define SEARC_ECHO   202   // 服务器回复的查询单词消息

/*下线消息 */
#define USER_OFFLINE  404

/**
 * @brief Server-Client通信消息结构
 */
typedef struct pack {
    int  echo;              /* 成功失败 */
    int  type;              /* 消息类型 */
    char username[LEN];     
    char password[LEN];
    char msg[MSG];          /* 消息 */
} pack_t;

char *s_gets(char buf[], int len);

#endif 