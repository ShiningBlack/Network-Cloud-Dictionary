#include "ui.h"

static void Select_UI(int pos);
static void Cancel_UI(int pos);

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
static void Select_UI(int pos) {
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
static void Cancel_UI(int pos) {
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

/* ========== UI 实现部分 ========== */

/* ui.c - safer, refactored UI for terminal
 *
 * 依赖：ui.h 中需要定义 pack_t 和 LEN，例如：
 *   #define LEN 128
 *   typedef struct {
 *       char username[LEN];
 *       char password[LEN];
 *       char msg[LEN];
 *   } pack_t;
 *
 * 编译建议：
 *   gcc -std=c11 -Wall -Wextra -g ui.c -o ui
 * 调试建议：
 *   gcc -g -fsanitize=address -O1 ui.c -o ui  （检查越界）
 */

// #include "ui.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <termios.h>
// #include <errno.h>

// #define UI_WIDTH 40
// #define MENU_PADDING 14

// /* ---------- 小工具 ---------- */
// static void clear_screen(void) {
//     /* 更可移植的清屏：移动光标到左上并清屏 */
//     printf("\033[H\033[J");
//     fflush(stdout);
// }

// /* 打印一行星号边框 */
// static void draw_line(int width) {
//     for (int i = 0; i < width; ++i) putchar('-');
//     putchar('\n');
// }

// /* 把 title 居中画在两颗星之间（宽度为 width），不使用复杂的 printf 格式 */
// static void draw_frame_title(const char *title, int width) {
//     int title_len = (int)strlen(title);
//     int inner_width = width - 2; /* 去掉首尾两个 '*' 和两个 '*' 的空位 */
//     int left = 0, right = 0;
//     if (inner_width > title_len) {
//         left = (inner_width - title_len) / 2;
//         right = inner_width - title_len - left;
//     }
//     draw_line(width);
//     printf("|");
//     for (int i = 0; i < left; ++i) putchar(' ');
//     printf("%s", title);
//     for (int i = 0; i < right; ++i) putchar(' ');
//     printf("|\n");
//     draw_line(width);
// }

// /* 打印菜单（title + items），pos 为高亮项索引（0-based） */
// static void print_menu(const char *title, const char *items[], int count, int pos) {
//     clear_screen();
//     draw_frame_title(title, UI_WIDTH);
//     printf("**%36s**\n", ""); /* 空行占位 */

//     for (int i = 0; i < count; ++i) {
//         printf("**");
//         /* 左侧空格对齐（固定） */
//         for (int j = 0; j < MENU_PADDING; ++j) putchar(' ');
//         if (i == pos) {
//             /* 高亮：反白 + 闪烁（可能在某些终端不支持闪烁） */
//             printf("\033[7m%s\033[0m", items[i]);
//         } else {
//             printf("%s", items[i]);
//         }
//         /* 右侧补空格直到行尾 */
//         int printed = MENU_PADDING + (int)strlen(items[i]);
//         for (int j = 0; j < (UI_WIDTH - 4 - printed); ++j) putchar(' ');
//         printf("**\n");
//     }

//     printf("**%36s**\n", "");
//     draw_line(UI_WIDTH);
//     fflush(stdout);
// }

// /* ---------- 安全输入函数 ---------- */

// /* 安全读取一行，保证 NUL 结尾，返回 0 成功，-1 失败/EOF */
// static int get_string_safe(char *buf, size_t maxlen) {
//     if (!buf || maxlen == 0) return -1;
//     if (fgets(buf, (int)maxlen, stdin) == NULL) {
//         buf[0] = '\0';
//         return -1;
//     }
//     /* 移除换行 */
//     buf[strcspn(buf, "\n")] = '\0';
//     return 0;
// }

// /* 使用 termios 以非 canonical 模式逐字符读取并显示 '*'，支持退格
//  * 返回读取长度 >=0，或 -1 出错。
//  */
// static int get_password_masked(char *buf, size_t maxlen) {
//     if (!buf || maxlen == 0) return -1;

//     struct termios oldt, newt;
//     if (tcgetattr(STDIN_FILENO, &oldt) != 0) {
//         return -1;
//     }
//     newt = oldt;

//     /* 关闭回显与 canonical，以便逐字符读取并即时显示 '*' */
//     newt.c_lflag &= ~(ECHO | ICANON);
//     newt.c_cc[VMIN] = 1;
//     newt.c_cc[VTIME] = 0;

//     if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) != 0) {
//         /* 尽量恢复旧设置（尽管可能没修改） */
//         tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
//         return -1;
//     }

//     size_t idx = 0;
//     int c = 0;
//     while ((c = getchar()) != '\n' && c != EOF) {
//         if (c == 127 || c == '\b') { /* 退格 */
//             if (idx > 0) {
//                 --idx;
//                 /* 在终端上删除一个字符（退格、空格、退格） */
//                 fputs("\b \b", stdout);
//                 fflush(stdout);
//             }
//         } else if (idx < maxlen - 1) {
//             buf[idx++] = (char)c;
//             putchar('*');
//             fflush(stdout);
//         } else {
//             /* 超出缓冲区，丢弃剩余输入直到换行 */
//             /* 仍然要读完行以免下次读残留 */
//             /* 但不要写入 buf */
//         }
//     }
//     buf[idx] = '\0';
//     putchar('\n');

//     /* 恢复终端设置 */
//     tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
//     return (int)idx;
// }

// /* ---------- 对外 UI 接口（保持原先行为） ---------- */

// /**
//     初始界面UI函数：
//             电子词典
//         1.登录
//         2.注册
//         3.退出
//     返回：
//         1：登录
//         2：注册
//         3：退出
// */
// int InitUI(void) {
//     static const char *menu_items[] = {"LOGIN", "REGISTER", "QUIT"};
//     const int menu_count = (int)(sizeof(menu_items) / sizeof(menu_items[0]));

//     int pos = 0;
//     print_menu("E-DICTIONARY", menu_items, menu_count, pos);

//     /* 切到非 canonical + no-echo 模式以便逐字符读取（用 termios） */
//     struct termios oldt, newt;
//     int term_changed = 0;
//     if (tcgetattr(STDIN_FILENO, &oldt) == 0) {
//         newt = oldt;
//         newt.c_lflag &= ~(ICANON | ECHO);
//         newt.c_cc[VMIN] = 1;
//         newt.c_cc[VTIME] = 0;
//         if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) == 0) term_changed = 1;
//     }

//     int ch;
//     while ((ch = getchar()) != '\n' && ch != EOF) {
//         if (ch == 'w' || ch == 'W') {
//             if (pos > 0) pos--;
//         } else if (ch == 's' || ch == 'S') {
//             if (pos < menu_count - 1) pos++;
//         } else if (ch == '\033') {
//             /* 如果按了方向键，通常是 ESC '[' 'A' 等，简单地尝试吞掉剩余两个字节（如果可用） */
//             int c1 = getchar();
//             int c2 = getchar();
//             (void)c1; (void)c2;
//         }
//         print_menu("E-DICTIONARY", menu_items, menu_count, pos);
//     }

//     if (term_changed) {
//         tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
//     } else {
//         /* 若无法切换 termios（例如非终端环境），什么也不做 */
//     }

//     clear_screen();
//     return pos + 1; /* 保持原有约定：1=login 2=register 3=quit */
// }

// /** 登录界面 UI */
// int Login_Ui(pack_t *pack) {
//     if (!pack) return -1; /* 强校验，避免 NULL deref */

//     clear_screen();
//     draw_frame_title("Login", UI_WIDTH);

//     printf("Username: ");
//     fflush(stdout);
//     if (get_string_safe(pack->username, (size_t)LEN) < 0) {
//         return -1;
//     }

//     printf("Password: ");
//     fflush(stdout);
//     if (get_password_masked(pack->password, (size_t)LEN) < 0) {
//         return -1;
//     }

//     return 0;
// }

// /** 注册界面 UI */
// int Register_Ui(pack_t *pack) {
//     if (!pack) return -1;

//     clear_screen();
//     draw_frame_title("Register", UI_WIDTH);

//     printf("Username: ");
//     fflush(stdout);
//     if (get_string_safe(pack->username, (size_t)LEN) < 0) return -1;

//     printf("Password: ");
//     fflush(stdout);
//     /* 注册处不做掩码也可以，但这里与登录一致做掩码 */
//     if (get_password_masked(pack->password, (size_t)LEN) < 0) return -1;

//     return 0;
// }

// /** 查询单词 UI */
// int Search_Ui(pack_t *pack) {
//     if (!pack) return -1;

//     clear_screen();
//     draw_frame_title("E-DICTIONARY", UI_WIDTH);

//     printf("Enter Word (type '#quit' to quit): ");
//     fflush(stdout);
//     if (get_string_safe(pack->msg, (size_t)LEN) < 0) return -1;

//     return 0;
// }

