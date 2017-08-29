/**
* 文件:alarm.c
* 描述:alarm - set an alarm clock for delivery of a signal
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
    printf("already set alarm , going to pause\n");

    alarm(3);

    pause();

    return 0;
}