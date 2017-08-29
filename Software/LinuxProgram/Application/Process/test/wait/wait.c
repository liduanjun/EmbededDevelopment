/**
* 文件:wait.c
* 描述:Linux进程 - 进程控制- wait, waitpid 等待进程改变状态
* 作者:liduanjun@126.com
* 创建:2017-02-04
* 修改:2017-02-04
**/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
    pid_t pid,w;
    int status;

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
        //execl("/bin/ls","ls",".",NULL);
        printf("Children fork return = %d \n",pid);
        printf("Children pid = %d \n",getpid());

        //sleep(1);
        pause();

        return 4;

    }
    else
    {
        printf("Father fork return = %d \n",pid);
        printf("Father pid = %d \n",getpid());

        /*
        wait, waitpid, waitid - wait for process to change state
        函数原型:pid_t wait(int *status);
        返回值  :pid_t , -1 error , n the process ID of the terminated child
        注意事项:wait 函数参数可以为空
        */
        w = wait(&status);

        if (w == -1) 
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) 
        {
            printf("exited, exit code(status)=%d\n", WEXITSTATUS(status));
        } 
        else if (WIFSIGNALED(status))
        {
            printf("killed by signal %d\n", WTERMSIG(status));
        } 
        else if (WIFSTOPPED(status)) 
        {
            printf("stopped by signal %d\n", WSTOPSIG(status));
        } 
        else if (WIFCONTINUED(status)) 
        {
            printf("continued\n");
        }

        printf("child process has exit , the process ID of terminated process is %d\n",w);

    }   

    return 0;
}