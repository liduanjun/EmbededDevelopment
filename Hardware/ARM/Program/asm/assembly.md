FakeARM# assembly - ARM 汇编

## ARM指令和Thumb指令的区别

ARM指令有两种，ARM指令和Thumb指令

ARM指令：32 bit
Thumb指令：16 bit 或者 32 bit

ARM指令和Thumb指令使用的助记符是一样的，在编译由助记符写成的汇编代码时
可以指定将汇编代码编译成ARM指令还是Thumb指令的二进制文件。

16 bit 的 Thumb指令由于比 32 bit 的 ARM指令短一般，所以讲汇编文件
编译成Thumb指令的二进制文件通常比汇编文件编译成ARM指令的二进制文件
要短小。所以Thumb指令通常用在内存吃紧的MCU中。

ARM指令在ARMv8架构的处理器中可以被编译成 32 bit 或者 64 bit.

## ARM指令

### 操纵 32 位 PSR 的指令

复制一个寄存器到 PSR 中
  MSR     CPSR, R0                ; 复制 R0 到 CPSR 中
  MSR     SPSR, R0                ; 复制 R0 到 SPSR 中
  MSR     CPSR_flg, R0            ; 复制 R0 的标志位到 CPSR 中
  MSR     CPSR_flg, #1<<28        ; 复制(立即值)标志位到 CPSR 中

复制 PSR 到一个寄存器中
  MRS     R0, CPSR                ; 复制 CPSR 到 R0 中
  MRS     R0, SPSR                ; 复制 SPSR 到 R0 中


你有两个 PSR - CPSR 是当前的程序状态寄存器(Current Program Status Register)，
而 SPSR 是保存的程序状态寄存器(Saved Program Status Register)(前面的处理器模式的 PSR)。
每个有特权的模式都有自己的 SPSR，可获得的 PSR 有:

CPSR_all - 当前的 
SPSR_svc - 保存的，SVC(32) 模式 
SPSR_irq - 保存的，IRQ(32) 模式 
SPSR_abt - 保存的，ABT(32) 模式 
SPSR_und - 保存的，UND(32) 模式 
SPSR_fiq - 保存的，FIQ(32) 模式 

你不能显式的指定把 CPSR 保存到哪个 SPSR 中，切换到哪个模式才能改变哪个模式。


## 条件代码

每个指令的顶端部分是一个条件代码，所以可以有条件的运行每个单一的 ARM 指令。 
                                    
|指令位图|                      条件编号|条件代码|          	    所须标志|
|:---|:---|:---|:---|
|0000xxxx xxxxxxxx xxxxxxxx xxxxxxxx | 0 |   EQ(等于，Equal)               |  Z|
|0001xxxx xxxxxxxx xxxxxxxx xxxxxxxx | 1 |   NE(不等于，Not Equal)	     | ~Z|
|0010xxxx xxxxxxxx xxxxxxxx xxxxxxxx | 2 |   CS(进位设置，Carry Set)	    |  C|
|0011xxxx xxxxxxxx xxxxxxxx xxxxxxxx | 3 |   CC(进位清除，Carry Clear)     | ~C|
|0100xxxx xxxxxxxx xxxxxxxx xxxxxxxx | 4 |   MI(负号，MInus)        	     | N|
|0101xxxx xxxxxxxx xxxxxxxx xxxxxxxx | 5 |   PL(正号，PLus)         	     | ~N|
|0110xxxx xxxxxxxx xxxxxxxx xxxxxxxx | 6 |   VS(溢出设置，oVerflow Set)    | V|
|0111xxxx xxxxxxxx xxxxxxxx xxxxxxxx | 7 |   VC(溢出清除，oVerflow Clear)  |~V|
|1000xxxx xxxxxxxx xxxxxxxx xxxxxxxx | 8 |   HI(高于，HIgher)       	     | C and ~Z|
|1001xxxx xxxxxxxx xxxxxxxx xxxxxxxx | 9 |   LS(低于或同于，Lower or Same) |~C| and  Z|
|1010xxxx xxxxxxxx xxxxxxxx xxxxxxxx | A |   GE(大于等于，Greater or equal)|N =  V|
|1011xxxx xxxxxxxx xxxxxxxx xxxxxxxx | B |   LT(小于，Less Than)    	     |  N = ~V|
|1100xxxx xxxxxxxx xxxxxxxx xxxxxxxx | C |   GT(大于，Greater Than) 	     |(N =  V) and ~Z|
|1101xxxx xxxxxxxx xxxxxxxx xxxxxxxx | D |   LE(小于等于，Less or equal)  |(N = ~V)  or  Z|
|1110xxxx xxxxxxxx xxxxxxxx xxxxxxxx | E |   AL(总是，Always)	         |永真|
|1111xxxx xxxxxxxx xxxxxxxx xxxxxxxx | F |   NV(从不，Never)              |永假|

