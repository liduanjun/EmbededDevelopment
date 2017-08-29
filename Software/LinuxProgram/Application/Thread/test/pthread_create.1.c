/**
* 文件:pthread_create.1.c
* 描述:Linux线程 - pthread_create 基本用法
* 作者:liduanjun@126.com
* 创建:2017-02-06
* 修改:2017-02-06
**/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void* fun_thread1(void* arg)
{
	printf("hello world 1!\n");
}

void* fun_thread2(void* arg)
{
	printf("hello world 2!\n");
}

int main()
{
	pthread_t thread1,thread2;
	int pthread_result;

	pthread_result = pthread_create(&thread1,NULL,fun_thread1,NULL);
	pthread_result = pthread_create(&thread2,NULL,fun_thread2,NULL);

	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
}