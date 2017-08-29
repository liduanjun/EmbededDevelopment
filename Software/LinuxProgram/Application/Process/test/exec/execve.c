/**
* 文件:execve.c
* 描述:Linux进程 - execve - execute program
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
    /* argv , envp 数组最后一个元素一定是 NULL */
    char * const argv[]={"myexec","arg1","arg2","arg3",NULL};
    char * const envp[]={"name=zs","email=zs@126.com",NULL};

    /*
    execv - exec -> execute 执行 ; v -> argv 列表
    函数原型:int execve(const char *filename, char *const argv[],char *const envp[]);
    返回值  : int , -1 error , 更多见 man execve
    注意事项:参数 filename 为要执行的程序的文件名 filename;
             参数 argv 为要执行的程序的参数列表;
             参数 envp 为要执行的程序的环境列表;
    */
    execve("./myexec",argv,envp);

    return 0;
}