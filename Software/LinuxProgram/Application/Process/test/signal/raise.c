/**
* 文件:raise.c
* 描述:raise - send a signal to the caller
* 作者:liduanjun@126.com
* 创建:2017-02-06
* 修改:2017-02-06
**/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

void signal_handler(int sig)
{
    if(sig == SIGALRM)
    {
        printf("Revice Signal - SIGALRM\n");
    }
    else if(sig == SIGINT)
    {
        printf("Revice Signal - SIGINT\n");
    }
}

int main()
{
    signal(SIGALRM,signal_handler);
    signal(SIGINT,signal_handler);

    raise(SIGALRM);
    raise(SIGINT);

    return 0;
}