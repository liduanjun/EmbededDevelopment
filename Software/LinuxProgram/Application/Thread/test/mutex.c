/**
* 文件:mutex.c
* 描述:Linux线程 - pthread_mutex - 线程互斥
* 作者:liduanjun@126.com
* 创建:2017-02-06
* 修改:2017-02-06
**/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void printer(char* str)
{
	//pthread_mutex_lock(&mutex);

	while(*str!='\0')
	{
		putchar(*str);
		fflush(stdout);
		str++;
		sleep(1);
	}
	printf("\n");

	//pthread_mutex_unlock(&mutex);
}

void* fun_pthread1(void *arg)
{
	char *str = "hello";
	printer(str);
}

void* fun_pthread2(void *arg)
{
	char *str = "world";
	printer(str);
}

int main()
{
	pthread_t thread1,thread2;

	pthread_create(&thread1,NULL,fun_pthread1,NULL);
	pthread_create(&thread2,NULL,fun_pthread2,NULL);

	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);

	return 0;
}