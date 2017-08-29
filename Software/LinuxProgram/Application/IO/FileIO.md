# File IO 

> * open
> * read
> * write
> * close
> * lseek
> * fcntl

## open
open()函数用于创造或者打开一个文件

```
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);

int creat(const char *pathname, mode_t mode);

int openat(int dirfd, const char *pathname, int flags);
int openat(int dirfd, const char *pathname, int flags, mode_t mode);
```

## read
read()函数从文件中读出一定的字节，放在缓存区(通常是内存)里。

```
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t count);
```

## write

write()函数将缓存区(通常是内存)里的数据写入到文件中。

```
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count);
```

## close

close()函数用于关闭一个打开的文件

```
#include <unistd.h>

int close(int fd);
```

## lseek

lseek()函数用于对当前读写位置进行定位。

```
#include <sys/types.h>
#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence);
```

## fcntl

fcntl()函数用于操作文件描述符号，比如可以对文件上锁。

```
#include <unistd.h>
#include <fcntl.h>

int fcntl(int fd, int cmd, ... /* arg */ );
```