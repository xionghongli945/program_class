#include<stdio.h>
int main()
{
	FILE *f;
	char buf[100];
	char str[] = "hello,world!\n";
	if((f = fopen("test.txt","w")) == NULL)
	{
		printf("file open failed!\n");
		return 1;
	}
	fwrite(str,sizeof(str),1,f);
	//fprintf(f,"hello,world!\n");
	fseek(f,0,SEEK_SET);
	fgets(buf,99,f);
	printf("file reading:\n");
	printf("%s",buf);
	fclose(f);
	//printf("hello,world!\n");
	return 0;
}

