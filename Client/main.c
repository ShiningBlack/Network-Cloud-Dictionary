#include "includes.h"
#include "ui.h"
#include "core.h"

char username[32] = {0};

int main(int argc, const char *argv[])
{
    int pos;
    char ch;
    int sockfd;
    struct sockaddr_in ser_addr;

    //------------------------------------连接服务器----------------------------------
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(-1);
    }
    printf("socket ok\n");

    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(6698);
    ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(sockfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr)) == -1){
        perror("in main function connect");
        exit(-1);
    }
    printf("Connecting to the server successfully\n");
    //------------------------------------连接服务器----------------------------------

    //------------------------------------客户端处理----------------------------------
    pos = 0;
    while (pos != 4){
        switch (pos){
            case 0:
                /************************初始界面：选择登录、注册、退出****************/
                pos = InitUI();
                break;
            case 1:
                //-----------------------登陆界面-----------------------------------
                if (Echo_core(sockfd, Login_Ui, LOGIN_APPL) == -1){
                    /** 登录失败，返回初始界面 */
                    pos = 0; 
                    printf("Enter <continue>...");
                    while(getchar() != '\n')
                        continue;
                    system("clear");
                }
                else{
                    /** 登录成功，跳转到查询单词页面 */
                    pos = 3;
                    system("clear");
                }

                break;
                //-----------------------登陆界面-----------------------------------
            case 2:
                //-----------------------注册界面-----------------------------------
                if (Echo_core(sockfd, Register_Ui, RGTER_APPL) == -1){
                    printf("\rRegister failed, continue [y/n]: ");
                    while (ch = getchar()){
                        if (ch == 'y'){
                            /** 返回注册界面*/
                            pos = 2;
                            break;
                        }
                        else if (ch == 'n'){
                            /** 返回初始界面*/
                            pos = 0;
                            break;
                        }
                        else
                            printf("Enter 'y' or 'n': ");
                    }
                    /** 清理垃圾字符 */
                    while (getchar() != '\n')
                            continue;
                }
                else{
                    /** 注册成功，跳转到初始页面 */
                    pos = 0;
                }
                break;
                //-----------------------注册界面-----------------------------------
            case 3:
                //-----------------------查询单词-----------------------------------
                int stat = Echo_core(sockfd, Search_Ui, SEARC_APPL);
                if (stat == -1){
                    printf("\rSearch err, continue [y/n]: ");
                    while (ch = getchar()){
                        while (getchar() != '\n')
                            continue;
                        if (ch == 'y'){
                            pos = 3;
                            break; //继续查询
                        }
                        else if (ch == 'n'){
                            pos = 0;
                            //system("clear");
                            break; //返回初始界面
                        }
                        else
                            printf("Enter 'y' or 'n': ");
                    }
                }
                else if (stat == 4){
                    pos = 4;  //查询成功，继续查询
                }else{
                    pos = 3;
                }
                break;
                //-----------------------查询单词-----------------------------------
            case 4:
                /** 退出客户端 */
                printf("client exit!!!\n");
                break;
            default:
                printf("pos err\n");
                break;
        }
    }
    //------------------------------------客户端处理----------------------------------

    close(sockfd);
    return 0;
}