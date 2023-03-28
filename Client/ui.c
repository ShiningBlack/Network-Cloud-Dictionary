#include "ui.h"

/**
    初始界面UI函数：
            电子词典
        1.登录
        2.注册
        3.退出
    pos返回：
        1：登录
        2：注册
        3：退出
*/
int InitUI(void){
    int i;
    char ch;
    int pos = 0;

    for(i = 0; i < 4; i++)
        printf("**********");
    putchar('\n');

    printf("**\033[12CE-dictionary\033[12C**\n");
    printf("**\033[36C**\n");

    printf("**\033[14C\033[7mLOGIN\033[0m\033[17C**\n");
    printf("**\033[14CREGISTER\033[14C**\n");
    printf("**\033[14CQUIT\033[18C**\n");

    printf("**\033[36C**\n");
    for(i = 0; i < 4; i++)
        printf("**********");
    putchar('\n');

    printf("\033[5A"); //移动到login行
    printf("\r**\033[14C\033[7m\033[5mLOGIN\033[0m\033[17C\033[?25l**");

    system("stty -icanon"); /**关闭缓冲区*/
    system("stty -echo");   /*关闭命令回显*/
    ch = getchar();
    while (ch != '\n'){
        switch (ch){
            case 'w':
                if (pos > 0 && pos < 3){
                    Cancel_UI(pos);
                    pos--;
                    printf("\033[1A");
                    Select_UI(pos);
                }
                break;
            case 's':
                if (pos < 2 && pos > -1){
                    Cancel_UI(pos);
                    pos++;
                    printf("\033[1B");
                    Select_UI(pos);
                }
                break;
            default:
                break;
        }
        ch = getchar();
    }
    system("stty icanon"); 
    system("stty echo");
    system("clear");
    printf("\033[?25h"); //恢复光标

    //发送pos
    pos++;
    return (pos==3) ? 4 : pos;
}

/**登录界面UI*/
int Login_Ui(pack_t *pack){
    int i;

    for(i = 0; i < 4; i++)
        printf("**********");
    putchar('\n');

    printf("**\033[15CLogin\033[16C**\n");
    printf("**\033[36C**\n");

    printf("**\033[4CUsername:\033[23C**\n");
    printf("**\033[4CPassword:\033[23C**\n");

    printf("**\033[36C**\n");
    printf("**\033[36C**\n");
    for(i = 0; i < 4; i++)
        printf("**********");
    putchar('\n');

        /**填充数据包*/
    printf("\033[5A\r\033[16C");//ui
    if (s_gets(pack->username, LEN) == NULL)
        return -1;
    printf("\r\033[16C");//ui
    
    i = 0;
    char ch;
    char buf[32] = {0};
    system("stty -icanon");
    system("stty -echo");
    while((ch = getchar()) != '\n')
    {
        if (ch == 127){
            if (i != 0){
                printf("\b");
                printf(" \033[1D");
                buf[--i] = '\0';
            }  
        }
        else{
            printf("*");
            buf[i++] = ch;
        }
    }
    strcpy(pack->password, buf);
    system("stty icanon");
    system("stty echo");
    printf("\033[1B\r");
    //printf("pack->password: %s\n", pack->password);
    //getchar();
    //if (s_gets(pack->password, LEN) == NULL)
    //    return -1;
    return 0;
}

/**注册界面UI*/
int Register_Ui(pack_t *pack){
    int i;

    for(i = 0; i < 4; i++)
        printf("**********");
    putchar('\n');

    printf("**\033[14CRegister\033[14C**\n");
    printf("**\033[36C**\n");

    printf("**\033[4CUsername:\033[23C**\n");
    printf("**\033[4CPassword:\033[23C**\n");

    printf("**\033[36C**\n");
    printf("**\033[36C**\n");
    for(i = 0; i < 4; i++)
        printf("**********");
    putchar('\n');

    /**填充数据包*/
    printf("\033[5A\r\033[16C");//ui
    if (s_gets(pack->username, LEN) == NULL)
        return -1;
    printf("\r\033[16C");//ui
    if (s_gets(pack->password, LEN) == NULL)
        return -1;
    return 0;
}

/**查询单词UI*/
int Search_Ui(pack_t *pack){
    int i;

    for(i = 0; i < 4; i++)
        printf("**********");
    putchar('\n');

    printf("**\033[12CE-dictionary\033[12C**\n");
    printf("**\033[36C**\n");

    printf("**\033[4CEnter Word:\033[21C**\n");
    printf("**\033[4CEcho:\033[27C**\n");

    printf("**\033[36C**\n");
    printf("**\033[36C**\n");
    printf("**\033[36C**\n");
    printf("**\033[36C**\n");
    printf("**\033[22C#quit to quit **\n");
    for(i = 0; i < 4; i++)
        printf("**********");
    putchar('\n');

        /**填充数据包*/
    printf("\033[8A\r\033[18C");//ui
    if (s_gets(pack->msg, LEN) == NULL)
        return -1;
    printf("\033[1B\033[8C");//ui

    //printf("word: %s len: %ld\n", pack->msg, strlen(pack->msg));
    return 0;
}


/**选择函数*/
static void Select_UI(int pos){
    switch (pos){
        case 0:
            printf("\r**\033[14C\033[7m\033[5mLOGIN\033[0m\033[17C\033[?25l**");
            break;
        case 1:
            printf("\r**\033[14C\033[7m\033[5mREGISTER\033[0m\033[14C\033[?25l**");
            break;
        case 2:
            printf("\r**\033[14C\033[7m\033[5mQUIT\033[0m\033[18C\033[?25l**");
            break;
        default:
            break;
    }
    return;
}

/**取消选择函数*/
static void Cancel_UI(int pos){
    switch (pos){
        case 0:
            printf("\r**\033[14CLOGIN\033[17C**");
            break;
        case 1:
            printf("\r**\033[14CREGISTER\033[14C**");
            break;
        case 2:
            printf("\r**\033[14CQUIT\033[18C**");
            break;
        default:
            break;
    }
    return;
}