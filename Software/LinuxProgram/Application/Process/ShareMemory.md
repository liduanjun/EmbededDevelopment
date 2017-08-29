# Share Memory 共享内存 - 进程间通讯

## 概念

Shared memory allows two or more processes to share a given region of memory. This
is the fastest form of IPC, because the data does not need to be copied between the client
and the server. The only trick in using shared memory is synchronizing access to a
given region among multiple processes. If the server is placing data into a shared
memory region, the client shouldn’t try to access the data until the server is done.
Often, semaphores are used to synchronize shared memory access. (But as we saw at
the end of the previous section, record locking or mutexes can also be used.)

## shell 上查看 Kernel 管理的共享内存

> ipcs -m