/**
* 文件:execlp.1.c
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
        execlp - exec -> execute 执行 ; l -> list 参数列表 ; p -> path 系统环境路径PATH
        函数原型:int execlp(const char *file, const char *arg, ...);
        返回值  : int , -1 error 
        注意事项:函数最后一个参数必须是NULL
                 参数 file 为要执行的程序的文件名 filename;
                 参数 arg  为要执行的程序的文件名 filename，和第一个参数一样;
                 execlp 和 excel 的区别在于，前者自带路径搜索功能，第一个参数不用像后者一样要写完整路径
        */
        execlp("ls","pwd","-al",NULL);
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