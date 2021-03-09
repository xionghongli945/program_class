#include<stdio.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
	FILE *in,*out;
	char ch;
	if(argc != 3)
	{
		printf("tips:x file1 file2\n");
		exit(0);
	}
	if((in = fopen(argv[1],"rb")) == NULL)
	{
		printf("%s open failed!\n",argv[1]);
		exit(0);
	}
	if((out = fopen(argv[2],"wb")) == NULL)
	{
		printf("%s open failed!\n",argv[2]);
		exit(0);
	}
	while(!feof(in))
	{
		ch = fgetc(in);
		fputc(ch,out);
	}
	fclose(in);
	fclose(out);
}







