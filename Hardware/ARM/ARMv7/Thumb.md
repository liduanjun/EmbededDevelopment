Thumb[edit]
To improve compiled code-density, processors since the ARM7TDMI (released in 1994[70]) have featured the Thumb instruction set, which have their own state. (The "T" in "TDMI" indicates the Thumb feature.) When in this state, the processor executes the Thumb instruction set, a compact 16-bit encoding for a subset of the ARM instruction set.[71] Most of the Thumb instructions are directly mapped to normal ARM instructions. The space-saving comes from making some of the instruction operands implicit and limiting the number of possibilities compared to the ARM instructions executed in the ARM instruction set state.

In Thumb, the 16-bit opcodes have less functionality. For example, only branches can be conditional, and many opcodes are restricted to accessing only half of all of the CPU's general-purpose registers. The shorter opcodes give improved code density overall, even though some operations require extra instructions. In situations where the memory port or bus width is constrained to less than 32 bits, the shorter Thumb opcodes allow increased performance compared with 32-bit ARM code, as less program code may need to be loaded into the processor over the constrained memory bandwidth.

Embedded hardware, such as the Game Boy Advance, typically have a small amount of RAM accessible with a full 32-bit datapath; the majority is accessed via a 16-bit or narrower secondary datapath. In this situation, it usually makes sense to compile Thumb code and hand-optimise a few of the most CPU-intensive sections using full 32-bit ARM instructions, placing these wider instructions into the 32-bit bus accessible memory.

The first processor with a Thumb instruction decoder was the ARM7TDMI. All ARM9 and later families, including XScale, have included a Thumb instruction decoder.[72] The Thumb instruction set was originally inspired by SuperH's ISA; ARM licensed several patents from Hitachi.[72]

Thumb-2[edit]
Thumb-2 technology was introduced in the ARM1156 core, announced in 2003. Thumb-2 extends the limited 16-bit instruction set of Thumb with additional 32-bit instructions to give the instruction set more breadth, thus producing a variable-length instruction set. A stated aim for Thumb-2 was to achieve code density similar to Thumb with performance similar to the ARM instruction set on 32-bit memory.

Thumb-2 extends the Thumb instruction set with bit-field manipulation, table branches and conditional execution. At the same time, the ARM instruction set was extended to maintain equivalent functionality in both instruction sets. A new "Unified Assembly Language" (UAL) supports generation of either Thumb or ARM instructions from the same source code; versions of Thumb seen on ARMv7 processors are essentially as capable as ARM code (including the ability to write interrupt handlers). This requires a bit of care, and use of a new "IT" (if-then) instruction, which permits up to four successive instructions to execute based on a tested condition, or on its inverse. When compiling into ARM code, this is ignored, but when compiling into Thumb it generates an actual instruction. For example:

; if (r0 == r1)
CMP r0, r1
ITE EQ        ; ARM: no code ... Thumb: IT instruction
; then r0 = r2;
MOVEQ r0, r2  ; ARM: conditional; Thumb: condition via ITE 'T' (then)
; else r0 = r3;
MOVNE r0, r3  ; ARM: conditional; Thumb: condition via ITE 'E' (else)
; recall that the Thumb MOV instruction has no bits to encode "EQ" or "NE"
All ARMv7 chips support the Thumb instruction set. All chips in the Cortex-A series, Cortex-R series, and ARM11 series support both "ARM instruction set state" and "Thumb instruction set state", while chips in the Cortex-M series support only the Thumb instruction set.[73][74][75]

Thumb Execution Environment (ThumbEE)[edit]
ThumbEE (erroneously called Thumb-2EE in some ARM documentation), marketed as Jazelle RCT (Runtime Compilation Target), was announced in 2005, first appearing in the Cortex-A8 processor. ThumbEE is a fourth instruction set state, making small changes to the Thumb-2 extended instruction set. These changes make the instruction set particularly suited to code generated at runtime (e.g. by JIT compilation) in managed Execution Environments. ThumbEE is a target for languages such as Java, C#, Perl, and Python, and allows JIT compilers to output smaller compiled code without impacting performance.

New features provided by ThumbEE include automatic null pointer checks on every load and store instruction, an instruction to perform an array bounds check, and special instructions that call a handler. In addition, because it utilises Thumb-2 technology, ThumbEE provides access to registers r8-r15 (where the Jazelle/DBX Java VM state is held).[76] Handlers are small sections of frequently called code, commonly used to implement high level languages, such as allocating memory for a new object. These changes come from repurposing a handful of opcodes, and knowing the core is in the new ThumbEE state.

On 23 November 2011, ARM Holdings deprecated any use of the ThumbEE instruction set,[77] and ARMv8 removes support for ThumbEE.