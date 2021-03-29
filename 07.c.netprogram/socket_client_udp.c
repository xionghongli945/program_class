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
    int sock_fd, z;
    char buf[80], strl[80];
    struct sockaddr_in adr_srvr;
    FILE *fp;
    printf("open file....\n");
    /* open file (liu) with only read */
    fp = fopen("read.txt", "r");
    if(fp == NULL)
    {
        perror("open file error");
        exit(1);
    }
    printf("connecting server....\n");
    /* create IP address */
    adr_srvr.sin_family = AF_INET;
    adr_srvr.sin_port = htons(port);
    adr_srvr.sin_addr.s_addr = htonl(INADDR_ANY);
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
        sprintf(buf, "%s\n", strl);
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
    /* read 3 lines to send  
    for(int i=1;i<=3;i++)
    {
        fgets(strl, 80, fp);
        printf("%d:%s", i, strl);
        sprintf(buf, "%d:%s", i, strl);
        z = sendto(sock_fd, buf, sizeof(buf), 0, (struct sockaddr *)&adr_srvr, sizeof(adr_srvr));
        if(z < 0)
        {
            perror("recvfrom error");
            exit(1);        
        }
    }
    printf("send....\n");
    sprintf(buf, "stop\n");
    z = sendto(sock_fd, buf, sizeof(buf), 0, (struct sockaddr *)&adr_srvr, sizeof(adr_srvr));
    if(z < 0)
    {
        perror("sendto error");
        exit(1);
    }
    */
    fclose(fp);
    close(sock_fd);
    exit(0);
}