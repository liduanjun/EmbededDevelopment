# ARM 伪指令

不同的ARM编译器拥有自己独特的ARM伪指令。
和ARM指令不同的是，伪指令没有对应的机器码。
伪指令存在的意义在于，伪指令方便程序员更快更好地开发出程序。
伪指令最终会由编译器翻译成真实的ARM指令。

* ARM指令 --直译--> 机器码
* ARM伪指令 --意译--> 机器码

## ARM公司自己的编译器(ARMCC)所支持的伪代码

### ADR : 装载地址(load Address)

ADR{后缀} <寄存器>, <标号>

它把参照的地址装载到给定寄存器中: 
   00008FE4                    OPT     l%
   00008FE4 E28F0004           ADR     R0, text
   00008FE8 EF000002           SWI     "OS_Write0"
   00008FEC E1A0F00E           MOV     PC, R14
   00008FF0                    .text
   00008FF0                    EQUS    "Hello!" + CHR$13 + CHR$10 + CHR$0
   00008FFC                    ALIGN

下列代码有完全相同的效果: 

   00008FE4                    OPT     l%
   00008FE4 E28F0004           ADD     R0, R15, #4
   00008FE8 EF000002           SWI     "OS_Write0"
   00008FEC E1A0F00E           MOV     PC, R14
   00008FF0                    .text
   00008FF0                    EQUS    "Hello!" + CHR$13 + CHR$10 + CHR$0
   00008FFC                    ALIGN

实际上，它们的反汇编将显示: 
   *MemoryI 8FE4 +18
   00008FE4 :  E28F0004 : ..忊 : ADR     R0,&00008FF0
   00008FE8 :  EF000002 : ...? : SWI     "OS_Write0"
   00008FEC :  E1A0F00E : .馉? : MOV     PC,R14
   00008FF0 :  6C6C6548 : Hell : STCVSTL CP5,C6,[R12],#-&120 ; =288
   00008FF4 :  0A0D216F : o!.. : BEQ     &003515B8
   00008FF8 :  00000000 : .... : DCD     &00000000

ADR 是一个很有用的指令，你不需要关心相对 R15 的偏移量(例如，我们为什么只加 4?)，也不需要在一块代码上计算偏移量。可以简单的使用 ADR Rx, label 而汇编器将设法为你使用 ADD、SUB、MOV 或 MVN 中最恰当的那个指令。限制因素是你的引用范围只能是在 4096 字节中(不完全是真的，它典型的对 ADD 或 SUB 使用被循环右移的立即值，但是为了参数的一致性，我们假定范围是 4K)。



### ADRL : 装载长地址(load Address Long)

  ADRL{后缀} <寄存器>, <标号>

 BASIC 汇编器不支持它，但一些扩展支持它。 
ADRL 指令使用 ADR 和 ADD，或 ADR 和 SUB 的一个组合，来生成一个更广大的可以到达的地址范围。但是它总是使用两个指令，所以可以尝试更加可运做的布置来重新组织你的那些可以使用普通的 ADR 代码。 

还有，在一些汇编器中，用使用三个指令的 ADRX 来定位更大的地址。 

### ALIGN : 对齐指针(ALIGN pointers)

 ALIGN

ALIGN 指令设置 P% (如果需要的话还有 O%)来在一个字边界上对齐。通常要求它跟随着一个字符串或者一个或多个字节的数据，并切应当在更远的代码被汇编之前使用它。 
BASIC 汇编器非常聪明并且有经验，如果你疏忽了，它能为你处理对齐问题... 

   00008FF4                    OPT     l%
   00008FF4 E28F0004           ADR     R0, text
   00008FF8 EF000002           SWI     "OS_Write0"
   00008FFC EA000004           B       carryon
   00009000                    .text
   00009000                    EQUS    "unaligned text!!!" + CHR$0
   00009012                    .carryon
   00009014 E1A0F00E           MOV     PC, R14

### DCx : 初始化数据存储

 DCx <值>

没有 DCx 指令。小‘x’表示一个可能的范围。它们是: 
   DCB    预备一个字节(8 位值)
   DCW    预备一个半字(16 位值)
   DCD    预备一个字(32 位值)
   DCS    按给出的字符串的要求预备直到 255 个的字符

例如: 
   .start_counter
     DCB     1

   .pointer
     DCD     0

   .error_block
     DCD     17
     DCS     "Uh-oh! It all went wrong!" + CHR$0
     ALIGN

### EQUx : 初始化数据存储

EQUx <值>

没有 EQUx 指令，小‘x’表示一个可能的范围。它们是: 
   EQUB   预备一个字节(8 位值)
   EQUW   预备一个半字(16 位值)
   EQUD   预备一个字(32 位值)
   EQUS   按给出的字符串的要求预备直到 255 个的字符

简单的理解，除了名字不同之外与(上面的) DCx 完全一样。你可以使用‘=’作为 EQUB 的简写。 

### OPT : 设置汇编器选项(set assembler Options)

OPT <值>

它设置各种汇编器选项。  