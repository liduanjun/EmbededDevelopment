/**
* 文件:pthread_join.c
* 描述:Linux线程 - pthread_join 用来等待一个线程的结束
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
	pthread_exit("thread 1 exit!");
}

void* fun_thread2(void* arg)
{
	printf("hello world 2!\n");
	pthread_exit("thread 2 exit!");
}

int main()
{
	pthread_t thread1,thread2;
	int pthread_result;
	void* ret1,* ret2;

	pthread_result = pthread_create(&thread1,NULL,fun_thread1,NULL);
	pthread_result = pthread_create(&thread2,NULL,fun_thread2,NULL);

	/*
		在Linux中，默认情况下是在一个线程被创建后，必须使用此函数对创建的线程进行资源回收，
		但是可以设置Threads attributes来设置当一个线程结束时，直接回收此线程所占用的系统资源，
		详细资料查看Threads attributes。
		
		其实在Linux中，新建的线程并不是在原先的进程中，而是系统通过一个系统调用clone()。
		该系统调用copy了一个和原先进程完全一样的进程，并在这个进程中执行线程函数。不过这个copy过程和fork不一样。 
		copy后的进程和原先的进程共享了所有的变量，运行环境。这样，原先进程中的变量变动在copy后的进程中便能体现出来。

		pthread_join()函数，以阻塞的方式等待thread指定的线程结束。当函数返回时，被等待线程的资源被收回。
		如果线程已经结束，那么该函数会立即返回。并且thread指定的线程必须是joinable的。

		函数原型:int pthread_join(pthread_t thread, void **retval);
		注意事项:编译此文件时加 -pthread 选项
	*/
	pthread_join(thread1,&ret1);
	pthread_join(thread2,&ret2);

	printf("ret1 = %s\n",(char *)ret1);
	printf("ret2 = %s\n",(char *)ret2);
}