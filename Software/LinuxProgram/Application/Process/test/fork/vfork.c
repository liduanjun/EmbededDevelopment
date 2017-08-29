/**
* 文件:vfork.c
* 描述:Linux进程 - vfork - create a child process and block parent
* 作者:liduanjun@126.com
* 创建:2017-02-04
* 修改:2017-02-04
**/

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main()
{
    pid_t pid;

    errno = 0;

    /*
        vfork - create a child process and block parent
        函数原型:pid_t vfork(void);
        注意事项:vfork()  is  a special case of clone(2).  It is used to create new processes 
                without copying the page tables of the parent process.  
                It may be useful in performance-sensitive applications where a child is created 
                which then immediately issues an execve(2).
                vfork 创建的子进程一定先于父进程运行。

                ubuntu on windows 10 有bug , 表现为 vfork 创建的子进程不一定先于父进程运行。
    */
    pid = vfork();

    if(pid<0)
    {
        perror("fail to vfork:");
    }
    else if(pid == 0)
    {
        //execlp("ls","ls",".","-al",NULL);
        printf("Children fork return = %d \n",pid);
        printf("Children pid = %d \n",getpid());
        exit(0);
    }
    else
    {
        printf("Father fork return = %d \n",pid);
        printf("Father pid = %d \n",getpid());
    }    

    printf("hello vfork!\n");

    return 0;
}