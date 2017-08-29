/**
* 文件:shm_read.c
* 描述:shm - share memory - 共享内存，是最快的IPC
* 作者:liduanjun@126.com
* 创建:2017-02-06
* 修改:2017-02-06
**/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define BUFSIZE 2048

int main()
{
	int shmid;
	int ret;
	key_t key;
	char* shmadd;

	key = ftok(".",2017);

	if(key == -1)
	{
		perror("ftok:");
	}

	system("ipcs -m");

	shmid = shmget(key,BUFSIZE,IPC_CREAT|0666);
	if(shmid<0)
	{
		perror("shmid:");
		exit(-1);
	}

	shmadd = shmat(shmid,NULL,0);
	if(shmadd<0)
	{
		perror("shmat:");
		exit(-1);
	}

	printf("data = %s\n",shmadd);

	ret = shmdt(shmadd);

	if(ret<0)
	{
		perror("shmdt");
		exit(1);
	}
	else
	{
		printf("deleted shared-memory\n");
	}

	shmctl(shmid,IPC_RMID,NULL);
	system("ipcs -m");

	return 0;
}