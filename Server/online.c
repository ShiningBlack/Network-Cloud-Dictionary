/************************/
/* @Features：用户在线表 */
/* @Nature:  链表       */
/************************/
#include "online.h"


/**
    初始化用户在线表
*/
online_t * Init_OnlineList(void)
{   
    online_t *pHead;

    pHead = (online_t *)malloc(sizeof(online_t));
    if (pHead == NULL)
        return NULL;
    pHead->fd = 0;
    pHead->next = NULL;
    
    return pHead;
}

int Add_OnlineList(online_t * list, char *username, int fd)
{
    struct node *new = (struct node *)malloc(sizeof(struct node));
    if (new == NULL)
        return -1;
    
    new->fd = fd;
    new->next = NULL;
    strcpy(new->name, username);

    while (list->next != NULL)
        list = list->next;
    list->next = new;

    return 0;
}

int Check_UserOnline(online_t * list, char *username)
{
    while (list->next != NULL)
    {
        list = list->next;
        if (strcmp(list->name, username) == 0)
            return 0; 
    }

    return -1;
}

int Del_OnlineList(online_t * list, int fd)
{   
    online_t * p = list;

    while (list->next != NULL){
        list = list->next;
        if (fd == list->fd)
        {   
            p->next = list->next;
            free(list);
            return 0;
        }
        p = p->next;
    }

    return -1;
}