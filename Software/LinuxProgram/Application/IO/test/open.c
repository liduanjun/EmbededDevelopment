/**
* 文件:1.1.c
* 描述:创建文件
* 作者:liduanjun@126.com
* 创建:2017-02-04
* 修改:2017-02-04
**/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main()
{
    int fd;

    /* 打开文件 test.txt 如果失败，则返回函数 */
    fd = open("test.txt",O_RDWR|O_CREAT|O_TRUNC,0666);
    if(fd<0)
    {
        perror("fail to open");
        return -1;
    }
    
    close(fd);

    return 0;
}