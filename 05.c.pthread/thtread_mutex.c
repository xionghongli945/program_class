#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
pthread_mutex_t my_lock;
int g_var;
void * pthread1(void * arg)
{
	printf("ENTER pthread1!\n");
	pthread_mutex_lock(&my_lock);
	for(int i = 0; i<10; i++)
	{
		//pthread_mutex_lock(&my_lock);
		g_var++;
		printf("th1:%d\n", g_var);
		//pthread_mutex_unlock(&my_lock);
		sleep(1);
	}
	pthread_mutex_unlock(&my_lock);
	return NULL;
}
void * pthread2(void * arg)
{
	printf("ENTER pthread2!\n");
	//printf("trylock:%d\n",pthread_mutex_trylock(&my_lock));
	while(pthread_mutex_trylock(&my_lock))
	{
		printf("pthread2 wait!\n");
		sleep(1);
	}
	for(int i = 0; i<10; i++)
	{
		//pthread_mutex_lock(&my_lock);
		g_var--;
		printf("th2:%d\n", g_var);
		//pthread_mutex_unlock(&my_lock);
		sleep(1);
	}
	pthread_mutex_unlock(&my_lock);
	return NULL;
}
int main()
{
	pthread_t tid1,tid2;
	pthread_mutex_init(&my_lock, NULL);
	pthread_create(&tid1, NULL, pthread1, NULL);
	pthread_create(&tid2, NULL, pthread2, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	return 0;
}
