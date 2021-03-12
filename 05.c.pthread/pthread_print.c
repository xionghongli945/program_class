#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
pthread_t ntid1;
pthread_t ntid2;
int conunter = 0;
void *thread_print(void *arg)
{
	int i =0;
	for(i; i<10; i++)
	{
		printf("%c%d",(char)arg,counter++);
		fflush(stdout);
		//printf("#");
		sleep(1);
	}
	return NULL;
}
int main()
{
	 int err;
	 err = pthread_create(&ntid1,NULL,thread_print,(void *)'#');
	 if(err != 0)
	 {
		 printf("pthread create failed!\n");
		 exit(1);
	 }
	 err = pthread_create(&ntid2,NULL,thread_print,(void *)'*');
	 pthread_join(ntid1,NULL);
	 pthread_join(ntid2,NULL);
	 return 0;
}

