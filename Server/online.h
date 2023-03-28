#ifndef _ONLINE_H_
#define _ONLINE_H_

#include "includes.h"

#define LEN  32
typedef struct node{
    int fd;
    char name[LEN];
    struct node * next;
}online_t;

/**
    初始化用户在线表
    成功返回：在线表头指针
    失败返回：NULL
*/
online_t * Init_OnlineList(void);
/**
    检查用户是否在用户在线表
    用户在线：  返回0
    用户不在线：返回-1
*/
int Check_UserOnline(online_t * list, char *username);
/**
    增加用户到在线用户表：
*/
int Add_OnlineList(online_t * list, char *username, int fd);

int Del_OnlineList(online_t * list, int fd);
#endif