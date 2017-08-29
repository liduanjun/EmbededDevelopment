/**
* 文件:getuid.c
* 描述:getuid - get real user ID of calling process
*      geteuid - get effective user ID of calling process
* 作者:liduanjun@126.com
* 创建:2017-02-05
* 修改:2017-02-05
**/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{

    printf("the real user ID of calling process = %d \n",getuid());
    printf("the effective user ID of calling process = %d \n",geteuid());

    return 0;
}