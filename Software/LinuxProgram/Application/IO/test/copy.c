/**
* 文件:1.2.c
* 描述:读写文件 从文件A中读出数据，写到文件B中
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

#define BUFSIZE 1
#define SRCFILE "a.txt"
#define DSTFILE "b.txt"

int main()
{
    int fd_a=0,fd_b=0,nbyte=0,sbyte=0;
    char buf[BUFSIZE];

    /* 打开src(source)源文件 a.txt 如果失败，则返回函数 */
    fd_a = open(SRCFILE,O_RDONLY);
    if(fd_a<0)
    {
        perror("file not exist");
        return -1;
    }

    /* 打开dst(destination)目的文件 b.txt 如果失败，则返回函数 */
    fd_b = open(DSTFILE,O_RDWR|O_CREAT|O_TRUNC,0666);
    if(fd_b<0)
    {
        perror("can not create file");
        return -2;
    }
    
    /* 一边读，一边写 */
    while( (nbyte = read(fd_a,buf,BUFSIZE))>0 )
    {
        sbyte+=nbyte;
        write(fd_b,buf,nbyte);
    }

    printf("file ");
    printf(SRCFILE);
    printf(" size = %d byte\n",sbyte);


    close(fd_a);
    close(fd_b);

    return 0;
}