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
int port = 8888;
int main()
{
    int sock_fd, len, z;
    char buf[256];
    struct sockaddr_in adr_inet;
    struct sockaddr_in adr_clnt;
    printf("waitting client.....\n");
    /* create IP address */
    adr_inet.sin_family = AF_INET;
    adr_inet.sin_port = htons(port);
    adr_inet.sin_addr.s_addr = htonl(INADDR_ANY);
    bzero(&(adr_inet.sin_zero), 8);
    len = sizeof(adr_clnt);
    /* create socket */
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock_fd == -1)
    {
        perror("create socket error");
        exit(1);
    }
    /* bind socket */
    z = bind(sock_fd, (struct sockaddr *)&adr_inet, sizeof(adr_inet));
    if(z == 1)
    {
        perror("bind error");
        exit(1);
    }
    while(1)
    {
        /* receive message */
        z = recvfrom(sock_fd, buf, sizeof(buf), 0, (struct sockaddr *)&adr_clnt, &len);
        if(z < 0)
        {
            perror("recvfrom error");
            exit(1);
        }
        buf[z] = '\n';
        printf("received:%s",buf);
        /* received "stop" ,disconnected */
        if(strncmp(buf, "stop", 4) == 0)
        {
            printf("ending...\n");
            break;
        }
    }
    close(sock_fd);
    exit(0);
}