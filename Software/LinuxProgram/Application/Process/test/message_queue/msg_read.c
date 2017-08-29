/**
* 文件:msg_read.c
* 描述:message queue - 消息队列，进程间通讯
* 作者:liduanjun@126.com
* 创建:2017-02-06
* 修改:2017-02-06
**/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

typedef struct _msg
{
	long mtype;
	char mtext[50];
}MSG;

int main()
{
	key_t key;
	int msgqid;
	MSG msg;

	key = ftok(".",2017);
	msgqid = msgget(key,IPC_CREAT|0666);
	if(msgqid == -1)
	{
		perror("msgget");
		exit(-1);
	}
	msgrcv(msgqid,&msg,sizeof(msg.mtext),10,IPC_NOWAIT);
	printf("msg.mtext=%s\n",msg.mtext);
	//msgctl(msgqid,IPC_RMID,NULL);
	return 0;
}