# ARM 伪指令

不同的ARM编译器拥有自己独特的ARM伪指令。
和ARM指令不同的是，伪指令没有对应的机器码。
伪指令存在的意义在于，伪指令方便程序员更快更好地开发出程序。
伪指令最终会由编译器翻译成真实的ARM指令。

* ARM指令 --直译--> 机器码
* ARM伪指令 --意译--> 机器码

## 开源编译器(GNU)所支持的伪代码

### 全局标号 .global , .globl

格式 : .global symbol

.globl 和 global 一样，表示这个标号在所有汇编文件中可用。
这个指令类似于ARM伪指令中的 EXPORT.

### 局部标号 .local

格式 : .local symbol

.local 表示此symbol只能在本文件内使用

### 变量赋值 .set .equ

格式 : .set symbol , expr

```
.set start , 0x40
start .equ ,0x40
```

和ARM伪代码中的 EQU 类似

### 数据定义 

#### .byte - 1 byte
#### .short - 2 byte
#### .word - 4 byte
#### .long - 4 byte
#### .quad - 8 byte
#### .float - 4 byte

a: .byte #1
等效于 char a = 1;

#### .space - n byte ； .skip - n byte ,和space一样.

* a: .space 10,0x01
用 0x01 填充 10 个byte的空间

####  .string , .ascii , .asciz.

.string 和 .space 类似
以下语句是相同的
* a: space "hello"
* a: sting "hello"
.string 和 .space 不同的地方在于   
.string 家族还有 .string8 , .string16 , .string32 , .string64   
.string 和 .string8 一样   
字符串 "hello" 放在 .string8 中就是 "hello"   
字符串 "hello" 放在 .string16 中就是 "h\0e\0l\0l\0o\0",16 bit 放 一个字符，空的地方放\0

.ascii 和 .string 类似；.asciz 和 .ascii 类似。
.ascii和.asciz的区别是，.asciz会在字符串后自动添加结束符\0.

#### 重复执行 .rept

.rept 3 ; 重复执行3次
.long 0
.endr

等效于

.long 0
.long 0
.long 0

## 汇编流程控制

### .if , .else , .else if , .endif

```
if xxx
...
.else
...
.endif
```
和C语言的  if-else 类似

### .macro , .endm , .exitm

```

```

## 其它操作

### .align
### .section
### .data
### .text
### .include
### .code32 
### .code16
### .thumb
### .extern
### .weak
### .end

## GNU汇编器支持的ARM伪代码

### ADR,ADRL - 装载标号地址与当前地址偏移量到寄存器

格式 : ADR register label
将label地址与当前地址的偏移量放入到寄存器中

```
ADR PC,RESET
``` 
上述代码将RESET标号地址相对于当前指令地址之差加到PC寄存器中

ADR和ADRL的区别：ADRL支持更长的偏移量，具体区别如下：
|Align|ADR|ADRL|
|:---|:---|:---|
|1 byte|-255 Byte , 255 Byte|-64 KiloByte , 64 KiloByte|
|4 byte|-1024 Byte , 1024 Byte|-256 KiloByte , 256 KiloByte|
|16 byte|-4096 Byte , 4096 Byte|-1024 KiloByte , 1024 KiloByte|

### LDR - 装载地址到寄存器

格式 : LDR register , =expr

```
LDR R0,=0xff00 ; 相当于 MOV R0,#0XFF00
LDR R1,=labelname ; 把标号labelname地址放在寄存器R1中
```