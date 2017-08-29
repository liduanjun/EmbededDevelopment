# Float - 浮点数

## 浮点数和定点数

小数点在数制中代表一种对齐方式，比如说你要比较1000和200哪个比较大你应该怎么做呢？你必须把他们右对齐：

1000   
200   

然后发现1比0（前面补零）大，所以1000比较大。那么如果是比较1000和200.01呢？这时候就不是右对齐了，而是对应位对齐，也就是小数点对齐：

1000   
200.01   

小数点位置在进制表示中是至关重要的，位置差一位整体就要差进制倍（十进制就是十倍）。在计算机中也是这样，虽然计算机使用二进制，
但在处理非整数时，也需要考虑小数点位置的问题，无法对齐小数点就无法做加法、减法比较这样的操作。我们说小数点位置，
永远是说相对于我们存储的数位来说的，比如说我们存储了01001001，然后小数点在第三位之后，也就是010.01001了。
在计算机中处理小数点位置有浮点和定点两种，定点就是小数点永远在固定的位置上，比如说我们约定一种32位无符号定点数，
它的小数点永远在第5位后面，这样最大能表示的数就是11111.111111111111111111111111111，它是32 - 2^-27，
最小非零数是2^-27。定点数是提前对齐好的小数，整数是一种特殊情况，小数点永远在最后一位之后。
定点数的优点是很简单，大部分运算实现起来和整数一样或者略有变化，但是缺点则是表示范围，比如我们刚才的例子中，
最大只能表示32；而且在表示很小的数的时候，大部分位都是0，精度很差，不能充分运用存储单元。
浮点数就是设计来克服这个缺点的，它相当于一个定点数加上一个阶码，阶码表示将这个定点数的小数点移动若干位。由于可以用阶码移动小数点，因此称为浮点数。

当代大部分计算机和程序在处理浮点数时所遵循的标准是由IEEE和ANSI制定的。比如，单精度的浮点数以4个字节来表示，
这4个字节可以分为三个部分：1位的符号位(0代表正数，1代表负数)，8位用作指数，最后的23位表示有效数字。

“浮点数”的定义是相对于“定点数”来说的，它们是两种表示小数的方式。

所谓“定点”是指小数点的位置总是在数的某个特定位置。
比如在银行系统中，小数点的位置总是在两位小数之前(这两位小数用来表示角和分)。其可以使用BCD码来对小数进行编码。

浮点格式则是基于科学计数法的，它是存储极大或极小数的理想方式。但使用浮点数来表示数据的时候，
由于其标准制定方面的原因可能会带来一些问题，例如：某两个不同的整数在单精度浮点数的表示方法下很可能无法区分。

## ARM 的浮点数

### 一：早期ARM上的浮点模拟器：
早期的ARM没有协处理器，所以浮点运算是由CPU来模拟的，即所需浮点运算均在浮点运算模拟器（float math emulation）上进行，需要的浮点运算，常要耗费数千个循环才能执行完毕，因此特别缓慢。
直到今天，在ARM Kernel配置时，都有如下选项：
* Floating point emulation  --->
* [ ] NWFPE math emulation
* [ ] FastFPE math emulation (EXPERIMENTAL) 
在这里，可以配置ARM 浮点模拟器。
 
浮点模拟器 模拟浮点是利用了undefined instrction handler，这么做带来的后果是带来极频繁的exception，大大增加中断延迟，降低系统实时性。
 
### 二：软浮点技术：
软浮点支持是由交叉工具链提供的功能，与Linux内核无关。当使用软浮点工具链编译浮点操作时，编译器会用内联的浮点库替换掉浮点操作，使得生成的机器码完全不含浮点指令，但是又能够完成正确的浮点操作。
 
