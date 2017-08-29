# Shell

## Shell 解释器
* Bourne shell(sh) : 
* C shell (csh) : 
* Korn shell (ksh) : 
* Bourne again shell (bash) :

## Shell Command

### 查看帮助

* 1: User commands; man-pages includes a very few Section 1 pages that document programs supplied by the GNU C library.
* 2: System calls documents the system calls provided by the Linux kernel.
* 3: Library functions documents the functions provided by the standard C library.
* 4: Devices documents details of various devices, most of which reside in /dev.
* 5: Files describes various file formats, and includes proc(5), which documents the /proc file system.
* 7: Overviews, conventions, and miscellaneous.
* 8: Superuser and system administration commands; man-pages includes a very few Section 8 pages, mainly documenting programs supplied by the GNU C library.

> `man help`  
> `man 2 open` 还可以指定哪个类的man文件，比如2
> [man-online](https://www.kernel.org/doc/man-pages/)

### 查看程序路径

> `which ls`

### 全盘搜索文件名

> 1. `sudo updatedb`
> 2. `locate stdio.h`

### 查看某个文件属于哪个包

> `dpkg -S /usr/include/stdio.h`


### 在文件中查找某字符利器:gnome-search-tool
> `sudo apt-get install gnome-search-tool`
> `gnome-search-tool`