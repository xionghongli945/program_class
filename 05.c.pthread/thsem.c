#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
sem_t my_sem;
sem_t my_semspace;//my_sem信号量 剩余空位数量
int buf[10];
int idx;
void * producer(void *arg)
{
	for (int i=0; i<10; i++)
	{
		sem_wait(&my_semspace);
		idx++;
		if (i == 9)
		{
			buf[idx] =0xab;
		}
		else
		{
			buf[idx] = rand();
		}
		printf("product:%d\n",buf[idx]);
		sem_post(&my_sem);
		sleep(1);
	}
	return NULL;
}
void * consumer(void *arg)
{
	while(1)
	{
		sem_wait(&my_sem);
		printf("consumer:%d\n",buf[idx--]);
		if (buf[idx] == 0xab) break;
		sem_post(&my_semspace);
		sleep(1);
	}
	return NULL;
}
int main()
{
	pthread_t tid1,tid2;
	sem_init(&my_sem, 0, 0);
	sem_init(&my_semspace, 0, 10);//信号量空位资源数为10
	pthread_create(&tid1, NULL, producer, NULL);
	pthread_create(&tid2, NULL, consumer, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	sem_destroy(&my_sem);
	exit(1);
}
