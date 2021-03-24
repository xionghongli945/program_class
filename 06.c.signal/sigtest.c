#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
void func_ctrl_z();
//kill(pid,siganl);
int main()
{
    //(void) signal(SIGTSTP, func_ctrl_z);//注册自己的信号处理函数
    (void) signal(SIGTSTP, SIG_IGN);//ignore SIGTSTP
    (void) signal(SIGTSTP, SIG_DFL);//restore SIGTSTP default process
    int time=0;
    pid_t pid;
    pid = fork();
    if(pid > 0)
    {
        sleep(10);
        printf("parent kill child\n");
        kill(pid,SIGTSTP);
    }
    else if (pid = 0)
    {
        while(1)
        {
            time++;
            printf("chlid running:%ds\n",time);
            //fflush(0);
            sleep(1);
        }
    }
    else
    {
        printf("fork child failed!\n");
        exit(-1);
    }
    //(void) signal(SIGTSTP, func_ctrl_z);//注册自己的信号处理函数
    //alarm(10);10s后内核发送SIGALRM信号，默认终止
    return 0;
}
void func_ctrl_z()
{
    printf("\nI don't want hangup!\n");
}