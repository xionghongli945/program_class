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
#define STDIN 0
int main(int argc, char *argv[])
{
    if (argc <3)
    {
        fprintf(stderr, "Please enter the server's hostname and port\n");
        exit(1);
    }
    int sockfd, z, ret, recvbytes;
    char *str;
    char revbuf[MAXDATASIZE];
    char sedbuf[MAXDATASIZE];
    char name[MAXDATASIZE];
    struct sockaddr_in adr_srvr;
    struct timeval timeout;
    fd_set rfd_set, wfd_set, efd_set;
    printf("connecting server....\n");
    /* create IP address */
    if((sockfd=socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket error");
        exit(1);
    }
    bzero(&(adr_srvr.sin_zero), 8);
    adr_srvr.sin_family = AF_INET;
    adr_srvr.sin_port = htons(atoi(argv[2]));
    inet_aton(argv[1], &adr_srvr.sin_addr);
    fcntl(sockfd, F_SETFD, O_NONBLOCK);
    printf("input your name before chat\n");
    scanf("%s", name);
    getchar();
    name[strlen(name)] = '\0';
    printf("%s:", name);
    fflush(stdout);
    if (sendto(sockfd, name, sizeof(name), 0, (struct sockaddr *)&adr_srvr, sizeof(adr_srvr)) < 0)
    {
        perror("sendto error");
        exit(1);
    }
    /* user input by keyboard */
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
            sendto(sockfd, sedbuf, sizeof(sedbuf), 0, (struct sockaddr *)&adr_srvr, sizeof(adr_srvr));
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
            printf("Server: %s\n", revbuf);
            if (strncmp("quit", revbuf, 4) == 0)
            {
                printf("quit...\n");
                close(sockfd);
                exit(0);
            }
            printf("%s: ", name);
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