### 三：浮点协处理器：
在较新版本的ARM中，可以添加协处理器。 一些ARM CPU为了更好的处理浮点计算的需要，添加了浮点协处理器。
并定义了浮点指令集。 如果不存在实际的硬件，则这些指令被截获并由浮点模拟器模块(FPEmulator)来执行。
 
 
### 四: 硬件浮点协处理器以及对应指令集的使用:
这里Sam是这样理解的：
想要使用硬件浮点协处理器来帮助运算Application中的浮点运算。需要以下几个前提条件：
1. Kernel中设置支持 硬件协处理器。
2. 编译器支持将浮点运算翻译成硬件浮点运算指令。
 
1.Kernle的支持：

如果Kernel不支持浮点协处理器，则因为协处理器寄存器等使用权限等问题，协处理器对应指令无法运行。
网络上有位高手指出：
CP15 c1 协处理器访问控制寄存器，这个寄存器规定了用户模式和特权对协处理器的访问权限。我们要使用VFP当然要运行用户模式访问CP10和CP11。
另外一个寄存器是VFP的FPEXC Bit30这是VFP功能的使用位。
其实操作系统在做了这两件事情之后，用户程序就可以使用VFP了。当然，Kernel 除了这2件事外，还处理了其他一些事情。
 
Sam看了看Kernel中对应代码，发现是汇编后就放弃继续研究了。
* Floating point emulation  --->
* [*] VFP-format 

floating point maths Include VFP support code in the kernel. This is needed IF your 
hardware includes a VFP unit.
 
2.编译器指定浮点指令：

编译器可以显式指定将浮点运算翻译成何种浮点指令。
 
如果编译器支持软浮点，则其可能会将浮点运算翻译成编译器中自带的浮点库。则不会有真正的浮点运算。
否则，可以翻译成FPA(Floating Point Accelerator)指令。 FPA指令再去查看是否有浮点模拟器。
还可以将浮点运算指定为VFP（vector floating point）指令。
 
 
### 五. 编译器指定编译硬浮点指令:
Sam有个测试程序，测试CPU浮点性能。例如：浮点加减乘除等运算的时间长度：
```
float src_mem_32[1024] = {1.024};

float dst_mem_32[1024] = {0.933};
 
for(j = 0; j < 1024; j++)
{
     for(i = 0; i < 1024; i++)
     {
          src_32 = src_mem_32[i] + dst_mem_32[i];
     }
}
```
通过printf 计算前后毫秒数的差值来看计算能力。
 
编译：

> arm-hisiv200-linux-gcc -c   -Wall fcpu.c -o fcpu.o
> arm-hisiv200-linux-gcc fcpu.o -o FCPU -L./

运行，则得到32位浮点数加1024次所需要时间。
 
如果要使用VFP呢？

> arm-hisiv200-linux-gcc -c   -Wall -mfpu=vfp -mfloat-abi=softfp  fcpu.c -o fcpu.o
> arm-hisiv200-linux-gcc -Wall -mfpu=vfp -mfloat-abi=softfp   fcpu.o -o FCPU -L./   

则运行后发现，所需要时间几乎减小了一半。 说明还是非常有效果的。
关于-mfpu   -mfloat-abi讲解：见附录2。 
 
另外，如何才能在直观的检查出是否使用VFP呢？
可以通过察看编译出的ASM程序得到结论。
 
> arm-hisiv200-linux-objdump -d fcpu.o

