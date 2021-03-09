#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *in,*out;
	char ch,infile[10],outfile[10];
	printf("ENTER THE INFILE NAME:\n");
	scanf("%s",infile);
	if((in = fopen(infile,"r")) == NULL)
	{
		printf("infile open failed!\n");
		exit(0);
	}
	printf("ENTER THE OUTFILE NAME:\n");
	scanf("%s",outfile);
	if((out = fopen(outfile,"w")) == NULL)
	{
		printf("outfile open failed!\n");
		exit(0);
	}
	ch = getchar();
	while(!feof(in))
	{
		ch = fgetc(in);
		fputc(ch,out);
	}
	fclose(in);
	fclose(out);
	return 0;
}
