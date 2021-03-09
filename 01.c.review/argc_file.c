#include<stdio.h>
#include<stdlib.h>
int main(int argc,char *argc[])
{
	FILE *in,*out;
	char ch;
	if(argc != 3)
	{
		printf("tags:x file1 file2\n");
		exit(0);
	}
	if((in = fopen(argc[1],"rb")) == NULL)
	{
		printf("%s open failed!\n",argc[1]);
		exit(0);
	}
	if((out = fopen(argc[2],"wb")) == NULL)
	{
		printf("%s open failed!\n",argc[2]);
		exit(0);
	}







