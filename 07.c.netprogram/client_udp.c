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
int main(int argc, char *argv[])
{
    if (argc <3)
    {
        fprintf(stderr, "Please enter the server's hostname and port\n");
        exit(1);
    }
    int sock_fd, z, port;
    char buf[80], strl[80];
    struct hostent *host;
    struct sockaddr_in adr_srvr;
    printf("connecting server....\n");
    /* create IP address */
    adr_srvr.sin_family = AF_INET;
    adr_srvr.sin_port = htons((int)argv[2]);
    //adr_srvr.sin_addr.s_addr = htonl(INADDR_ANY);
    adr_srvr.sin_addr.s_addr = htonl((int)argv[1]);
    bzero(&(adr_srvr.sin_zero), 8);
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock_fd == -1)
    {
        perror("socket error");
        exit(1);
    }
    printf("send message....\n");
    /* user input by keyboard */
    while(1)
    {
        printf("input send message:");
        scanf("%s",strl);
        printf("%s\n", strl);
        sprintf(buf, "%s", strl);
        z = sendto(sock_fd, buf, sizeof(buf), 0, (struct sockaddr *)&adr_srvr, sizeof(adr_srvr));
        if (z < 0)
        {
            perror("sendto error");
            exit(1);
        }
        if (strncmp(strl, "stop", 4) == 0)
        {
            printf("ending....\n");
            break;
        }   
    }
    close(sock_fd);
    exit(0);
}