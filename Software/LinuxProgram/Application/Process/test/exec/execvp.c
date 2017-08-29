/**
* 文件:execvp.c
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
    /* argv , envp 数组最后一个元素一定是 NULL */
    char * const argv[]={"myexec","arg1","arg2","arg3",NULL};
    char * const envp[]={"name=zs","email=zs@126.com",NULL};

    /*
    execvp - exec -> execute 执行 ; v -> argv 列表
    函数原型:int execvp(const char *file, char *const argv[]);
    返回值  : int , -1 error
    注意事项:参数 file 为要执行的程序的文件名 filename;
             参数 argv 为要执行的程序的参数列表;
             程序 myexec 需要在环境变量中能找到才能正确执行
             下条命令将 myexec 放入到环境变量中去
             > sudo cp myexec /bin/ 
    */
    execvp("myexec",argv);

    return 0;
}