在多数汇编器中，插入条件代码到紧随在助记符根代码(stub)的后面；省略条件代码缺省为使用 AL。 

在一些汇编器中把 HS (高于或同于) 和 LO (低于) 分别用做 CS 和 CC 的同义词。 

条件 GT、GE、LT、LE 被成为有符号比较，而 HS、HI、LS、LO 被称为无符号比较。 

把一个条件代码与 1 进行异或得到相反的条件的代码。 

NB: ARM 废弃使用 NV 条件代码 - 假定你使用 MOV R0,R0 作为一个空指令而不是以前推荐的 MOVNV R0,R0 。将来的处理器可能重新使用 NV 条件来做其他事情。 

所须条件为假的指令执行 1S 周期，使一个指令有条件执行不招致时间处罚。

## 算数运算

### MOV : 传送(move)

格式 : MOV{条件}{S}  dest, op_1   
意义 : dest = op_1

MOV 从另一个寄存器、被移位的寄存器、或一个立即值装载一个值到目的寄存器。

```
MOV R1,R0 ; R1 = R0
MOV R1,#3 ; R1 = 3
MOV R1,R0,LSL#1 ; R1 = (R0 << 1)
```
### MVN : 传送取反的值(Move Negative)

格式 : MVN{条件}{S}  dest, op_1 
意义 : dest = !op_1

MVN 从另一个寄存器、被移位的寄存器、或一个立即值装载一个值到目的寄存器。
不同之处是在传送之前位被反转了，所以把一个被取反的值传送到一个寄存器中。

```
MVN R0,#0 ; R0 = -1
MVN R0,#4 ; R0 = -5
```
### ADD : 加法(Addition)

格式 : ADD{条件}{S}  <dest>, <op 1>, <op 2>
意义 : dest = op_1 + op_2

ADD 将把两个操作数加起来，把结果放置到目的寄存器中。
操作数 1 是一个寄存器，操作数 2 可以是一个寄存器，被移位的寄存器，或一个立即值: 

```
ADD R0, R1, R2 ; R0 = R1 + R2
ADD R0, R1, #256 ; R0 = R1 + 256
ADD R0, R2, R3,LSL#1 ; R0 = R2 + (R3 << 1)
```
### ADC : 带进位的加法

ADC 将把两个操作数加起来，并把结果放置到目的寄存器中。
它使用一个进位标志位，这样就可以做比 32 位大的加法。
运算ADD操作后，如果进位标志位为 1 时，表示要进位。

```
ADDS R4, R0, R2 ; Add lower words
ADC R5, R1, R3 ; Add upper words
```
上述代码是将两个 64 bit 的数加在一起。
R0 - 存放着 64 bit 数1 的低位
R1 - 存放着 64 bit 数1 的高位
R2 - 存放着 64 bit 数2 的低位
R3 - 存放着 64 bit 数2 的高位
R4 - 存放着 64 bit 结果 的低位
R5 - 存放着 64 bit 结果 的高位

R5 = R1 + R3 + !carry

### SUB : 减法

SUB 用操作数 one 减去操作数 two，把结果放置到目的寄存器中。

```
SUB R0,R1,R2 ; R0 = R1 -R2
SUB R0,R1,#32 ; R0 = R1 - 32
SUB R0,R2,R3,LSL#1 ; R0 = R2 - (R3 << 1)
```

