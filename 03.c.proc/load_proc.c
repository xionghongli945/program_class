#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
	pid_t i;
	char *argc[]={"/home/xhl/program_class/03.c.proc/proc",NULL};
	printf("I'm load:%d\n",getpid());
	i = fork();
	if(i == 0)
	{
		execl(argc[0],"proc",argc[1]);
	}
	else
	{
		wait(NULL);
		printf("\nI'm load and finished!\n");
	}
	return 0;
}
