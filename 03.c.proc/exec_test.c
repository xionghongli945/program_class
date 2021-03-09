#include<stdio.h>
#include<unistd.h>
int main()
{
	char *arg[] = {"ls","-al",NULL};
	//execv("/bin/ls",arg);
	//execlp("ls","ls","-al",NULL);//p表示不需要给出文件路径，l表示参数需要一一列举
	execl("/bin/ls","ls","-al",NULL);//需要给出文件路径，需要一一列出参数
	return 1;
}

