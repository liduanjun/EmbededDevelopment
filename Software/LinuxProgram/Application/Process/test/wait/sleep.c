/**
* 文件:execl.2.c
* 描述:Linux进程 - 进程控制 - 用 sleep 函数延时 以同步父子进程
* 作者:liduanjun@126.com
* 创建:2017-02-04
* 修改:2017-02-04
**/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main()
{
    pid_t pid;

    errno = 0;

    pid = fork();
    /* 
        父子进程在此分道扬镳，
        在父进程中，变量pid为子进程的Process ID ,
        在子进程中，变量pid为等于0 ,
    */
    
    if(pid<0)
    {
        perror("fail to fork:");
    }
    else if(pid == 0)
    {
        execl("/bin/ls","ls","/","-al",NULL);
        printf("Children fork return = %d \n",pid);
        printf("Children pid = %d \n",getpid());
    }
    else
    {
        printf("Father fork return = %d \n",pid);
        printf("Father pid = %d \n",getpid());
    }    

    printf("hello fork!\n");

    /*
        sleep - delay for a specified amount of time
        函数原型:unsigned int sleep(unsigned int seconds);
        返回值  :unsigned int , 0 表示已经醒了 ，n 表示被中断了，中断后还差n秒才睡够。
        注意事项:sleep 函数是可以被中断的。当进程在 sleep(睡眠) 的过程中，如果被中断，那么当中断处理完成后，
                 回来再继续 sleep 下一条语句运行，此时,返回值表示 还差 n 秒 sleep 函数才会自然醒，才会去执行下一句。
    */
    sleep(1);

    return 0;
}