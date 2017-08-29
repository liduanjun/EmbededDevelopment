# File 

## Everything is a file

unix界有句话流传甚广，“一切皆文件”
documents, directories, hard-drives, modems, keyboards, printers and even some inter-process and 
network communications are simple streams of bytes exposed through the filesystem name space.

Linux定义了一个抽象的内核级接口，能够容许集中不同的后端文件系统，文件树的有些部分由传统的给予磁盘的实现来处理，
其他部分则由内核中单独的驱动程序来负责。我们说“Linux中一切皆文件”直观地可以这样理解:所有的东西，设备、内存都模拟成文件。

## 文件类型

6种文件类型
> * file
> * directory
> * symbolic link
> * pipe
> * socket
> * device


## directory 目录

目录是一种特殊类型的文件，文件的内容是由目录内文件的信息组成的表格，文件信息包含了文件名和文件的引用。
这一“文件名+引用”的组合被称作链接，每个文件可以有多个链接，因而有多个名词，出现在相同或不同的目录中。  

目录可以包含指向文件或者目录的链接。
> * .  是指向自己这个目录的链接。
> * .. 是指向父级目录的链接。

相关命令

> dir - list directory contents
> ls - list directory contents

如果对基本指令不清楚，可以查阅Shell文档:[shell help](Shell.md)


## symbolic link 符号链接

符号链接给是给文件起了个别名。符号链接又叫做软链接(soft link)，类似Widnwos上的快捷方式。

> `ln -s`  
> 通过上述命令建立的符号链接文件如果被修改而不影响原文件。

在Linux中，与软链接(soft link)对应的还有硬链接(hard link)。

> `ln -s`  
> 通过上述命令建立的符号链接文件如果被修改会影响原文件。

文件都有文件名与数据，这在 Linux 上被分成两个部分:用户数据 (user data) 与元数据 (metadata)。
用户数据，即文件数据块 (data block)，数据块是记录文件真实内容的地方；而元数据则是文件的附加属性，
如文件大小、创建时间、所有者等信息。在 Linux 中，元数据中的 inode 号
（inode 是文件元数据的一部分但其并不包含文件名，inode 号即索引节点号）才是文件的唯一标识而非文件名。
文件名仅是为了方便人们的记忆和使用，系统或程序通过 inode 号寻找正确的文件数据块。

硬链接的inode号都是一样的，因为它们是同一个文件。软链接的inode号都是不一样的，因为它们不是同一个文件。

## 文件名

Linux上的文件名大多可以支持到最大255个字符。
当你命名文件时，建议只用0到9的数字，a到z和A到Z的字符，还有(.)，(-),(_)这些字符的集合.
不要使用(-)连字符作为文件名的开始，免得此文件被shell理解成为选项开关。

## 路径名

> * 绝对路径
> * 绝对路径以(/)开始，指明文件相对于根目录的位置。

> * 相对路径
> * 相对路径不以(/)开始，指明文件相对于当前目录的位置。
> * ./ 指向当前目录
> * ../指向当前目录的父级(上一级)目录

## 文件权限

文件记录着3类权限，
> * 文件的所有者的权限(读=4,写=2,运行=1)
> * 与文件的所有者同组人的权限(读=4,写=2,运行=1)
> * 与文件的所有者不同组人的权限(读=4,写=2,运行=1)

相关命令

> * chmod - change file mode bits
> * chown - change file owner and group