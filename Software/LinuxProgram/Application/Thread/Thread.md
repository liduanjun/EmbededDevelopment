#　Thread 线程

## create , destory , contorl

pthread_create - create a new thread

```
#include <pthread.h>
/*
	thread - 线程标号
	attr - 线程属性，通常使用NULL,表示使用默认属性
	start_routine - 执行线程的具体函数名
	arg - 传给线程的参数，为一个通用指针，通常使用NULL
*/
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine) (void *), void *arg);
```

pthread_exit - terminate calling thread

```
#include <pthread.h>

void pthread_exit(void *retval)
```

pthread_cancel - send a cancellation request to a thread

```
#include <pthread.h>

int pthread_cancel(pthread_t thread);
```

pthread_join - join with a terminated thread

```
#include <pthread.h>
/*
	thread - 被等待的进程号
	retval - 用于接受线程的状态,通常用NULL,表示不关心线程退出后的状态
*/
int pthread_join(pthread_t thread, void **retval);
```

## 常见问题

**1.编译**

gcc 编译内含 pthread 的程序时，要带 -pthread 选项