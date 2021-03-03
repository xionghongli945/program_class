#include<stdio.h>
int main()
{
	FILE *f;
	char str[] = "hello,world!";
	f = fopen("test.txt","w");
	fwrite(str,sizeof(str),1,f);
	fclose(f);
	printf("Wrote fanished!\n");
	//printf("hello,world!\n");
	return 0;
}

