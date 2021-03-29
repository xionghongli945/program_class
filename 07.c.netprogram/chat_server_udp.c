#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <fcntl.h>
#define MAXDATASIZE 256
#define SERVPORT 6666
#define STDIN 0
int main()
{
    FILE *fp;
    int sockfd, client_fd, ret, recvbytes, len;
    char *str;
    char revbuf[MAXDATASIZE];
    char sedbuf[MAXDATASIZE];
    char name[MAXDATASIZE];
    struct sockaddr_in adr_mine;
    struct sockaddr_in adr_clnt;
    struct timeval timeout;
    fd_set rfd_set, wfd_set, efd_set;
    printf("wait client....\n");
    /* create IP address */
    if((sockfd=socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket error");
        exit(1);
    }
    bzero(&(adr_mine.sin_zero), 8);
    adr_mine.sin_family = AF_INET;
    adr_mine.sin_port = htons(SERVPORT);
    adr_mine.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sockfd, (struct sockaddr *)&adr_mine, sizeof(adr_mine)) == -1)
    {
        perror("bind error");
        exit(1);
    }
    fcntl(sockfd, F_SETFD, O_NONBLOCK);
    len = sizeof(adr_clnt);
    recvbytes = recvfrom(sockfd, name, sizeof(name), 0, (struct sockaddr *)&adr_clnt,&len);
    name[sizeof(name)] = '\0';
    fflush(stdout);
    if ((fp=fopen("name_udp.txt", "a+")) == NULL)
    {
        printf("can not open file,exit...\n");
        return -1;
    }
    fprintf(fp, "%s\n", name); /* 保存client名字 */
    while(1)
    {
        FD_ZERO(&rfd_set);
        FD_ZERO(&wfd_set);
        FD_ZERO(&efd_set);
        FD_SET(STDIN, &rfd_set);
        FD_SET(sockfd, &rfd_set);
        FD_SET(sockfd, &efd_set);
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;
        ret =select(sockfd + 1, &rfd_set, &wfd_set, &efd_set, &timeout);
        if (ret == 0)
        {
            continue;
        }
        if (ret < 0)
        {
            perror("select error");
            exit(-1);
        }
        if (FD_ISSET(STDIN, &rfd_set))
        {
            fgets(sedbuf, 256, stdin);
            sedbuf[strlen(sedbuf) -1] = '\0';
            sendto(sockfd, sedbuf, sizeof(sedbuf), 0, (struct sockaddr *)&adr_clnt, sizeof(adr_clnt));
            if (strncmp("quit", sedbuf, 4) == 0)
            {
                close(sockfd);
                exit(0);
            }
        }
        if (FD_ISSET(sockfd, &rfd_set))
        {
            recvbytes = recv(sockfd, revbuf, MAXDATASIZE, 0);
            revbuf[recvbytes] = '\0';
            printf("%s:%s\n", name, revbuf);
            if (strncmp("quit", revbuf, 4) == 0)
            {
                printf("quit...\n");
                close(sockfd);
                exit(0);
            }
            printf("Server: ");
            fflush(stdout);
        }
        if (FD_ISSET(sockfd, &efd_set))
        {
            close(sockfd);
            exit(0);
        } 
    }
    close(sockfd);
    exit(0);
}