/**
* 文件:msg_write.c
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

	msg.mtype = 10;
	strcpy(msg.mtext,"hello message queue");

	key = ftok(".",2017);
	msgqid = msgget(key,IPC_CREAT|0666);
	if(msgqid == -1)
	{
		perror("msgget");
		exit(-1);
	}
	msgsnd(msgqid,&msg,sizeof(msg.mtext),0);
	printf("msg.mtype=%ld , msg.mtext=%s\n",msg.mtype,msg.mtext);
	//msgctl(msgqid,IPC_RMID,NULL);
	return 0;
}