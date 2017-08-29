# Library 库

## C语言的库

> 1. 动态库
> 2. 静态库

## LSB

LSB资料

> [LSB](../Standardization/LSB.md)

## Libc

我们学习的libc库是Linux 应用程序开发当中最基础，最庞大的库。
ubuntu 14.04 amd64 发行版 中用到的libc库 是由 Gnu C libraries 实现的  
在bash中运行下面命令就可以得到 libc的信息

> /lib/x86_64-linux-gnu/libc.so.6

```
GNU C Library (Ubuntu EGLIBC 2.19-0ubuntu6.7) stable release version 2.19, by Roland McGrath et al.
Copyright (C) 2014 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.
There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.
Compiled by GNU CC version 4.8.2.
Compiled on a Linux 3.13.11 system on 2016-02-16.
Available extensions:
	crypt add-on version 2.1 by Michael Glad and others
	GNU Libidn by Simon Josefsson
	Native POSIX Threads Library by Ulrich Drepper et al
	BIND-8.2.3-T5B
libc ABIs: UNIQUE IFUNC
For bug reporting instructions, please see:
<https://bugs.launchpad.net/ubuntu/+source/eglibc/+bugs>.
```