```
00000000 <test_F32bit_addition>:
   0:   e52db004        push    {fp}            ; (str fp, [sp, #-4]!)
   4:   e28db000        add     fp, sp, #0
   8:   e24dd00c        sub     sp, sp, #12
   c:   e3a03000        mov     r3, #0
  10:   e50b300c        str     r3, [fp, #-12]
  14:   e3a03000        mov     r3, #0
  18:   e50b3008        str     r3, [fp, #-8]
  1c:   e3a03000        mov     r3, #0
  20:   e50b3008        str     r3, [fp, #-8]
  24:   ea000017        b       88 <test_F32bit_addition+0x88>
  28:   e3a03000        mov     r3, #0
  2c:   e50b300c        str     r3, [fp, #-12]
  30:   ea00000d        b       6c <test_F32bit_addition+0x6c>
  34:   e51b200c        ldr     r2, [fp, #-12]
  38:   e59f3064        ldr     r3, [pc, #100]  ; a4 <test_F32bit_addition+0xa4>
  3c:   e0831102        add     r1, r3, r2, lsl #2
  40:   ed917a00        vldr    s14, [r1]
  44:   e51b200c        ldr     r2, [fp, #-12]
  48:   e59f3058        ldr     r3, [pc, #88]   ; a8 <test_F32bit_addition+0xa8>
  4c:   e0831102        add     r1, r3, r2, lsl #2
  50:   edd17a00        vldr    s15, [r1]
  54:   ee777a27        vadd.f32        s15, s14, s15
  58:   e59f304c        ldr     r3, [pc, #76]   ; ac <test_F32bit_addition+0xac>
  5c:   edc37a00        vstr    s15, [r3]
  60:   e51b300c        ldr     r3, [fp, #-12]
  64:   e2833001        add     r3, r3, #1
  68:   e50b300c        str     r3, [fp, #-12]
  6c:   e51b200c        ldr     r2, [fp, #-12]
  70:   e59f3038        ldr     r3, [pc, #56]   ; b0 <test_F32bit_addition+0xb0>
  74:   e1520003        cmp     r2, r3
  78:   daffffed        ble     34 <test_F32bit_addition+0x34>
  7c:   e51b3008        ldr     r3, [fp, #-8]
  80:   e2833001        add     r3, r3, #1
  84:   e50b3008        str     r3, [fp, #-8]
  88:   e51b2008        ldr     r2, [fp, #-8]
  8c:   e59f301c        ldr     r3, [pc, #28]   ; b0 <test_F32bit_addition+0xb0>
  90:   e1520003        cmp     r2, r3
  94:   daffffe3        ble     28 <test_F32bit_addition+0x28>
  98:   e28bd000        add     sp, fp, #0
  9c:   e49db004        pop     {fp}            ; (ldr fp, [sp], #4)
  a0:   e12fff1e        bx      lr
```

这里明显包含vfp指令。 所以是使用vfp指令的：
> arm-hisiv200-linux-gcc -c   -Wall -mfpu=vfp -mfloat-abi=softfp  fcpu.c -o fcpu.o
注意：VFP 指令指令在附录1中。
 
 
如果使用：
> arm-hisiv200-linux-gcc -c   -Wall fcpu.c -o fcpu.o
 
> arm-hisiv200-linux-objdump -d fcpu.o

```
00000000 <test_F32bit_addition>:
   0:   e92d4800        push    {fp, lr}
   4:   e28db004        add     fp, sp, #4
   8:   e24dd008        sub     sp, sp, #8
   c:   e3a03000        mov     r3, #0
  10:   e50b300c        str     r3, [fp, #-12]
  14:   e3a03000        mov     r3, #0
  18:   e50b3008        str     r3, [fp, #-8]
  1c:   e3a03000        mov     r3, #0
  20:   e50b3008        str     r3, [fp, #-8]
  24:   ea000019        b       90 <test_F32bit_addition+0x90>
  28:   e3a03000        mov     r3, #0
  2c:   e50b300c        str     r3, [fp, #-12]
  30:   ea00000f        b       74 <test_F32bit_addition+0x74>
  34:   e51b200c        ldr     r2, [fp, #-12]
  38:   e59f3068        ldr     r3, [pc, #104]  ; a8 <test_F32bit_addition+0xa8>
  3c:   e7932102        ldr     r2, [r3, r2, lsl #2]
  40:   e51b100c        ldr     r1, [fp, #-12]
  44:   e59f3060        ldr     r3, [pc, #96]   ; ac <test_F32bit_addition+0xac>
  48:   e7933101        ldr     r3, [r3, r1, lsl #2]
  4c:   e1a00002        mov     r0, r2
  50:   e1a01003        mov     r1, r3
  54:   ebfffffe        bl      0 <__aeabi_fadd>
  58:   e1a03000        mov     r3, r0
  5c:   e1a02003        mov     r2, r3
  60:   e59f3048        ldr     r3, [pc, #72]   ; b0 <test_F32bit_addition+0xb0>
  64:   e5832000        str     r2, [r3]
  68:   e51b300c        ldr     r3, [fp, #-12]
  6c:   e2833001        add     r3, r3, #1
  70:   e50b300c        str     r3, [fp, #-12]
  74:   e51b200c        ldr     r2, [fp, #-12]
  78:   e59f3034        ldr     r3, [pc, #52]   ; b4 <test_F32bit_addition+0xb4>
  7c:   e1520003        cmp     r2, r3
  80:   daffffeb        ble     34 <test_F32bit_addition+0x34>
  84:   e51b3008        ldr     r3, [fp, #-8]
  88:   e2833001        add     r3, r3, #1
  8c:   e50b3008        str     r3, [fp, #-8]
  90:   e51b2008        ldr     r2, [fp, #-8]
  94:   e59f3018        ldr     r3, [pc, #24]   ; b4 <test_F32bit_addition+0xb4>
  98:   e1520003        cmp     r2, r3
  9c:   daffffe1        ble     28 <test_F32bit_addition+0x28>
  a0:   e24bd004        sub     sp, fp, #4
  a4:   e8bd8800        pop     {fp, pc}

```
则不包含VFP指令。
且去调用 __aeabi_fadd
 
