#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
void func_ctrl_c();
int main()
{
    int i;
    sigset_t set,pendset;
    struct sigaction action;
    (void) signal(SIGINT,func_ctrl_c);
    if (sigemptyset(&set)<0)
        printf("初始化信号集合错误\n");
    if (sigaddset(&set,SIGINT)<0)
        printf("加入信号集合错误");
    if(sigprocmask(SIG_BLOCK,&set,NULL)<0)
        printf("往信号阻塞集合添加一个信号集合错误");
    else
    {
        for (i=0; i<5; i++)
        {
            printf("程序阻塞中\n");
            sleep(2);
        }
    }
    if(sigprocmask(SIG_UNBLOCK,&set,NULL)<0)
        printf("从信号阻塞集合删除一个信号集合错误");

}
void func_ctrl_c()
{
    printf("1\n");
    printf("2\n");
    printf("3\n");
    (void) signal(SIGINT,SIG_DFL);
}