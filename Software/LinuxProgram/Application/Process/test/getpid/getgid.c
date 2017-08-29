/**
* 文件:getgid.c
* 描述:getgid - get real user group ID of calling process
*      getegid - get effective(有效) group ID of calling process
* 作者:liduanjun@126.com
* 创建:2017-02-05
* 修改:2017-02-05
**/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{

    printf("the real group ID of calling process = %d \n",getgid());
    printf("the effective group ID of calling process = %d \n",getegid());

    return 0;
}