### 六：新一代ARM 浮点引擎---Neon：
Neon是ARM核心附带的浮点SIMD引擎，可以把它当一个DSP用。
如果不使用Neon，就只能有CPU自带的VFP进行浮点运算。标准A8的VFP没有管线化，速度是比较低的。A9的VFP管线化后，效能有明显提升，但还是不如Neon。
Neon支持与VFP类似，都需要编译器和Kernel双方支持才可以。
Kernel配置中：
* Floating point emulation  --->
* [*] VFP-format floating point maths
* [ ]   Advanced SIMD (NEON) Extension support 
需要选中。
 
编译器支持分析如下：
 
ARM的GCC 编译选项：
http://gcc.gnu.org/onlinedocs/gcc-4.1.1/gcc/ARM-Options.html#ARM-Options
 
 
### 七: ARM浮点相关编译选项：
1. -mfloat-abi=name:
	* Specifies which floating-point ABI to use.指定浮点应用程序二进制接口
	* 可选值：soft，softfp，hard
	* soft: 编译器将浮点操作编译成调用输出库....(没吃透，也许是调用编译器中的软浮点实现？？)
	* softfp: 编译器生成硬件浮点指令（汇编语句见附录1）。但继续使用软浮点调用规则。
	* hard:编译器生成硬件浮点指令（汇编语句见附录1）。使用FPU指定的调用规则。
 
2. 
	-mhard-float   
		Equivalent to -mfloat-abi=hard.   
	-msoft-float   
		Equivalent to -mfloat-abi=soft.   
 
3. 
	-mfpu=name   
	指定在此平台上，何种硬件浮点设备或者硬件浮点模拟器可用。
	可用参数：fpa，fpe2，fpe3，maverick，vfp，vfpv3，vfpv3-fp16，vfpv3-d16，vfpv3-d16-fp16，vfpv3xd，vfpv3xd-fp16，neon，neon-fp16，vfpv4，vfpv4-d16，fpv4-sp-d16，neon-vfpv4
	vfp: 之前已经详细谈过。   
	neon:前面也谈过。但neon并不完全支持 IEEE 754。   
 
 
4. 
	-mfpe=number   
	-mfp=number   
	-mfpe=X -mfp=X 等同于-mfpu=fpeX 其中X为fpe后面的数字。为了与老版本GCC统一。   
 
 
 
