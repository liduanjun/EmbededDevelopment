# IPC , Inter-Process Communication , 进程间通信

## pipe 无名管道

Pipes are the oldest form of UNIX System IPC and are provided by all UNIX systems.

pipe 有两个限制

> pipe 的工作方式是半双工(half duplex)，意味着数据流只能往一个方向流动。
> pipe 只能用在父子进程或者兄弟进程之间

