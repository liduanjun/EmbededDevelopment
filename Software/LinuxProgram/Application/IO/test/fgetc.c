/**
* 文件:2.1.c
* 描述:标准IO - fgetc,fputc
* 作者:liduanjun@126.com
* 创建:2017-02-04
* 修改:2017-02-04
**/

#include <stdio.h>

int main()
{
    int c;

    FILE* file = fopen("2.3.1.txt","w+");

    while(1)
    {
        c = fgetc(stdin);
        fputc(c,file);
        if( c == '\n' )
        {
            break;
        }
    }

    return 0;
}