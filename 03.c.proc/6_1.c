#include<stdio.h>
#include<unistd.h>
int main()
{
	printf("系统分配的进程号（PID）是:%d\n",getpid());
	printf("系统分配的父进程号（PPIDP）是:%d\n",getppid());
	return 0;
}

