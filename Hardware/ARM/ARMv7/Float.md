Floating-point (VFP)[edit]
VFP (Vector Floating Point) technology is an FPU (Floating-Point Unit) coprocessor extension to the ARM architecture[78] (implemented differently in ARMv8 - coprocessors not defined there). It provides low-cost single-precision and double-precision floating-point computation fully compliant with the ANSI/IEEE Std 754-1985 Standard for Binary Floating-Point Arithmetic. VFP provides floating-point computation suitable for a wide spectrum of applications such as PDAs, smartphones, voice compression and decompression, three-dimensional graphics and digital audio, printers, set-top boxes, and automotive applications. The VFP architecture was intended to support execution of short "vector mode" instructions but these operated on each vector element sequentially and thus did not offer the performance of true single instruction, multiple data (SIMD) vector parallelism. This vector mode was therefore removed shortly after its introduction,[79] to be replaced with the much more powerful NEON Advanced SIMD unit.

Some devices such as the ARM Cortex-A8 have a cut-down VFPLite module instead of a full VFP module, and require roughly ten times more clock cycles per float operation.[80] Pre-ARMv8 architecture implemented floating-point/SIMD with the coprocessor interface. Other floating-point and/or SIMD units found in ARM-based processors using the coprocessor interface include FPA, FPE, iwMMXt, some of which were implemented in software by trapping but could have been implemented in hardware. They provide some of the same functionality as VFP but are not opcode-compatible with it.

VFPv1
Obsolete
VFPv2
An optional extension to the ARM instruction set in the ARMv5TE, ARMv5TEJ and ARMv6 architectures. VFPv2 has 16 64-bit FPU registers.
VFPv3 or VFPv3-D32
Implemented on most Cortex-A8 and A9 ARMv7 processors. It is backwards compatible with VFPv2, except that it cannot trap floating-point exceptions. VFPv3 has 32 64-bit FPU registers as standard, adds VCVT instructions to convert between scalar, float and double, adds immediate mode to VMOV such that constants can be loaded into FPU registers.
VFPv3-D16
As above, but with only 16 64-bit FPU registers. Implemented on Cortex-R4 and R5 processors and the Tegra 2 (Cortex-A9).
VFPv3-F16
Uncommon; it supports IEEE754-2008 half-precision (16-bit) floating point as a storage format.
VFPv4 or VFPv4-D32
Implemented on the Cortex-A12 and A15 ARMv7 processors, Cortex-A7 optionally has VFPv4-D32 in the case of an FPU with NEON.[81] VFPv4 has 32 64-bit FPU registers as standard, adds both half-precision support as a storage format and fused multiply-accumulate instructions to the features of VFPv3.
VFPv4-D16
As above, but it has only 16 64-bit FPU registers. Implemented on Cortex-A5 and A7 processors (in case of an FPU without NEON[81]).
VFPv5-D16-M
Implemented on Cortex-M7 when single and double-precision floating-point core option exists.
In Debian Linux, and derivatives such as Ubuntu, armhf (ARM hard float) refers to the ARMv7 architecture including the additional VFP3-D16 floating-point hardware extension (and Thumb-2) above. Software packages and cross-compiler tools use the armhf vs. arm/armel suffixes to differentiate.[82]