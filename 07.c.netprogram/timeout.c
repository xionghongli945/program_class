#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#define STDIN 0
int main()
{
    struct timeval tv;
    fd_set readfds;
    char name[30];
    printf("what's your name:\n");
    tv.tv_sec = 10;
    tv.tv_usec = 500000; /*微秒 1s = 1000000us*/
    FD_ZERO(&readfds);
    FD_SET(STDIN, &readfds);
    select(STDIN+1, &readfds, NULL, NULL, &tv);
    if (FD_ISSET(STDIN, &readfds))
    {
        //fgets(name, sizeof(name), STDIN);
        scanf("%s", name);
        printf("your name is %s\n",name);
    }
    else
        printf("输入超时\n");
    return 0;
}