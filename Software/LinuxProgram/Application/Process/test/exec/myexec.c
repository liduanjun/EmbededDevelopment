/**
* 文件:myexec.c
* 描述:Linux进程 - 被 execle.1 调用，实现参数的传递演示
* 作者:liduanjun@126.com
* 创建:2017-02-04
* 修改:2017-02-04
**/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

/*
    main 的两种写法
    1. int main()
    2. int main(int argc , char* argv[])
        argc 代表传给进程的参数个数，
        argv 代表传给进程的参数的具体内容，
        数组argv中一共有argc个字符串(char *)
*/
int main(int argc , char* argv[])
{
    int i;

    for(i=0;i<argc;i++)
    {
        printf("arg%d : %s\n",i,argv[i]);
    }

    printf("name = %s , email = %s\n",getenv("name"),getenv("email"));
    printf("print over\n");

    return 0;
}