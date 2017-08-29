# AMBA - Advanced Microcontroller Bus Architecture

|历代总线|描述|
|:---|:---|
|ASB（the Advanced System Bus）|是第一代AMBA系统总线，同AHB相比，它数据宽度要小一些，它支持的典型数据宽度为8位、16位、32位。|
|APB（the Advanced Peripheral Bus）|是本地二级总线（local secondary bus ），通过桥和AHB/ASB相连。它主要是为了满足不需要高性能流水线接口或不需要高带宽接口的设备的互连|
|AHB（the Advanced High-performance Bus）|应用于高性能、高时钟频率的系统模块，它构成了高性能的系统骨干总线|
|AXI4（Advanced eXtensible Interface）|AXI4 协议是对 AXI3 的更新，在用于多个主接口时，可提高互连的性能和利用率|
|AXI4-Lite|AXI4-Lite 是 AXI4 协议的子协议，适用于与组件中更简单且更小的控件寄存器式的接口通信|
|AXI4-Stream|AXI4-Stream 协议可用于从主接口到辅助接口的单向数据传输，可显著降低信号路由速率|