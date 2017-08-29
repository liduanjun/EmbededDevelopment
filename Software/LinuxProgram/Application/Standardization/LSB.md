# Linux Stadard Base(LSB)

[LSB](https://wiki.linuxfoundation.org/lsb/start) 定义了Linux 上C语言库标准。

LSB 项目最初发起于 1998 年 5 月，其项目启动宣言得到了 Linus Torvalds、Bruce Perens、
Eric Raymond 等人的签名支持，当时的目标是建立一系列构建 Linux 发行版所采用的源代码应该遵循的标准，
并提供一个参考平台。2000 年 5 月，LSB 成为 Free Standards Group（FSG） 的一个工作组。

[Linux基金会](https://www.linuxfoundation.org)
是一个非盈利性的联盟，其目的在于协调和推动Linux系统的发展，以及宣传、保护和规范Linux，
该组织是2007年，由开源码发展实验室（Open Source Development Labs，OSDL)与
自由标准组织（Free Standards Group ,FSG)联合起来成立的.

LSB 基于 Single UNIX Specification(SUS == Posix),并在 SUS 的基础上拓展了标准，
LSB 的定义包括以下几个部分:

> * 文件目录 [Filesystem Hierarchy Standard (FHS)](https://wiki.linuxfoundation.org/lsb/fhs)
> * 库 [libraries](http://refspecs.linuxfoundation.org/LSB_5.0.0/LSB-Common/LSB-Common/requirements.html)
> * 一些系统工具和命令，包含POSIX规定的部分
> * 运行级别 run levels
> * 打印系统 printing system 
> * X Windows System

如果Linux发行商们都遵循 LSB 标准，那么应用程序开发者写的程序就可以不修改源码而直接编译
源码在各Linux发行版本上运行程序了。