/**
* 文件:2.1.c
* 描述:标准IO - fopen,fclose,strerror
* 作者:liduanjun@126.com
* 创建:2017-02-04
* 修改:2017-02-04
**/

#include <stdio.h>
#include <errno.h>
#include <string.h>

int main()
{
    FILE *fp;
    if( (fp = fopen("h.txt","r"))==NULL )
    {
        printf("fail to fopen : %s\n",strerror(errno));
        return -1;
    }

    fclose(fp);

    return 0;
}