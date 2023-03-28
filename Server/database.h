#ifndef _DATABASE_H_
#define _DATABASE_H_

#include "includes.h"
#include "core.h"
struct user_sq{
    int  echo_user;
    int  echo_pass;           //用于通信
    char username[64];
    char password[64];
};
/**
    打开<注册用户>数据库
*/
int Open_DataBase(char *pathname, sqlite3 ** db);
/**
    增加一个用户信息到<注册用户>数据库
*/
int Add_User(sqlite3 * db, char *username, char *password);

/**检查<注册用户>数据库中是否有此用户
    用户存在：  返回0
    用户不存在：返回-1
*/
int Check_UserExist(sqlite3 * db, char *username);
int callback_check_exist(void *arg, int argc, char *argv[], char *argn[]);
/**检查<用户名>和<密码>是否对应
    对应：  返回0
    不对应：返回-1
*/
int Check_UserPass(sqlite3 * db, char *username, char *password);
int callback_check_pass(void *arg, int argc, char *argv[], char *argn[]);
/**
    数据库查询函数：
    参数：数据库句柄、数据包
    查询完成把数据 写入数据包
    返回数据包；
*/
struct pack Inquire_Database(sqlite3 * db_word, char *word);
int callback_search_word(void *arg, int argc, char *argv[], char *argn[]);
#endif