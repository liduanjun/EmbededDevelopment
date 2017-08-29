/**
* 文件:atexit.c
* 描述:Linux进程 - 进程控制- atexit - register a function to be called at normal process termination
* 作者:liduanjun@126.com
* 创建:2017-02-04
* 修改:2017-02-04
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
	退出时调用的函数，既没有返回值(void)，也没有参数(void).
	这种函数一般做程序的善后工作，比如关闭文件，释放malloc申请的内存等。
*/
void bye(void)
{
	printf("Bye Bye!\n");
}

int main(void)
{
	int result;

	/*
		函数原型:int atexit(void (*function)(void));
		注意事项:atexit 函数 和 on_exit 函数类似，但是 on_exit 函数已经不建议使用了
	*/
	result = atexit(bye);
	if (result != 0) {
		fprintf(stderr, "cannot set exit function\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}