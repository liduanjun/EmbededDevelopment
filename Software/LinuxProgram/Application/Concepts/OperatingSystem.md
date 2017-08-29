# Opreating System 操作系统

## 操作系统的含义

狭义地讲，操作系统指的是管理硬件(CPU,RAM,输入输出设备,存储设备等)，并为上层用户程序(user-space program)服务的内核。
广义地讲，操作系统除了内核外，还有一些软件工具，比如命令解释器，图形用户界面，文件管理工具，文本编辑器等。

我们通常说的linux操作系统是实际上应该叫 GNU/Linux 操作系统。因为它不仅包含内核，还有很多应用程序。

## GNU Operating System

理查德·马修·斯托曼（Richard Matthew Stallman, RMS，生于1953年），自由软件运动的精神领袖、
GNU计划以及自由软件基金会（Free Software Foundation）的创立者、著名黑客。他的主要成就包括Emacs及后来的GNU
Emacs，GNU C 编译器及GNU 除错器。 他所写作的GNU通用公共许可证（GNUGPL）是世上最广为采用的自由软件许可证，
为copyleft观念开拓出一条崭新的道路。他最大的影响是为自由软件运动竖立了道德、政治以及法律框架。

1983年，Richard Stallman (rms) 开启了[GNU](http://www.gnu.org/)计划，
1985年，它创建了自由软件基金会（Free Software Foundation,[FSF](http://www.fsf.org/)）。

Richard Stallman说它小时候老师讲过，小朋友带着好吃的东西要学会分享给其它的同学。而他发现现在很多大人，
写了代码却不能拿出来分享是不对的。他看不起AT&T的做法，他决定自己写一套unix，叫 Gnu Operating System.
然后自己定义一套授权证书，叫GPL，General Public License ,GPL的规则简单地说所有用GPL的代码都得开放源代码.
Gnu计划内的所有软件都是用的GPL，所以只要你修改了GNU计划中的任何一个软件，都需要开放源代码到公共区域。
怪不得后来Android Opreating System 用的是自己的C库。

Richard Stallman就开始写代码了，unix上有多少个软件，他就一个一个去实现，一开始是他一个人，后来有人支持他，
加入他，有钱捐钱，有力出力，他们一群人从1984年写到1991年，基本上把unix上的软件都实现了，除了内核，
这时候他发现有一个叫linux的内核做得挺好，就跟linus Torvalds(linux的发明者)商量着合并。
linus Torvalds接受了GPL，合并后的操作系统叫 GNU/Linux Operating System,大家都叫Linux操作系统。

Richard Stallman也写过内核，叫做Hurd,属于微内核的一种，和Linux宏内核相反。
Hurd设计思想很先进，但是很难设计，很难被调试，它还不成熟，不稳定，没什么人用它。

## GNU Operating System 和 BSD 的区别

和BSD不一样的地方是，BSD(包括openBSD,freeBSD,netBSD)是从内核到各种应用程序都提供。
而GNU Operating System必须和Linux Kernel 配合着才能组成一个完整的系统。