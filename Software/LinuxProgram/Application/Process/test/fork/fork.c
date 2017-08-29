/**
* 文件:fork.c
* 描述:Linux进程 - fork - create a child process
* 作者:liduanjun@126.com
* 创建:2017-02-04
* 修改:2017-02-04
**/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main()
{
    pid_t pid;

    errno = 0;

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
    }
    else
    {
        printf("Father fork return = %d \n",pid);
        printf("Father pid = %d \n",getpid());
    }    

    printf("hello fork!\n");

    return 0;
}