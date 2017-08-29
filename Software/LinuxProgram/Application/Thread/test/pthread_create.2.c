/**
* 文件:pthread_create.2.c
* 描述:Linux线程 - pthread_create 给线程传值
* 作者:liduanjun@126.com
* 创建:2017-02-06
* 修改:2017-02-06
**/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct ARG_PTHREAD
{
	char* name;
	int id;
}arg_pthread_t;

arg_pthread_t arg_pthread1,arg_pthread2;

void* fun_thread1(void* arg)
{
	printf("hello world 1!\n");
	arg_pthread_t* arg_pthread = arg;
	printf("name = %s,id = %d\n",arg_pthread->name,arg_pthread->id);
}

void* fun_thread2(void* arg)
{
	printf("hello world 2!\n");
	arg_pthread_t* arg_pthread = arg;
	printf("name = %s,id = %d\n",arg_pthread->name,arg_pthread->id);
}

int main()
{
	pthread_t thread1,thread2;
	int pthread_result;

	arg_pthread1.name = "pthread1";
	arg_pthread1.id = 1;

	arg_pthread2.name = "pthread2";
	arg_pthread2.id = 2;

	pthread_result = pthread_create(&thread1,NULL,fun_thread1,&arg_pthread1);
	pthread_result = pthread_create(&thread2,NULL,fun_thread2,&arg_pthread2);

	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
}