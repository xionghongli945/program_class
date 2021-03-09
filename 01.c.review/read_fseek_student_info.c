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
int main()
{
	int i;
	FILE *f;
	if((f = fopen("student_list.txt","rb")) == NULL)
	{
		printf("file open failed!\n");
		exit(0);
	}
	for(i = 0;i < SIZE;i++)
	{
		fseek(f,i * sizeof(struct student_info),0);
		fread(&stud[i],sizeof(struct student_info),1,f);
		printf("%-15s %-4d   %-4d  %-15s\n",stud[i].name,stud[i].num,stud[i].age,stud[i].addr);
	}
	fclose(f);
	return 0;
}