### RSB : 反向减法

格式 : RSB{条件}{S}  <dest>, <op 1>, <op 2>
意义 : dest = op_2 - op_1

SUB 用操作数 two 减去操作数 one，把结果放置到目的寄存器中。操作数 1 是一个寄存器，操作数 2 可以是一个寄存器，被移位的寄存器，或一个立即值: 
  RSB     R0, R1, R2              ; R0 = R2 - R1
  RSB     R0, R1, #256            ; R0 = 256 - R1
  RSB     R0, R2, R3,LSL#1        ; R0 = (R3 << 1) - R2

### SBC : 带借位的减法

格式 : SBC{条件}{S}  <dest>, <op 1>, <op 2>
意义 : dest = op_1 - op_2 - !carry

SBC 做两个操作数的减法，把结果放置到目的寄存器中。
它使用进位标志来表示借位，这样就可以做大于 32 位的减法。
运算SUB操作后，如果进位标志位为 0 时，表示要借位。

```
SUB R4, R0, R2 ; Sub lower words
SBC R5, R1, R3 ; Sub upper words
```
上述代码是将两个 64 bit 的数相减。
R0 - 存放着 64 bit 数1 的低位
R1 - 存放着 64 bit 数1 的高位
R2 - 存放着 64 bit 数2 的低位
R3 - 存放着 64 bit 数2 的高位
R4 - 存放着 64 bit 结果 的低位
R5 - 存放着 64 bit 结果 的高位

R5 = R1 - R3 - !carry

### RSC : 带借位的反向减法(Reverse Subtraction with Carry)

格式 : RSC{条件}{S}  <dest>, <op 1>, <op 2>
意义 : dest = op_2 - op_1 - !carry

RSC 和 SBC 类似，不同的是倒换了两个操作数的前后位置。 

### MUL : 乘法(Multiplication)

格式 : MUL{条件}{S}  <dest>, <op 1>, <op 2>
意义 : dest = op_1 * op_2

MUL 提供 32 位整数乘法。如果操作数是有符号的，可以假定结果也是有符号的。 

```
MUL R0,R1,R2 ; R0 = R1*R2
```

### MLA : 带累加的乘法(Multiplication with Accumulate)

格式 : MLA{条件}{S}  <dest>, <op 1>, <op 2>, <op 3>
意义 : dest = (op_1 * op_2) + op_3

MLA 的行为同于 MUL，但它把操作数 3 的值加到结果上。这在求总和时有用。

```
MUL R0,R1,R2,R3 ; R0 = (R1*R2)+R3
```

## 逻辑运算

### AND : 逻辑与(logical AND)

格式 : AND{条件}{S}  <dest>, <op 1>, <op 2>
意义 : dest = op_1 AND op_2

AND 将在两个操作数上进行逻辑与，把结果放置到目的寄存器中；
对屏蔽你要在上面工作的位很有用。 操作数 1 是一个寄存器，
操作数 2 可以是一个寄存器，被移位的寄存器，或一个立即值: 

```
AND R0, R0, #3 ; R0 = R0 & 3
```
R0 = xxxx
3  = 0011
R0 & 3 = 00xx

### ORR : 逻辑或(logical OR)

格式 : AND{条件}{S}  <dest>, <op 1>, <op 2>
意义 : dest = op_1 ORR op_2

AND 将在两个操作数上进行逻辑与，把结果放置到目的寄存器中；
对屏蔽你要在上面工作的位很有用。 操作数 1 是一个寄存器，
操作数 2 可以是一个寄存器，被移位的寄存器，或一个立即值: 

```
ORR R0, R0, #3 ; R0 = R0 | 3
```
R0 = xxxx
3  = 0011
R0 | 3 = xx11

### BIC : 位清除(Bit Clear)

格式 : BIC{条件}{S}  <dest>, <op 1>, <op 2>
意义 : dest = op_1 AND (!op_2)

BIC 是在一个字中清除位的一种方法，与 OR 位设置是相反的操作。
操作数 2 是一个 32 位位掩码(mask)。如果如果在掩码中设置了某一位，
则清除这一位。未设置的掩码位指示此位保持不变。 

