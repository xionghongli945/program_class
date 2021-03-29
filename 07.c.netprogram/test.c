#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#define MAXDATASIZE 256
#define STDIN 0
int main(void)
{
    int sockfd;
    int recybytes;
    char buf[MAXDATASIZE];
    char *str;
    int port;
    char name[MAXDATASIZE];
    char send_str[MAXDATASIZE];
    char ip[100] = {};
    struct sockaddr_in serv_addr; //套接字地址结构
    fd_set rfd_set, wfd_set, efd_set;
    struct timeval timeout; //本次select的超时结束时间
    int res;                //与服务器连接结果
    if ((sockfd == socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }
    bzero(&serv_addr, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    printf("please scanf port:\n");
    scanf("%d", &port);
    serv_addr.sin_port = htons(port);
    printf("please scanf ip:\n");
    scanf("%s", ip);
    inet_aton(ip, &serv_addr.sin_addr);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1)
    {
        //错误监测
        perror("connect:");
        exit(1);
    }
    fcntl(sockfd, F_SETFD, O_NONBLOCK);
    printf("please scanf your name:");
    scanf("%s", name);
    name[strlen(name)] = '\0';
    printf("%s:", name);
    fflush(stdout);
    send(sockfd, name, strlen(name), 0);
    while (1)
    {
        FD_ZERO(&rfd_set);
        FD_ZERO(&wfd_set);
        FD_ZERO(&efd_set);
        FD_SET(STDIN, &rfd_set);
        FD_SET(sockfd, &rfd_set);
        FD_SET(sockfd, &efd_set);
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;
        res = select(sockfd + 1, &rfd_set, &wfd_set, &efd_set, &timeout);
        if (res == 0)
        {
            continue;
        }
        if (res < 0)
        {
            perror("select error:");
            exit(-1);
        }
        if (FD_ISSET(STDIN, &rfd_set))
        {
            fgets(send_str, 256, stdin);
            send_str[strlen(send_str) - 1] = '\0';
            if (strncmp("quit", send_str, 4) == 0)
            {
                close(sockfd);
                exit(0);
            }
            send(sockfd, send_str, strlen(send_str), 0);
        }
        if (FD_ISSET(sockfd, &rfd_set))
        {
            recybytes = recv(sockfd, buf, MAXDATASIZE, 0);
            if (recybytes == 0)
            {
                close(sockfd);
                exit(0);
            }
            buf[recybytes] = '\0';
            printf("Server :%s\n", buf);
            printf("%s:", name);
            fflush(stdout);
        }
        if (FD_ISSET(sockfd, &efd_set))
        {
            close(sockfd);
            exit(0);
        }
    }
}