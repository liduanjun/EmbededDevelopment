/**
* 文件:2.1.c
* 描述:标准IO - fflush
* 作者:liduanjun@126.com
* 创建:2017-02-04
* 修改:2017-02-04
**/

#include <stdio.h>

int main()
{
    int c;

    FILE* file = fopen("2.4.1.txt","w+");

    while(1)
    {
        c = fgetc(stdin);
        fputc(c,file);
        fflush(file);
        if( c == '@' )
        {
            break;
        }
    }

    return 0;
}