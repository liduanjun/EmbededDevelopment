/**
* 文件:2.1.c
* 描述:标准IO - fopen,fclose,perror
* 作者:liduanjun@126.com
* 创建:2017-02-04
* 修改:2017-02-04
**/

#include <stdio.h>

int main()
{
    FILE *fp;
    if( (fp = fopen("h.txt","r"))==NULL )
    {
        perror("fail to fopen");
        return -1;
    }

    fclose(fp);

    return 0;
}