```
BIC R0,R1,#3 ; R0 = R1 & !3
```
R1 = xxxx
3  = 0011
R0 | 3 = xx00

### EOR : 逻辑异或(logical Exclusive OR)

格式 ： EOR{条件}{S}  <dest>, <op 1>, <op 2>
意义 : dest = op_1 EOR op_2

EOR 将在两个操作数上进行逻辑异或，把结果放置到目的寄存器中；
对反转特定的位有用。操作数 1 是一个寄存器，操作数 2 可以是一个寄存器，
被移位的寄存器，或一个立即值

```
ORR R0,R0,#3 ; R0 = R0^3
```
反转 R0 中的 0 和 1

## 移位运算

### 逻辑左移(Logical Shift Left)

格式 : Rx, LSL op_1
意义 : Rx = Rx << op_1

接受 Rx 的内容并按用‘n’或在寄存器 Rn 中指定的数量向高有效位方向移位。
最低有效位用零来填充。除了概念上的第 33 位(就是被移出的最小的那位)之外丢弃移出最左端的高位，
如果逻辑类指令中 S 位被设置了，则此位将成为从桶式移位器退出时进位标志的值。

···
R0, LSL #3 ; R0 = R0 << 3
R0, LSL R1 ; R0 = R0 << R1
···


### 算数左移(Arithmetic Shift Left)

格式 : Rx, ASL op_1
意义 : Rx = Rx << op_1

接受 Rx 的内容并按用‘n’或在寄存器 Rn 中指定的数量向高有效位方向移位。
最低有效位用零来填充。除了概念上的第 33 位(就是被移出的最小的那位)之外丢弃移出最左端的高位，
如果逻辑类指令中 S 位被设置了，则此位将成为从桶式移位器退出时进位标志的值。

···
R0, ASL #3 ; R0 = R0 << 3
R0, ASL R1 ; R0 = R0 << R1
···

### 逻辑右移(Logical Shift Right)

格式 : Rx, LSR op_1
意义 : Rx = Rx >> op_1

它在概念上与左移相对。把所有位向更低有效位方向移动。
如果逻辑类指令中 S 位被设置了，则把最后被移出最右端的那位放置到进位标志中。
它同于 BASIC 的 register = value >>> shift

···
R0, LSR #3 ; R0 = R0 >> 3
R0, LSR R1 ; R0 = R0 >> R1
···

### 算术右移(Arithmetic Shift Right)

格式 : Rx, ASR op_1
意义 : Rx = Rx >> op_1

类似于 LSR，但使用要被移位的寄存器(Rx)的第 31 位的值来填充高位，
用来保护补码表示中的符号。如果逻辑类指令中 S 位被设置了，
则把最后被移出最右端的那位放置到进位标志中。
它同于 BASIC 的 register = value >> shift

···
R0, ASR #3 ; R0 = R0 >> 3
R0, ASR R1 ; R0 = R0 >> R1
···

### 循环右移(Rotate Right)

格式 : Rx, ROR op_1
意义 : Rx = Rx >> op_1

循环右移类似于逻辑右移，但是把从右侧移出去的位放置到左侧，
如果逻辑类指令中 S 位被设置了，则同时放置到进位标志中，
这就是位的‘循环’。一个移位量为 32 的操作将导致输出与输入完全一致,
因为所有位都被移位了 32 个位置，又回到了开始时的位置! 

···
R0, ROR #3 ; R0 = R0 >> 3
R0, ROR R1 ; R0 = R0 >> R1
···

### 带扩展的循环右移(Rotate Right with extend)

格式 : Rx, RRX
意义 : Rx = Rx >> 1 且带扩展

这是一个 ROR#0 操作，它向右移动一个位置，不同之处是，
它使用处理器的进位标志来提供一个要被移位的 33 位的数量。


## 比较指令

### CMP : 比较(Compare)

格式 : CMP{条件}{P}  <op 1>, <op 2>
意义 : status = op_1 - op_2

