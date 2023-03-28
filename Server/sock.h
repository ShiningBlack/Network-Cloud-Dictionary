#ifndef _SOCK_H_
#define _SOCK_H_

#include "includes.h"

int CreateSock(int *sockfd);
int BindSock(int sockfd, char *addr, int port);
int ListenSock(int sockfd, int num);
int AcceptSock(int sockfd, int *accefd, struct sockaddr_in *cli_addr);

int CreateEpoll(int *epfd);
int AddEpoll(int epfd, int fd);
int DelEpoll(int epfd, int fd);
#endif