/**
* 文件:fifo.c
* 描述:fifo - 有名管道,fifo用于进程间通讯
* 作者:liduanjun@126.com
* 创建:2017-02-06
* 修改:2017-02-06
**/

#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main()
{
	int fork_pid;
	int pipefd[2];
	char buf[20];

	pipe(pipefd);

	fork_pid = fork();
	if(fork_pid<0)
	{
		perror("forking error:");
	}

	if(fork_pid==0)
	{
		/* children process filed */
		while(1)
		{
			write(pipefd[1],"hello",sizeof("hello"));
			sleep(1);
		}
	}
	else
	{
		/* father process filed */
		while(1)
		{
			/* memset 将buf的内容清0 */
			memset(buf,0,20);

			/* 如果没有读到，read 就会一直阻塞着 */
			read(pipefd[0],buf,20);
			printf("info from children by pipe = %s\n",buf);
		}
	}
}