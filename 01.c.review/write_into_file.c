#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *f;
	char filename[10];
	char ch;
	scanf("%s",filename);
	if((f = fopen(filename,"w")) == NULL)
	{
		printf("open file failed!\n");
		exit(0);
	}
	ch = getchar();//接收scanf的回车键
	ch = getchar();//接收第一个字符
	while(ch != '#')
	{
		fputc(ch,f);
		putchar(ch);
		ch = getchar();
	}
	fclose(f);
	putchar('\n');
	return 0;
}
