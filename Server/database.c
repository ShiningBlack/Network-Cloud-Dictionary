#include "database.h"

/**
    创建一个数据库存放用户注册的数据

    1.创建数据库
*/

/**打开数据库
   成功: 返回0
   失败: 返回-1
   并且自己打印错误
*/
int Open_DataBase(char *pathname, sqlite3 ** db)
{
    if (sqlite3_open(pathname, db) != 0){
        fprintf(stderr, "sqlite3_open: %s\n", sqlite3_errmsg(*db));
        return -1;
    }
    return 0;
}
/**
        把用户数据插入到用户注册数据库
*/
int Add_User(sqlite3 * db, char *username, char *password)
{
        char * errmsg;
        char buf[64];
        sprintf(buf, "insert into user(username, password) values(\"%s\", \"%s\");", username, password);

        printf("buf: %s\n", buf);
        printf("用户注册中......\n");
        if (sqlite3_exec(db, buf, NULL, NULL, &errmsg) != 0){
                fprintf(stderr, "sqlite3_exec: %s\n", errmsg);
                return -1;
        }
        printf("用户注册成功！！！！\n");
        return 0;
}
/**检查<注册用户>数据库中是否有此用户
    用户存在：  返回1
    用户不存在：返回-1
*/
int Check_UserExist(sqlite3 * db, char *username)
{
        char * errmsg;

        struct user_sq user;
        /**默认用户不存在*/
        user.echo_user = -1;
        user.echo_pass = -1;
        strcpy(user.username, username);

        if (sqlite3_exec(db, "select * from user", callback_check_exist, &user, &errmsg) != 0){
                fprintf(stderr, "sqlite3_exec: %s\n", errmsg);
                return -1;
        }
        printf("user.echo_user: %d, username: %s\n", user.echo_user, user.username);
        return user.echo_user;
}


//int flags = 0;
/**
        检查用户名是否注册的回调函数
*/
int callback_check_exist(void *arg, int argc, char *argv[], char *argn[])
{
        int i;

        
        for (i = 0; i < argc; i++){
                if (strcmp(((struct user_sq*)arg)->username, argv[0]) == 0){
                        ((struct user_sq*)arg)->echo_user = 1;
                        return 0;
                }
        }
        return 0;
}

/**检查<用户名>和<密码>是否对应
    对应：  返回0
    不对应：返回-1
*/
int Check_UserPass(sqlite3 * db, char *username, char *password)
{
        char * errmsg;
        
        struct user_sq user;
        user.echo_user = -1;
        user.echo_pass = -1;
        strcpy(user.username, username);
        strcpy(user.password, password);

        if (sqlite3_exec(db, "select * from user", callback_check_pass, &user, &errmsg) != 0){
                fprintf(stderr, "sqlite3_exec: %s\n", errmsg);
                return 0;
        }
        return user.echo_pass;
}
/**检查用户名和密码是否对应的回调函数*/
int callback_check_pass(void *arg, int argc, char *argv[], char *argn[])
{
        int i;

        printf("回调函数：username: %s password: %s\n", argv[0], argv[1]);
        for (i = 0; i < argc; i++){
                if (strcmp(((struct user_sq*)arg)->username, argv[0]) == 0){
                        printf("check pass: username: %s\n", argv[0]);
                        ((struct user_sq*)arg)->echo_user = 0;
                        if (strcmp(((struct user_sq*)arg)->password, argv[1]) == 0){
                                printf("check pass: passname: %s\n", argv[1]);
                                ((struct user_sq*)arg)->echo_pass = 0;
                                return 0;
                        }
                }
        }
        return 0;
}

/**
    数据库查询函数：
    参数：数据库句柄、数据包
    查询完成把数据 写入数据包
    返回数据包；
*/
pack_t Inquire_Database(sqlite3 * db_word, char *word)
{
        pack_t pack;
        char * errmsg;
        char buf[64] = {0};

        sprintf(buf, "select * from word where word='%s';", word);
        if (sqlite3_exec(db_word, buf, callback_search_word, &pack, &errmsg) != 0){
                fprintf(stderr, "sqlite3_exec: %s\n", errmsg);
        }

        return pack;
}

int callback_search_word(void *arg, int argc, char *argv[], char *argn[])
{
        memset(((pack_t*)arg)->msg, 0, MSG);

        strcpy(((pack_t*)arg)->msg, argv[1]);
        ((pack_t*)arg)->echo = ECHO_SUC;
        ((pack_t*)arg)->type = SEARC_ECHO;

        return 0;
}


