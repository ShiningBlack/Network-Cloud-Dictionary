#include "sock.h"

int CreateSock(int *sockfd)
{
    *sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (*sockfd == -1)
        return -1;
    return 0;
}

int BindSock(int sockfd, char *addr, int port)
{
    socklen_t addrlen;
    struct sockaddr_in ser_addr;

    addrlen = sizeof(ser_addr);
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(port);
    ser_addr.sin_addr.s_addr = inet_addr(addr);

    if (bind(sockfd, (struct sockaddr *)&ser_addr, addrlen) == -1)
        return -1;
    else
        return 0;
}

int ListenSock(int sockfd, int num)
{
    if (listen(sockfd, num) == -1)
        return -1;
    else
        return 0;
}

int AcceptSock(int sockfd, int *accefd, struct sockaddr_in *cli_addr)
{
    socklen_t addrlen = sizeof(struct sockaddr_in);

    *accefd = accept(sockfd, (struct sockaddr *)cli_addr, &addrlen);
    if (*accefd == -1)
        return -1;
    else
        return 0;
}

/********************************************************************************/
int CreateEpoll(int *epfd)
{
    *epfd = epoll_create(1);
    if (*epfd == -1)
        return -1;
    else
        return 0;
}

int AddEpoll(int epfd, int fd)
{
    struct epoll_event ev;

    ev.data.fd = fd;
    ev.events  = EPOLLIN | EPOLLET;

    if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1)
        return -1;
    else
        return 0;
}

int DelEpoll(int epfd, int fd)
{
    if (epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL) == -1){
        perror("DelEpoll()->epoll_ctl()");
        return -1;
    }
    if (close(fd) == -1){
        perror("DelEpoll()->close()");
        return -1;
    }
    else
        return 0;
}