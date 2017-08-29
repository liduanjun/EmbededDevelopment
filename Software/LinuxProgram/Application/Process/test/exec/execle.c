/**
* 文件:execle.1.c
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

    char * const envp[]={"name=zs","email=zs@126.com",NULL};

    /*
    execle - exec -> execute 执行 ; l -> list 参数列表 ; e -> environment 环境变量
    函数原型:int execle(const char *path, const char *arg,..., char * const envp[]);
    返回值  : int , -1 error 
    注意事项:函数倒数第二个参数必须是NULL
             参数 path 为要执行的程序的路径名 pathname;
             参数 arg  为要执行的程序的文件名 filename;
             参数 envp 为要传递给被调用程序的环境变量信息。
    */
    execle("./myexec","myexec","WWW",NULL,envp);

    return 0;
}