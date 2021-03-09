#include<stdio.h>
#include<stdlib.h>
#define SIZE 4
struct student_info
{
	char name[10];
	int num;
	int age;
	char addr[15];
}stud[SIZE];
void save()
{
	FILE *f;
	int i;
	if((f=fopen("student_list.txt","wb")) == NULL)
	{
		printf("file open failed!\n");
		exit(0);
	}
	for(i = 0;i < SIZE;i++)
	{
		if(fwrite(&stud[i],sizeof(struct student_info),1,f) != 1)
		{
			printf("file write error!\n");
		}
	}
	fclose(f);
}
int main()
{
	int i;
	for(i = 0;i < SIZE;i++)
	{
		printf("input name num age addr\n:");
		scanf("%s%d%d%s",stud[i].name,&stud[i].num,&stud[i].age,stud[i].addr);
	}
	save();
	return 0;
}
