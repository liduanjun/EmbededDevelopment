/**
* 文件:pause.c
* 描述:pause - wait for signal
* 作者:liduanjun@126.com
* 创建:2017-02-06
* 修改:2017-02-06
**/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

int main()
{
    printf("going to pause\n");

    pause();

    return 0;
}