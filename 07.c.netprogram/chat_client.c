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
#include <errno.h>
#define MAXDATASIZE 256
#define SERVPORT 4444
#define STDIN 0
int main(int argc, char *argv[])
{
    if (argc <3)
    {
        fprintf(stderr, "Please enter the server's hostname and port\n");
        exit(1);
    }
    int sockfd, ret, recvbytes;
    char *str;
    char buf[MAXDATASIZE];
    char name[MAXDATASIZE];
    char send_str[MAXDATASIZE];
    struct sockaddr_in serv_addr;
    fd_set rfd_set, wfd_set, efd_set;
    struct timeval timeout;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket error");
        exit(1);
    }
    bzero(&serv_addr, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    //serv_addr.sin_port = htons(SERVPORT);
    serv_addr.sin_port = htons(atoi(argv[2]));
    inet_aton(argv[1], &serv_addr.sin_addr);
    //inet_aton("127.0.0.1", &serv_addr.sin_addr);
    //serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("connect error");
        exit(1);
    }
    fcntl(sockfd, F_SETFD, O_NONBLOCK);
    printf("input your name before chat\n");
    scanf("%s", name);
    name[strlen(name)] = '\0';
    printf("%s:", name);
    fflush(stdout);
    send(sockfd, name, strlen(name), 0);
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
            fgets(send_str, 256, stdin);
            send_str[strlen(send_str) -1] = '\0';
            if (strncmp("quit", send_str, 4) == 0)
            {
                send(sockfd, send_str, strlen(send_str), 0);
                close(sockfd);
                exit(0);
            }
            send(sockfd, send_str, strlen(send_str), 0);
        }
        if (FD_ISSET(sockfd, &rfd_set))
        {
            recvbytes = recv(sockfd, buf, MAXDATASIZE, 0);
            /*
            if(recvbytes == 0)
            {
                close(client_fd);
                close(sockfd);
                exit(0);
            }
            */
           buf[recvbytes] = '\0';
           printf("Server: %s\n", buf);
           if (strncmp("quit", buf, 4) == 0)
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
}