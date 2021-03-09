#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
	int j;
	pid_t p1,p2,i;
	printf("I am parent:%d\nfork()\n",getpid());
	i = fork();
	if(i != 0)
	{
		printf("I am parent:%d\n",getpid());
		wait(NULL);
		/*
		for(j=0;j<100;j++)
		{
			printf("*");
			fflush(stdout);
			sleep(1);
		}
		*/
	}
	else
	{
		printf("I am child:%d My parent:%d\n",getpid(),getppid());
		
		for(j=0;j<20;j++)
		{
			printf("%d ",j);
			fflush(stdout);
			sleep(1);
		}
	
	}
	//printf("My PID:%d i:%d\n",getpid(),i);
	return 0;
}

