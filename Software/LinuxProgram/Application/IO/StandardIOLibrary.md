# Standard IO

#### 流的打开与关闭

> * fopen
> * fdopen
> * freopen
> * fclose

#### 流的出错处理

> * perror
> * strerror

#### 流的读写

> * getc
> * fgetc
> * getchar
> * putc
> * fputc
> * putchar
> * gets
> * fgets
> * puts
> * fputs
> * fread
> * fwrite

#### 流的定位

> * fseek
> * ftell

#### 格式化输入输出

> * scanf
> * fscanf
> * sscanf
> * printf
> * fprintf
> * sprintf

## fopen, fdopen, freopen 

fopen, fdopen, freopen - stream open functions

```
#include <stdio.h>

FILE *fopen(const char *path, const char *mode);

FILE *fdopen(int fd, const char *mode);

FILE *freopen(const char *path, const char *mode, FILE *stream);
```
## fclose

fclose - close a stream

```
#include <stdio.h>

int fclose(FILE *stream);
```

## fgetc, fgets, getc, getchar, ungetc

fgetc, fgets, getc, getchar, ungetc - input of characters and strings

```
#include <stdio.h>

int fgetc(FILE *stream);

char *fgets(char *s, int size, FILE *stream);

int getc(FILE *stream);

int getchar(void);

int ungetc(int c, FILE *stream);
```

## fputc, fputs, putc, putchar, puts

fputc, fputs, putc, putchar, puts - output of characters and strings

```
#include <stdio.h>

int fputc(int c, FILE *stream);

int fputs(const char *s, FILE *stream);

int putc(int c, FILE *stream);

int putchar(int c);

int puts(const char *s);
```

## fread, fwrite

fread, fwrite - binary stream input/output

```
#include <stdio.h>

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);

size_t fwrite(const void *ptr, size_t size, size_t nmemb,FILE *stream);
```

## fgetpos, fseek, fsetpos, ftell, rewind

fgetpos, fseek, fsetpos, ftell, rewind - reposition a stream

```
#include <stdio.h>

int fseek(FILE *stream, long offset, int whence);

long ftell(FILE *stream);

void rewind(FILE *stream);

int fgetpos(FILE *stream, fpos_t *pos);

int fsetpos(FILE *stream, const fpos_t *pos);
```

## scanf, fscanf, sscanf, vscanf, vsscanf, vfscanf

scanf, fscanf, sscanf, vscanf, vsscanf, vfscanf - input format conversion

```
#include <stdio.h>

int scanf(const char *format, ...);
int fscanf(FILE *stream, const char *format, ...);
int sscanf(const char *str, const char *format, ...);

#include <stdarg.h>

int vscanf(const char *format, va_list ap);
int vsscanf(const char *str, const char *format, va_list ap);
int vfscanf(FILE *stream, const char *format, va_list ap);
```

## printf, fprintf, dprintf, sprintf, snprintf, vprintf, vfprintf, vdprintf, vsprintf, vsnprintf

printf, fprintf, dprintf, sprintf, snprintf, vprintf, vfprintf, vdprintf, vsprintf, vsnprintf - formatted output conversion

```
#include <stdio.h>

int printf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);
int dprintf(int fd, const char *format, ...);
int sprintf(char *str, const char *format, ...);
int snprintf(char *str, size_t size, const char *format, ...);

#include <stdarg.h>

int vprintf(const char *format, va_list ap);
int vfprintf(FILE *stream, const char *format, va_list ap);
int vdprintf(int fd, const char *format, va_list ap);
int vsprintf(char *str, const char *format, va_list ap);
int vsnprintf(char *str, size_t size, const char *format, va_list ap);
```