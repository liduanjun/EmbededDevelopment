/**
* 文件:1.2.c
* 描述:文件定位,在文件中间插入字符串"12345"
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

#define FILE "c.txt"

int main()
{
    int fd,file_index=0,file_off=0;
    char buf[]="123";

    /* 打开 c.txt 如果失败，则返回函数 */
    fd = open(FILE,O_RDWR);
    if(fd<0)
    {
        perror("can not open file");
        return -2;
    }
    
    file_off = lseek(fd,0,SEEK_END);

    printf("file size = %d byte\n",file_off);

    file_off = lseek(fd,file_off/2,SEEK_SET);

    printf("file location now = %d byte\n",file_off);

    write(fd,buf,sizeof(buf)-1);

    close(fd);

    return 0;
}