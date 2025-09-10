#include "core.h"

/**
 * @details
 *  1. UI显示：收集数据
 *  2. 打包发送手机的数据
 *  3. 接收数据包并进行处理
 * 
 * @return 成功返回0，否则返回-1
 */
extern char username[32];

int Echo_core(int sockfd, int (*ui)(pack_t*), int type)
{
    int i, j;
    char * p;
    int nbytes;

    /** 创建 数据发送包*/
    pack_t pack;
    /** 创建 数据接收包*/
    pack_t retp;

    //------------------------------指定消息类型--------------------------------
    pack.type = type; 
    //LOGIN_APPL or RGTER_APPL or SEARC_APPL
    //------------------------------指定消息类型--------------------------------
    

    //------------------------------UI界面并收集数据----------------------------
    if (ui(&pack) == -1){
        fprintf(stderr, "login or register err\n");
        return -1;
    } 
    //------------------------------UI界面并收集数据----------------------------
    

    //-------------------------------检查收集数据-----------------------------------------
    if (pack.type == LOGIN_APPL || pack.type == RGTER_APPL){
        printf("\033[3Buser: %s\n", pack.username);
        printf("pass: %s\n", pack.password);
    }else{
        if (strcmp(pack.msg, "#quit") == 0){
            pack.type = USER_OFFLINE;
            strcpy(pack.username, username);
            send(sockfd, &pack, sizeof(pack), 0);

            printf("\033[6B\r");
            return 4;
        }        
    }
    //-------------------------------检查收集数据-----------------------------------------


    //-------------------------------把数据包发送给服务器---------------------------------
    if (send(sockfd, &pack, sizeof(pack), 0) == -1){
        perror("in Login_core function send");
        exit(-1);
    }
    /* 数据包发送成功提示消息 */
    //if (pack.type != SEARC_APPL)
    //    printf("send data pack success\n");
    //-------------------------------把数据包发送给服务器---------------------------------

        

    //-------------------------------接收服务器返回数据包---------------------------------
    nbytes = recv(sockfd, &retp, sizeof(retp), 0);

    //-------------------------------服务器返回数据包处理---------------------------------
    if (nbytes == -1) {
        perror("in Login_core function recv");
        return -1;
    } else if (nbytes == 0) {
        fprintf(stderr, "server quit\n");
        exit(-1);
    } else {
        if (retp.echo == ECHO_SUC) {
            switch (pack.type) {
                //---------------登录数据包---------------------------------------
                case LOGIN_APPL:
                    if (retp.type == LOGIN_ECHO){
                        printf("LOGIN SUCCESS! <Enter continue>\n");
                        strcpy(username, pack.username);
                        while (getchar() != '\n')
                            continue;
                        
                        system("clear");
                        return 0;
                    }else
                        return -1;
                    break;
                //---------------注册数据包----------------------------------------
                case RGTER_APPL:
                    if (retp.type == RGTER_ECHO){
                        printf("REGISTER SUCCESS! <Enter continue>\n");

                        while (getchar() != '\n')
                            continue;
                        
                        system("clear");
                        return 0;
                    }else
                        return -1;
                //---------------查询数据包----------------------------------------
                case SEARC_APPL:
                    if (retp.type == SEARC_ECHO){
                        
                        //-------打印Msg程序---------------------------------------
                        i = 0;
                        j = 0;
                        p = retp.msg;
                        while (*p != '\0')
                        {
                            putchar(*p);
                            p++;
                            i++;
                            if (i % 29 == 0 && j == 0){
                                i = 0;
                                j++;
                                printf("\033[1B\r\033[3C");
                            }else if(i % 34 == 0){
                                j++;
                                printf("\033[1B\r\033[3C");
                            }
                            else{
                                ;
                            }   
                        }
                        //-------打印Msg程序---------------------------------------

                        //-------换行提示程序--------------------------------------
                        i = 6-j;
                        while (i--)
                            printf("\033[1B\r");
                        printf("<continue>....");

                        while (getchar() != '\n')
                            continue;
                        system("clear");
                        //-------换行提示程序--------------------------------------                      
                        return 0;
                    }
                    break;
                default:
                    break;
            }
        //-----------------------ECHO_ERR失败包处理----------------------------------------
        }else{
            system("clear");
            /**如果不是退出指令：打印错误包消息*/
            if (strcmp(pack.msg, "#quit") != 0)
                fprintf(stderr, "\rerr msg: %s\n", retp.msg);
            
            return -1;
        }     
    }
    //-------------------------------服务器返回数据包处理---------------------------------
}

/**
 * 读取stdin函数
 */
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