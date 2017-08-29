/**
* 文件:semaphore.c
* 描述:Linux线程 - Semaphore - 信号量
* 作者:liduanjun@126.com
* 创建:2017-02-06
* 修改:2017-02-06
**/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

void printer(char* str)
{
	//pthread_mutex_lock(&mutex);
	sem_wait(&sem);

	while(*str!='\0')
	{
		putchar(*str);
		fflush(stdout);
		str++;
		sleep(1);
	}
	printf("\n");

	//pthread_mutex_unlock(&mutex);
	sem_post(&sem);
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
	/*
		函数原型:int sem_init(sem_t *sem, int pshared, unsigned int value);
		注意事项:sem - 某个要被初始化的信号灯的名字
				pshared - 0 , 此信号灯只在单一进程中的多线程间使用
						  非0 , 此信号灯在多进程间使用
				value - 信号灯上灯的数量，当value=1时，semaphora 的作用和 mutex 类似
	*/
	sem_init(&sem,0,1);

	pthread_t thread1,thread2;

	pthread_create(&thread1,NULL,fun_pthread1,NULL);
	pthread_create(&thread2,NULL,fun_pthread2,NULL);

	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);

	return 0;
}