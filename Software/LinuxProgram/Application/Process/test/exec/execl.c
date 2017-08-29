/**
* 文件:execl.1.c
* 描述:Linux进程 - execl, execlp, execle, execv, execvp, execvpe - execute a file
* 作者:liduanjun@126.com
* 创建:2017-02-04
* 修改:2017-02-04
**/

#include <sys/types.h>
#include <sys/wait.h>
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
        /*
        execl - exec -> execute 执行 ; l -> list 列表
        函数原型:int execl(const char *path, const char *arg, ...);
        返回值  : int , -1 error
        注意事项:函数最后一个参数必须是NULL
                 参数 path 为要执行的程序的路径名 pathname;
                 参数 arg  为要执行的程序的文件名 filename;
        */
        execl("/bin/ls","ls","-al",NULL);
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