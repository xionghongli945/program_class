#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#define SERVPORT 12306 /*服务器监听端口号*/
#define MAXDATASIZE 100 /*每次最大数据传输量*/
int main(int argc, char *argv[])
{
    int sock_fd, recvbytes;
    char buf[MAXDATASIZE];
    struct hostent *host;
    struct sockaddr_in serv_addr;
    if (argc <2)
    {
        fprintf(stderr, "Please enter the server's hostname\n");
        exit(1);
    }
    if ((host=gethostbyname(argv[1])) == NULL)
    {
        perror("gethostbyname 出错！");
        exit(1);
    }
    if ((sock_fd=socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket create 出错！");
        exit(1);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVPORT);
    serv_addr.sin_addr = *((struct in_addr *)host->h_addr);
    bzero(&(serv_addr.sin_zero), 8);
    if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("connect 出错！");
        exit(1);
    }
    if ((recvbytes=recv(sock_fd, buf, MAXDATASIZE, 0)) == -1)
    {
        perror("recevice 出错！");
        exit(1);
    }
    buf[recvbytes] = '\0';
    printf("收到：%s",buf);
    if(send(sock_fd, "It's Xionghongli ", 25, 0) == -1)
    printf("Send failed!\n");
    close(sock_fd);
}