### 附录1 ：VFP 指令
* VABS、VNEG 和 VSQRT : 浮点绝对值、求反和平方根。
* VADD、VSUB 和 VDIV : 浮点加法、减法和除法。
* VMUL、VMLA、VMLS、VNMUL、VNMLA 和 VNMLS : 浮点乘法和乘加，包含可选求反。
* VCMP : 浮点数比较。
* VCVT（在单精度数和双精度数之间） : 在单精度数和双精度数之间转换。
* VCVT（在浮点数和整数之间） : 在浮点数和整数之间转换。
* VCVT（在浮点数和定点数之间） : 在浮点数和定点数之间转换。
* VCVTB，VCVTT（半精度扩展） : 在半精度和单精度浮点数之间转换。
* VMOV : 将浮点常数插入单精度或双精度寄存器。
 
 
### 附录2：
-mfpu=name   
-mfpe=number   
-mfp=number   
	This specifies what floating point hardware (or hardware emulation) is available on the target. 
	Permissible names are: fpa, fpe2, fpe3, maverick, vfp.  -mfp and -mfpe are synonyms for -mfpu=fpenumber, 
	for compatibility with older versions of GCC.
 
-mfloat-abi=name   
	Specifies which ABI to use for floating point values.  Permissible values are: soft, softfp and hard.
	soft and hard are equivalent to -msoft-float and -mhard-float respectively.  softfp allows the generation
	of floating point instructions, but still uses the soft-float calling conventions.

Sam不明白为什么 hard不能使用。只好使用softfp
 
### 附录3：
RVCT 简介:   
ARM公司提供的一套编译器。RVCT(RealView Compilation Tools)业内公认的能够支持所有ARM处理器，并提供最好的执行性能的编译器。
RVDS 4.0中使用的编译器即为RVCT. 优化程度让人惊讶。
 
 
### 附录4:
其它与浮点有关的编译选项：  
-ffast-math：  
-fno-signed-zeros：高版本GCC才有的优化选项。与浮点里面的 正负0 有关。  
 
 
 
### 附录5：GNU GCC, LD 官方文档：
* MainSite : www.gnu.org
* Documentation : http://www.gnu.org/doc/doc.html
* GNU manuals: http://www.gnu.org/manual/manual.html
* GCC : http://www.gnu.org/software/gcc/
* GCC-Online : http://gcc.gnu.org/onlinedocs/
* GCC-4.6-Online : http://gcc.gnu.org/onlinedocs/gcc-4.6.0/gcc/
 
 
LD:   
LD则在list中选择：Binutils (as bfd binutils gprof ld)
http://sourceware.org/binutils/docs/ld/


Hi3716C:   
Sam在Hi3716C 平台通常使用如下选项：
* -mcpu=cortex-a9
* -mfpu=vfp
* -mfloat-abi=softfp
* -march=armv7
* -fsigned-char
 
-mcpu:   
指出目标代码运行于何种ARM processor(ARM处理器)
可用的name  有：arm2, arm250, arm3, arm6, arm60, arm600, arm610,arm620, arm7, arm7m, arm7d, arm7dm, arm7di, arm7dmi, 
arm70, arm700, arm700i, arm710, arm710c, arm7100, arm720,arm7500, arm7500fe, arm7tdmi, arm7tdmi-s, arm710t, arm720t, 
arm740t, strongarm, strongarm110, strongarm1100,strongarm1110, arm8, arm810, arm9, arm9e, arm920, arm920t, arm922t, 
arm946e-s, arm966e-s, arm968e-s, arm926ej-s,arm940t, arm9tdmi, arm10tdmi, arm1020t, arm1026ej-s, arm10e, arm1020e, 
arm1022e, arm1136j-s, arm1136jf-s, mpcore, mpcorenovfp, arm1156t2-s, arm1156t2f-s, arm1176jz-s, arm1176jzf-s, 
cortex-a5, cortex-a8, cortex-a9, cortex-a15,cortex-r4, cortex-r4f, cortex-m4, cortex-m3, cortex-m1, cortex-m0, 
xscale, iwmmxt, iwmmxt2, ep9312

-march=armv7   
-march 指出目标ARM architecture(ARM指令集)。
可以使用的为：armv2, armv2a, armv3, armv3m, armv4, armv4t, armv5, armv5t, armv5e, armv5te, armv6, armv6j,armv6t2, 
armv6z, armv6zk, armv6-m, armv7, armv7-a, armv7-r, armv7-m, iwmmxt, iwmmxt2, ep9312