CMP 允许把一个寄存器的内容如另一个寄存器的内容或立即值进行比较，
更改状态标志来允许进行条件执行。它进行一次减法，但不存储结果，而是正确的更改标志。
标志表示的是操作数 1 比操作数 2 如何(大小等)。如果操作数 1 大于操作操作数 2，则此后的有 GT 后缀的指令将可以执行。 


### CMN : 比较取负的值(Compare Negative)

格式 : CMN{条件}{P}  <op 1>, <op 2>
意义 : status = op_1 - (- op_2)

CMN 同于 CMP，但它允许你与小负值(操作数 2 的取负的值)进行比较，
比如难于用其他方法实现的用于结束列表的 -1。这样与 -1 比较将使用。

### TST : 测试位(Test bits)

格式 : TST{条件}{P}  <op 1>, <op 2>
意义 : Status = op_1 AND op_2

TST 类似于 CMP，不产生放置到目的寄存器中的结果。而是在给出的两个操作数上进行操作并把结果反映到状态标志上。
使用 TST 来检查是否设置了特定的位。操作数 1 是要测试的数据字而操作数 2 是一个位掩码。
经过测试后，如果匹配则设置 Zero 标志，否则清除它。 

### TEQ : 测试等价(Test Equivalence)

格式 : TEQ{条件}{P}  <op 1>, <op 2>
意义 : Status = op_1 EOR op_2

TEQ 类似于 TST。区别是这里的概念上的计算是 EOR 而不是 AND。
这提供了一种查看两个操作数是否相同而又不影响进位标志(不象 CMP 那样)的方法。

## 分支指令(Branch)

### B : 分支

格式 : B{条件}  <地址>

B 是最简单的分支。一旦遇到一个 B 指令，ARM 处理器将立即跳转到给定的地址，从那里继续执行。
注意存储在分支指令中的实际的值是相对当前的 R15 的值的一个偏移量，而不是一个绝对地址。
它的值由汇编器来计算，它是 24 位有符号数，左移两位后有符号扩展为 32 位，表示的有效偏移为 26 位(+/- 32 M)。 

```
B main ; 跳到主函数
```

### BL : 带连接的分支(Branch with Link)

格式 : BL{条件}  <地址>

BL 是另一个分支指令。就在分支之前，硬件会自动将PC指向的下一条指令的地址放在 LR 中。
等你执行完子程序后，可以将 LR 的值 复制到 PC 中，好让程序返回到分支之前的地址。

```
BL child_programe_1 
...
...
child_programe_1:
	xxx
	xxx
	MOV PC,LR
```

## 内存操作

### LDR : 从内存加载数据到寄存器(Load to Register)
### STR : 从寄存器存储数据到内存(Storage from Register)

LDR{条件}    Rd, <地址>
STR{条件}    Rd, <地址>
LDR{条件}B   Rd, <地址>
STR{条件}B   Rd, <地址>

### LDM : 从内存加载多个数据到寄存器(Load Muti-data to Register)
### STM : 从寄存器存储多个数据到内存(Storage Muti-data from Register)

LDM/STM 的主要用途是把需要保存的寄存器复制到栈上。

  栈        其他
  LDMED     LDMIB     预先增加装载
  LDMFD     LDMIA     过后增加装载
  LDMEA     LDMDB     预先减少装载
  LDMFA     LDMDA     过后减少装载 

  STMFA     STMIB     预先增加存储
  STMEA     STMIA     过后增加存储
  STMFD     STMDB     预先减少存储
  STMED     STMDA     过后减少存储

### SWP : 单一数据交换(swap)

格式 : SWP{条件}{B}  <dest>, <op 1>, [<op 2>]

这些指令装载一个内存的一个字(用寄存器 Rn 给出地址)到一个寄存器 Rd 并存储寄存器 Rm 到相同的地址。
Rm 和 Rd 可以是同一个寄存器，在这种情况下交换寄存器和内存位置的内容。
装载和存储操作通过设置 LOCK 引角(pin)为高电平来在操作期间锁定在一起，这指示内存管理器它们应当被没有中断的完成。 

## 其它操作

### SVC : 超级用户调用异常

