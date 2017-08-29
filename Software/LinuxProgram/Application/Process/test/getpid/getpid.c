/**
* 文件:getpid.c
* 描述:getpid - get process ID of calling process
*      getppid - get parent process ID of calling process
* 作者:liduanjun@126.com
* 创建:2017-02-05
* 修改:2017-02-05
**/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{

    printf("the process ID of calling process = %d \n",getpid());
    printf("the parent process ID of calling process = %d \n",getppid());

    return 0;
}