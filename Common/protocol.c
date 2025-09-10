#include "protocol.h"
#include <stdio.h>

/**
 * @brief 从标准输入安全地读取一行文本
 *
 * s_gets 函数是标准 fgets 函数的一个封装，旨在解决 fgets 在读取时可能保留换行符（'\n'）
 * 或在输入过长时留下残余字符在输入缓冲区的问题。
 *
 * @param buf 用于存储读取到的字符串的字符数组
 * @param len 缓冲区的大小
 * @return 成功读取时返回 buf，出错或到达文件末尾时返回 NULL
 */
char *s_gets(char buf[], int len)
{
    char *find;     // 声明一个字符指针，用于查找换行符
    char *ret_val;  // 声明一个字符指针，用于存储 fgets 的返回值

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