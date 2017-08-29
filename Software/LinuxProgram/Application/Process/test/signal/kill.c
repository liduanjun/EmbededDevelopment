/**
* 文件:kill.c
* 描述:kill - send a signal to a process
* 作者:liduanjun@126.com
* 创建:2017-02-06
* 修改:2017-02-06
**/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

int main()
{
    pid_t pid;

    pid = fork();
    /* 
        父子进程在此分道扬镳，
        在父进程中，变量pid为子进程的Process ID ,
        在子进程中，变量pid为等于0 ,
    */

    if(pid<0)
    {
        perror("fail to fork:");
    }
    else if(pid == 0)
    {
        printf("Children fork return = %d \n",pid);
        printf("Children pid = %d \n",getpid());

		sleep(1);
    }
    else
    {
        printf("Father fork return = %d \n",pid);
        printf("Father pid = %d \n",getpid());

		kill(pid,SIGKILL);
    }    

    printf("hello fork!\n");

    return 0;
}