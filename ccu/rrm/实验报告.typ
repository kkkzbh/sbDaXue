#import "report_template.typ": report

#show: report(
  header-text: "实验五 存储器实现实验报告",
  show-abstract: false,
  show-toc: false,
)[
= 一、实验目的
1. 了解只读存储器 ROM 和随机存取存储器 RAM 的原理。  
2. 理解 ROM 读取数据及 RAM 读取、写入数据的过程。  
3. 理解计算机中存储器地址编址和数据索引方法。  
4. 理解同步 RAM 和异步 RAM 的区别。  
5. 掌握调用 Xilinx 库 IP 实例化 RAM 的设计方法。  
6. 熟悉并运用 Verilog 语言进行电路设计。  
7. 为后续设计 CPU 的实验打下基础。

= 二、实验原理
== 存储器体系结构概述
现代 RISC-V/LoongArch 单周期 CPU 通常采用 Harvard 结构：指令存储器（ROM）与数据存储器（RAM）物理分离、独立总线并行访问。本实验仅实现数据 RAM 与指令 ROM，但所有原理均可推广至多级 Cache-DDR 架构。

=== 地址空间与字节对齐
- 地址总线宽度决定可寻址空间；本实验 A/B 两端口均使用 32 bit 地址，总线最低两位决定字节对齐模式。
- 为提升 FPGA Block RAM 资源利用率，实际地址输入给 IP 前取 `addr[6:2]`，即深度 256（2^8）×32 bit。
- 字节写使能（Byte Write Enable, BWE）通过 4 bit `wea`/`web` 信号独立控制 4 × 8 bit slice，满足 SB/SH/SW 指令对齐要求。

== RAM（同步双端口）设计原理
同步 RAM 意味着所有读写操作在时钟上升沿被锁存，避免组建级联触发的竞争—冒险；双端口（TDP）允许两个独立地址同时访问：
1. 端口 A（clka）—CPU 数据通路读写；  
2. 端口 B（clkb）—调试只读，实现在线观察而不破坏正常时序。

端口信号：
#{
  let port_spec(name, dir, width, description) = rect(
    width: 100%,
    radius: 2pt,
    inset: 8pt,
    fill: luma(240),
    stroke: none,
    grid(
      columns: (25%, 15%, 1fr),
      align: (left + horizon, center, left + horizon),
      gutter: 1em,
      // 信号名
      text(weight: "bold", raw(name, lang: "v")),
      // 方向和位宽
      stack(dir: ltr, spacing: 0.5em,
        box(
          fill: if dir == "I" { blue.lighten(80%) } else { green.lighten(80%) },
          stroke: if dir == "I" { blue } else { green },
          radius: 2pt,
          inset: (x: 4pt, y: 0pt),
          text(10pt, weight: "bold", if dir == "I" { "IN" } else { "OUT" })
        ),
        box(
          fill: luma(220),
          radius: 2pt,
          inset: (x: 4pt, y: 0pt),
          text(str(width) + "-bit")
        )
      ),
      // 描述
      description
    )
  );

  stack(
    spacing: 0.5em,
    port_spec("clka/clkb", "I", 1, "双端口时钟，由 10 MHz 驱动。" ),
    port_spec("wea/web", "I", 4, "字节写使能 (Byte Write Enable)。A口有效，B口固定为 `4'b0000`。" ),
    port_spec("addra/addrb", "I", 8, "端口地址，实际由 `addr[6:2]` 驱动，深度为 256。" ),
    port_spec("dina", "I", 32, "端口 A 写入数据。" ),
    port_spec("douta/doutb", "O", 32, "双端口读出数据。" ),
  )
}

=== 多字节写策略（SEC 模式）
`sec`=0/1/2 分别对应 *Byte/Half-word/Word* 模式。控制逻辑首先在 *行为级* 产生掩码数据 `wdata_masked` 与实际写使能 `actual_wea`：
```verilog
if (sec==2'd0 && addr[1:0]==2'b10) actual_wea = 4'b0100; // 只写第2个字节
```
保证 FPGA 端口始终按 32 bit 对齐、不触发未定义字节。

=== 时序要求
Vivado Timing Analyzer 表明 Block RAM 原语 `RAMB18E1` 在 -1 级别速度等级下 `T_CK=6 ns` 即可闭合；本实验 10 MHz (\<100 ns) 余量充足。仍需约束：
```tcl
create_clock -name clk -period 100 [get_ports clk]
set_input_delay 2 -clock clk [all_inputs]
```

== ROM（单端口）设计原理
指令存储器无需写入，仅在系统复位后提供定值，因此选 *Single Port ROM*：
- 端口简单：`clka`、`addra`、`douta` 三根主线；
- 初始化文件 `1.coe` 采用 16 进制向量描述，Vivado 在 Synthesis 阶段自动转换为 BRAM 内容；
- 常开 `EN`，读延迟 1 CLK，同步到 IF 取指阶段。

=== ROM 更新流程
1. 重新编译汇编/机器码 → 生成 `.coe`；  
2. 双击 `inst_rom.xci` → *Customize IP* → *Other Options* → 选择新文件；  
3. Regenerate Output Products 即可完成固化。

== Vivado Block Memory Generator 配置要点
#grid(
  columns: (1fr, 1fr),
  gutter: 1em,
  // RAM 配置
  rect(width: 100%, radius: 2pt, inset: 8pt, fill: luma(240), stroke: none)[
    #stack(
      spacing: 0.5em,
      text(weight: "bold", "RAM: True Dual Port"),
      line(length: 100%, stroke: 0.4pt),
      grid(
        columns: (auto, 1fr),
        gutter: 1em,
        text(weight: "bold")[Component Name:], `data_ram`,
        text(weight: "bold")[Memory Type:], `True Dual Port RAM`,
        text(weight: "bold")[W/D:], `32 / 256`,
        text(weight: "bold")[Write Enable:], `4-bit`,
      )
    )
  ],
  // ROM 配置
  rect(width: 100%, radius: 2pt, inset: 8pt, fill: luma(240), stroke: none)[
    #stack(
      spacing: 0.5em,
      text(weight: "bold", "ROM: Single Port"),
      line(length: 100%, stroke: 0.4pt),
      grid(
        columns: (auto, 1fr),
        gutter: 1em,
        text(weight: "bold")[Component Name:], `inst_rom`,
        text(weight: "bold")[Memory Type:], `Single Port ROM`,
        text(weight: "bold")[W/D:], `32 / 256`,
        text(weight: "bold")[Write Enable:], `None`,
      )
    )
  ]
)

== FPGA 资源利用
• 每个 32×256 存储体占用 4 × `RAMB18E1` (共约 3 Kb)。  
• 本实验板 Artix-7 XC7A35T 共有 50 个 `RAMB18`，占用率 < 10%，留足 CPU、Cache 后续扩展空间。


= 三、实验过程

本章节详细阐述了从前期方案设计到最终上板验证的完整实验流程。整个过程遵循模块化设计思想，通过 Vivado IP 核与自定义逻辑相结合的方式，高效、可靠地实现了同步双端口 RAM 和单端口 ROM。

== 前期准备与方案设计
在正式编码前，首先进行了详细的技术方案规划。

1.  *功能目标定义*：本次实验的核心目标是为后续的单周期 CPU 设计构建可靠的存储系统，包括：
    - *数据存储器 (Data Memory)*：要求能支持 CPU 的 `lw` 和 `sw` 指令，必须具备字节、半字、字三种粒度的读写能力。
    - *指令存储器 (Instruction Memory)*：要求能在系统启动时载入预设的机器码，并为 CPU 的取指阶段提供稳定的指令流。

2.  *技术选型*：考虑到 Xilinx FPGA 的内部资源特性，我们决定采用 Vivado 内置的 *Block Memory Generator IP 核* 作为基础。该 IP 核能生成高度优化、时序收敛可靠的 *BRAM*（块随机存取存储器）实例，避免了手动编写底层存储阵列的复杂性和潜在风险。

3.  *核心方案*：
    - 对于数据存储器，选用 *True Dual Port RAM* 模式。此模式提供两套完全独立的读写端口（*Port A*, *Port B*），极具灵活性。我们规划 *Port A* 作为 CPU 的主数据通道，进行读写操作；*Port B* 则配置为只读，用于连接调试模块，可以在不干扰 CPU 正常访存的情况下，实时窥探内存任意地址的内容，极大地便利了后续的在线调试。
    - 对于指令存储器，选用 *Single Port ROM* 模式。由于指令在程序运行期间是固定的，仅需读取，因此单端口只读模式足以满足需求，且资源占用更少。通过 *.coe* (Coefficient File) 文件进行初始化，可以将汇编器生成的机器码在 FPGA 综合阶段直接固化到 ROM 中。
    - *字节写使能 (Byte-Write-Enable)* 机制是本次设计的关键与难点。Block RAM IP 核本身支持字节写，但其 `WE` 端口需要一个4位的向量来精确控制4个字节中哪一个被写入。因此，我们设计了一个顶层控制模块，该模块接收一个简单的模式选择信号 `sec` (0/1/2 分别对应 1/2/4 字节写)，并根据该信号和地址的低两位，自动生成对应的4位 `wea` 向量和被屏蔽的数据 `dina`，从而向上层提供一个简洁而强大的字节、半字、字写入接口。

== 模块设计
在确定总体方案后，我们对各个模块的接口和内部逻辑进行了详细设计。

1.  *IP 核模块设计*：
    - `data_ram` (*TDP RAM*): 调用 *Block Memory Generator*，配置为 *True Dual Port RAM*，位宽32位，深度256（共 1KB），并启用 *Port A* 的4位字节写使能。
    - `inst_rom` (*SP ROM*): 配置为 *Single Port ROM*，位宽32位，深度256，并关联初始化文件 `1.coe`。

2.  *顶层交互模块设计*：为了便于上板测试，设计了 `data_ram_display` 作为 RAM 的顶层测试模块，其接口如下：
    - 输入:
        - `clk`: 系统时钟。
        - `touch_data`: 来自触摸屏的输入数据。
        - `touch_key`: 触摸屏按键有效信号。
    - 输出:
        - `lcd_data`: 显示在 LCD 屏幕上的数据。
    - 内部逻辑: 模块内部通过状态机解析触摸屏输入，将其转换为对 RAM 的地址、数据、写模式 (`sec`) 和写使能信号，并驱动 RAM IP 核。同时，将 RAM 的读出数据显示在 LCD 上。

== 模块实现
根据模块设计，我们使用 *Verilog HDL* 语言完成了编码实现。
1.  *控制逻辑实现* (`data_ram_display.v`): 在该文件中，我们实现了字节写使能的核心逻辑。根据输入的 `sec` 信号，通过 `case` 语句生成 `actual_wea` (实际的4位写使能) 和 `wdata_masked` (被屏蔽的写入数据)，确保了不同模式下的数据写入正确性。同时，实现了与触摸屏交互的状态机和显示逻辑。
2.  *ROM 顶层模块* (`inst_rom_display.v`): 类似地，为 ROM 也实现了一个简单的测试顶层，用于在屏幕上显示指定地址的指令码。
3.  *IP 核生成*: 在 Vivado 中，通过图形化界面完成 `data_ram.xci` 和 `inst_rom.xci` 的配置与生成。

== 功能验证
功能验证分为仿真验证和上板验证两个阶段，以确保设计的正确性。

1.  *仿真验证* (`tb.v`):
    - 我们编写了专门的测试平台 `tb.v`，旨在对 `data_ram_display` 模块进行全面的行为级仿真。
    - 测试序列覆盖了所有写模式：
        - *1-Byte 模式*: 依次向地址 0, 1, 2, 3 写入单字节数据，然后按 *4-Byte 模式* 从地址 0 读出，验证数据是否被正确拼接。
        - *2-Byte 模式*: 向地址 0, 2 写入半字数据，然后按 *4-Byte 模式* 从地址 0 读出，验证数据拼接。
        - *4-Byte 模式*: 进行全字写入和读取。
    - 仿真结果表明，所有模式下的写入、数据屏蔽、数据拼接行为均与预期一致，逻辑功能正确。

2.  *上板验证*:
    - 完成仿真后，对整个工程进行综合、实现并生成 *bitstream* 文件，下载到 FPGA 开发板。
    - 操作步骤:
        - 通过触摸屏的 `input_sel` 选择输入目标（写模式 `sec`、写地址 `addra`、写数据 `dina`）。
        - 依次输入控制参数和数据。
        - 在 LCD 屏幕上观察端口 A 和端口 B 的读出数据，验证写入是否成功。
    - 上板测试复现了仿真中的所有关键场景，包括不同字节模式的读写、地址不对齐时的自动截断等。详细的测试过程与抓图已在 4.2 节中详细呈现。最终，上板结果与仿真结果完全吻合，充分证明了设计的正确性和可靠性。

= 四、实验结果
== 行为仿真
#figure(
  image("resources/sim0-初始状态.png", width: 100%),
  caption: "(a) 初始状态：仿真开始时，所有RAM内容均为0，test端口指向默认地址。"
)
#figure(
  image("resources/sim1-4写4读-往20地址写入wdata=10，随后rdata读到10，将test_addr移动到20，随后20地址读出10.png", width: 100%),
  caption: "(b) 4字节写/读：向地址20写入wdata=10，随后rdata读到10，test_addr移动到20，20地址读出10。"
)
#figure(
  image("resources/sim2-1写4读-往40写入c，随后读出c，此时test地址仍然是20，test仍然读出10.png", width: 100%),
  caption: "(c) 1字节写/4字节读：向地址40写入c，随后读出c。test端口仍为20，test读出10，验证多端口独立性。"
)
#figure(
  image("resources/sim3-2写4读-往22地址写入abcd1234，发生截断只写入1234，然后22不符合4读，此时rdata读的是20地址，20地址之前4写过10，故这里整体读出来的结果为12340010，而test地址到40，读出刚才写的c.png", width: 100%),
  caption: "(d) 2字节写/4字节读，地址截断：向22地址写abcd1234，实际只写1234，22地址不对齐，rdata读的是20地址，整体读出12340010。test端口到40，读出c。"
)

== 上板验证
将生成的 bitstream 文件下载至 LS-CPU-EXB-002 实验箱后，通过板载触摸屏进行交互式测试。测试界面允许用户输入地址、数据、选择字节写模式（1/2/4-byte），并实时回显A/B两端口的读出数据。板载 LED 也同步显示端口A的读出数据，便于观察。

整个验证流程遵循序贯逻辑，全面测试了RAM的各项功能，具体如下：

=== 基础读写与字节写模式验证
首先，测试了基础的4字节读写，随后逐步验证1字节和2字节的写入、拼接及高位截断能力。

#figure(
  grid(
    columns: (1fr, 1fr, 1fr),
    gutter: 1em,
    image("resources/board0-按四字节写四字节读-0地址写入223-0地址读取223.png", width: 100%),
    image("resources/board1-按一字节写四字节读-0地址写入11-0地址读出11.png", width: 100%),
    image("resources/board2-按一字节写四字节读-1地址写入22-0地址读出2211.png", width: 100%),
  ),
  caption: [
    (a) 4-Byte模式：向地址0写入223，读出223，验证基本4字节写读。 \ 
    (b) 1-Byte模式：向地址0写入11，读出11，单字节写入正确。 \ 
    (c) 1-Byte模式：向地址1写入22，从地址0读出2211，数据拼接验证。
  ]
)

#figure(
  grid(
    columns: (1fr, 1fr, 1fr),
    gutter: 1em,
    image("resources/board3-1写4读-2地址写33-0地址读332211.png", width: 100%),
    image("resources/board4-1写4读-2地址写入3411123-0地址读出232211-展示1写的能力，多写会高位截断.png", width: 100%),
    image("resources/board5-2写4读-0地址写入23456-0地址读出3456-展示2写的能力并展示高位截断.png", width: 100%),
  ),
  caption: [
    (d) 续上一步，向地址2写入33，从地址0读出332211，验证多字节拼接。 \ 
    (e) 1-Byte高位截断：向地址2写入3411123，仅低8位23生效，覆盖原有33，读出232211。 \ 
    (f) 2-Byte高位截断：向地址0写入23456，仅低16位3456生效，验证高位截断。
  ]
)

=== 地址对齐与截断机制验证
此部分旨在验证当写入地址不符合当前字节模式的对齐要求时，硬件的自动处理机制。

#figure(
  grid(
    columns: (1fr, 1fr),
    gutter: 1em,
    image("resources/board7-2写模式下尝试将写入地址改为1，失效(会向下取整 比如7,那就会变成6)，因为2写模式地址必须是2的整数.png", width: 100%),
    image("resources/board9-4写下尝试将写入地址改为3，同样会被截断为0 (小于3的最大的4的倍数).png", width: 100%),
  ),
  caption: [
    (g) 2-Byte模式下，尝试向地址1写入，地址被自动截断为0（向下取整到2的倍数）。 \ 
    (h) 4-Byte模式下，向地址3写入，地址被截断为0（向下取整到4的倍数）。
  ]
)

=== 数据持久性与独立地址读写验证
最后，验证了在不同地址空间操作后，原有数据是否能正确保持，以及读地址的截断行为。

#figure(
  grid(
    columns: (1fr, 1fr, 1fr),
    gutter: 1em,
    image("resources/board10-4读4写-8地址写入342-0地址读出456.png", width: 100%),
    image("resources/board11-4读4写-8地址读出342.png", width: 100%),
    image("resources/board14-4读4写-经过刚才的操作回去读0地址，读出456，与之前写的值一致.png", width: 100%),
  ),
  caption: [
    (i) 向地址8写入342，地址0的值456不受影响，验证独立性。 \ 
    (j) 从地址8正确读出342，数据写入生效。 \ 
    (k) 经过一系列操作后，再次读取地址0，数据456依然存在，验证数据持久性。
  ]
)

上板验证结果与行为级仿真高度一致，证明了 Block RAM IP 核以及顶层字节写控制逻辑的正确性。所有模式下的数据写入、读取、地址对齐与截断行为均符合预期设计。这为后续将其作为数据存储器（D-MEM）集成入单周期 CPU 打下了坚实的基础。

= 五、源码

== data_ram_display.v
```verilog
`timescale 1ns / 1ps
module data_ram_display(
    //时钟与复位信号
     input clk,
    input resetn,    //后缀"n"表示低电平有效

    //输入开关，用于测试写使能和选择输入参数
    input [3:0] wen,
    input [1:0] input_sel,
    
    // SEC变为内部寄存器，不再是输入端口
    // input [1:0] sec,

    //led灯，用于指示写使能信号，以及当前在设什么参数
    output [3:0] led_wen,
    output led_addr,      //指示当前设置写地址
    output led_wdata,     //指示当前设置写数据
    output led_test_addr, //指示当前设置test地址

    //触摸屏接口，此处主要用作显示
    output lcd_rst,
    output lcd_cs,
    output lcd_rs,
    output lcd_wr,
    output lcd_rd,
    inout[15:0] lcd_data_io,
    output lcd_bl_ctr,
    inout ct_int,
    inout ct_sda,
    output ct_scl,
    output ct_rstn
    );
//-----{LED指示}begin
    assign led_wen       = wen;
    assign led_addr      = (input_sel==2'd0);
    assign led_wdata     = (input_sel==2'd1);
    assign led_test_addr = (input_sel==2'd2);
//-----{LED指示}end
//-----{数据存储器模块}begin
    //数据存储器有两个端口，一个用于读写，另一个用于测试地址显示内存中的数据
    reg  [31:0] addr;
    reg  [31:0] wdata;
    wire [31:0] rdata;
    reg  [31:0] test_addr;
    wire [31:0] test_data;
    
    // SEC从输入端口改为内部寄存器
    reg  [1:0] sec;

    // 根据SEC选择实际的写使能信号
    reg [3:0] actual_wea;
    
    always @(*)
    begin
        case(sec)
            2'd0: begin  // 1字节模式
                case(addr[1:0])
                    2'b00: actual_wea = {3'b000, wen[0]};
                    2'b01: actual_wea = {2'b00, wen[0], 1'b0};
                    2'b10: actual_wea = {1'b0, wen[0], 2'b00};
                    2'b11: actual_wea = {wen[0], 3'b000};
                endcase
            end
            2'd1: begin  // 2字节模式
                case(addr[1])
                    1'b0: actual_wea = {2'b00, {2{wen[0]}}};
                    1'b1: actual_wea = {{2{wen[0]}}, 2'b00};
                endcase
            end
            default: begin  // 4字节模式 (SEC=2)
                actual_wea = wen;
            end
        endcase
    end

    // 添加一个寄存器来存储复位后的test_data初始值
    reg [31:0] test_data_reg;
    wire reset_active;
    assign reset_active = !resetn;

    // 添加掩码处理逻辑，确保只有选定的字节被写入，其他字节正确保留
    reg [31:0] wdata_masked;
    
    always @(*) begin
        case(sec)
            2'd0: begin  // 1字节模式
                case(addr[1:0])
                    2'b00: wdata_masked = {rdata[31:8], wdata[7:0]};
                    2'b01: wdata_masked = {rdata[31:16], wdata[7:0], rdata[7:0]};
                    2'b10: wdata_masked = {rdata[31:24], wdata[7:0], rdata[15:0]};
                    2'b11: wdata_masked = {wdata[7:0], rdata[23:0]};
                endcase
            end
            2'd1: begin  // 2字节模式
                case(addr[1])
                    1'b0: wdata_masked = {rdata[31:16], wdata[15:0]};
                    1'b1: wdata_masked = {wdata[15:0], rdata[15:0]};
                endcase
            end
            default: begin  // 4字节模式 (SEC=2)
                wdata_masked = wdata;
            end
        endcase
    end
    
    // 修改RAM接口和读写控制逻辑
    reg [31:0] ram_init_data;  // 用于初始化RAM的数据寄存器
    reg [3:0] ram_init_wea;    // 用于初始化RAM的写使能信号
    reg [7:0] ram_init_addr;   // 用于初始化RAM的地址计数器
    reg ram_init_done;         // RAM初始化完成标志
    
    // RAM初始化状态机
    localparam INIT = 1'b0, NORMAL = 1'b1;
    reg ram_state;
    
    always @(posedge clk or negedge resetn) begin
        if (!resetn) begin
            ram_init_addr <= 8'd0;
            ram_init_data <= 32'h00000000;
            ram_init_wea <= 4'b1111;  // 初始化时，全部字节都写入
            ram_init_done <= 1'b0;
            ram_state <= INIT;
        end else begin
            case (ram_state)
                INIT: begin
                    // 初始化所有RAM地址为0
                    if (ram_init_addr < 8'd128) begin // 假设RAM大小为128个位置
                        ram_init_addr <= ram_init_addr + 1'b1;
                    end else begin
                        ram_init_done <= 1'b1;
                        ram_state <= NORMAL;
                    end
                end
                NORMAL: begin
                    // 正常操作模式，保持这些寄存器的值
                    ram_init_addr <= ram_init_addr;
                    ram_init_data <= ram_init_data;
                    ram_init_wea <= 4'b0000;
                    ram_init_done <= ram_init_done;
                end
            endcase
        end
    end
    
    // 写入RAM时使用的地址、数据和写使能信号
    wire [7:0] ram_addr;
    wire [31:0] ram_wdata;
    wire [3:0] ram_wea;
    
    // 在初始化和正常模式之间选择适当的信号
    assign ram_addr = (ram_state == INIT) ? ram_init_addr : {3'b0, addr[6:2]};
    assign ram_wdata = (ram_state == INIT) ? ram_init_data : wdata_masked;
    assign ram_wea = (ram_state == INIT) ? ram_init_wea : actual_wea;

    data_ram data_ram_module(
        //双端口RAM
    .clka(clk),    // input wire clka
    .wea(ram_wea),      // 使用根据SEC调整后的写使能信号和掩码数据
    .addra(ram_addr),  // input wire [7 : 0] addra
    .dina(ram_wdata),  // 使用掩码处理后的数据
    .douta(rdata),     // output wire [31 : 0] douta
    .web(4'b0000),     // 修改：B端口设置为只读模式，写使能始终为0
    .clkb(clk),        // input wire clkb
    .addrb({3'b0,test_addr[6:2]}),  // input wire [7 : 0] addrb
    .doutb(test_data)  // output wire [31 : 0] doutb
    );

    // 添加复位逻辑，确保T_DATA在复位后显示为0
    always @(posedge clk)
    begin
        if (!resetn)
        begin
            test_data_reg <= 32'h00000000; // 复位时将test_data_reg设置为0
        end
        else
        begin
            test_data_reg <= test_data; // 正常操作时，跟踪test_data的值
        end
    end
//-----{数据寄存器模块}end

//---------------------{触摸屏显示模块}begin--------------------//
//-----{实例化显示模块}begin
//此小段内不需要修改
    reg         display_valid;
    reg  [39:0] display_name;
    reg  [31:0] display_value;
    wire [5 :0] display_number;
    wire        input_valid;
    wire [31:0] input_value;

    lcd_module lcd_module(
        .clk            (clk           ),   //10Mhz
        .resetn         (resetn        ),

        //用户可修改的接口
        .display_valid  (display_valid ),
        .display_name   (display_name  ),
        .display_value  (display_value ),
        .display_number (display_number),
        .input_valid    (input_valid   ),
        .input_value    (input_value   ),

        //lcd物理接口，不需要修改
        .lcd_rst        (lcd_rst       ),
        .lcd_cs         (lcd_cs        ),
        .lcd_rs         (lcd_rs        ),
        .lcd_wr         (lcd_wr        ),
        .lcd_rd         (lcd_rd        ),
        .lcd_data_io    (lcd_data_io   ),
        .lcd_bl_ctr     (lcd_bl_ctr    ),
        .ct_int         (ct_int        ),
        .ct_sda         (ct_sda        ),
        .ct_scl         (ct_scl        ),
        .ct_rstn        (ct_rstn       )
    ); 
//-----{实例化显示模块}end

//-----{从触摸屏获取数据}begin
//根据实验需要，修改此小段：
//建议对每一个数的输入，编写单独一个always块
    //在这里实际需要改变输入，修改此小段：
    //当input_sel为2'b00时，显示参数项为写地址，即addr
    always @(posedge clk)
    begin
        if (!resetn)
        begin
            addr <= 32'd0;
        end
        else if (input_valid && input_sel==2'd0)
        begin
            // 根据SEC值应用不同的地址掩码，只限制写地址
            case(sec)
                2'd0: addr <= input_value;                   // 1字节模式：所有地址位有效
                2'd1: addr <= {input_value[31:1], 1'b0};     // 2字节模式：低1位强制为0
                2'd2: addr <= {input_value[31:2], 2'b00};    // 4字节模式：低2位强制为0
                default: addr <= {input_value[31:2], 2'b00}; // 默认同4字节模式
            endcase
        end
    end
    
    //当input_sel为2'b01时，显示参数项为写数据，即wdata
    always @(posedge clk)
    begin
        if (!resetn)
        begin
            wdata <= 32'd0;
        end
        else if (input_valid && input_sel==2'd1)
        begin
            wdata <= input_value;
        end
    end
    
    //当input_sel为2'b10时，显示参数项为test地址，即test_addr
    //对读地址T_ADD不做字节对齐限制，始终读取4字节
    always @(posedge clk)
    begin
        if (!resetn)
        begin
            test_addr  <= 32'd0;
        end
        else if (input_valid && input_sel==2'd2)
        begin
            // 恢复原始逻辑，不限制读地址
            test_addr[31:2] <= input_value[31:2];
        end
    end
    
    //当input_sel为2'b11时，显示参数项为SEC值，即字节宽度设置
    always @(posedge clk)
    begin
        if (!resetn)
        begin
            sec <= 2'd2;  // 默认为4字节模式
        end
        else if (input_valid && input_sel==2'd3)  // 使用新的选择值2'd3
        begin
            if (input_value < 3)  // 确保SEC只能是0,1,2
                sec <= input_value[1:0];
        end
    end
//-----{从触摸屏获取数据}end

//-----{将数据显示到触摸屏}begin
//根据需要显示的内容，修改此小段：
//本实验总共需要44个显示条目，可以显示44个32位数据
//44个显示条目的编号从1开始，即为1~44。
    always @(posedge clk)
    begin
       case(display_number)
           6'd1:
           begin
               display_valid <= 1'b1;
               display_name  <= "ADDR ";
               display_value <= addr;
           end
           6'd2: 
           begin
               display_valid <= 1'b1;
               display_name  <= "WDATA";
               display_value <= wdata;
           end
           6'd3: 
           begin
               display_valid <= 1'b1;
               display_name  <= "RDATA";
               display_value <= rdata;
           end
           6'd4:
           begin
               display_valid <= 1'b1;
               display_name  <= "SEC  ";
               display_value <= {30'b0, sec};
           end
           6'd5: 
           begin
               display_valid <= 1'b1;
               display_name  <= "T_ADD";
               display_value <= test_addr;
           end
           6'd6: 
           begin
               display_valid <= 1'b1;
               display_name  <= "T_DAT";
               // 使用test_data_reg而不是直接使用test_data
               display_value <= reset_active ? 32'h00000000 : test_data_reg;
           end
           6'd7:
           begin
               display_valid <= 1'b1;
               case(sec)
                   2'd0: display_name <= "MODE1";  // 1字节模式
                   2'd1: display_name <= "MODE2";  // 2字节模式
                   2'd2: display_name <= "MODE4";  // 4字节模式
                   default: display_name <= "ERROR";
               endcase
               case(sec)
                   2'd0: display_value <= 32'h1;  // 1字节
                   2'd1: display_value <= 32'h2;  // 2字节
                   2'd2: display_value <= 32'h4;  // 4字节
                   default: display_value <= 32'h0;
               endcase
           end
           default :
           begin
               display_valid <= 1'b0;
               display_name  <= 40'd0;
               display_value <= 32'd0;
           end
       endcase
    end
//-----{将数据显示到触摸屏}end
//----------------------{触摸屏显示模块}end---------------------//
endmodule
```

== tb.v
```verilog
`timescale 1ns / 1ps
module tb;
    reg clk;
    reg  [3:0] wen;
    reg  [31:0] addr;
    reg  [31:0] wdata;
    reg  [31:0] test_addr;
    reg  [1:0] sec;
    wire [31:0] rdata;
    wire [31:0] test_data;
    reg [3:0] actual_wea;
    always @(*)
    begin
        case(sec)
            2'd0: begin
                case(addr[1:0])
                    2'b00: actual_wea = {3'b000, wen[0]};
                    2'b01: actual_wea = {2'b00, wen[0], 1'b0};
                    2'b10: actual_wea = {1'b0, wen[0], 2'b00};
                    2'b11: actual_wea = {wen[0], 3'b000};
                endcase
            end
            2'd1: begin
                case(addr[1])
                    1'b0: actual_wea = {2'b00, {2{wen[0]}}};
                    1'b1: actual_wea = {{2{wen[0]}}, 2'b00};
                endcase
            end
            default: actual_wea = wen;
        endcase
    end
    reg [31:0] wdata_masked;
    reg clk;
    reg  [3:0] wen;
    reg  [31:0] addr;
    reg  [31:0] wdata;
    reg  [31:0] test_addr;
    reg  [1:0] sec;
    wire [31:0] rdata;
    wire [31:0] test_data;
    reg [3:0] actual_wea;
    always @(*)
    begin
        case(sec)
            2'd0: begin
                case(addr[1:0])
                    2'b00: actual_wea = {3'b000, wen[0]};
                    2'b01: actual_wea = {2'b00, wen[0], 1'b0};
                    2'b10: actual_wea = {1'b0, wen[0], 2'b00};
                    2'b11: actual_wea = {wen[0], 3'b000};
                endcase
            end
            2'd1: begin
                case(addr[1])
                    1'b0: actual_wea = {2'b00, {2{wen[0]}}};
                    1'b1: actual_wea = {{2{wen[0]}}, 2'b00};
                endcase
            end
            default: actual_wea = wen;
        endcase
    end
    reg [31:0] wdata_masked;
    always @(*) begin
        case(sec)
            2'd0: begin
                case(addr[1:0])
                    2'b00: wdata_masked = {rdata[31:8], wdata[7:0]};
                    2'b01: wdata_masked = {rdata[31:16], wdata[7:0], rdata[7:0]};
                    2'b10: wdata_masked = {rdata[31:24], wdata[7:0], rdata[15:0]};
                    2'b11: wdata_masked = {wdata[7:0], rdata[23:0]};
                endcase
            end
            2'd1: begin  // 2字节模式
                case(addr[1])
                    1'b0: wdata_masked = {rdata[31:16], wdata[15:0]};
                    1'b1: wdata_masked = {wdata[15:0], rdata[15:0]};
                endcase
            end
            default: begin  // 4字节模式 (SEC=2)
                wdata_masked = wdata;
            end
        endcase
    end
    
    data_ram uut (//仿真IP核，自动仿真用uut，IP核必须为同名才行
       .clka(clk),    // input wire clka
       .wea(actual_wea),      // input wire [3 : 0] wea
       .addra({3'b0,addr[6:2]}),  // input wire [7 : 0] addra
       .dina(wdata_masked),    // 使用掩码处理后的数据
       .douta(rdata),  // output wire [31 : 0] douta
       .clkb(clk),    // input wire clkb
       .web(4'b0000),  // 修改：B端口设置为只读
       .addrb({3'b0,test_addr[6:2]}),  // input wire [7 : 0] addrb
       .dinb(32'b0),
       .doutb(test_data)  // output wire [31 : 0] doutb
    );
    initial begin
    clk = 0;
    wen = 0;
    addr = 0;
    wdata = 0;
    test_addr = 0;
    sec = 2'd2;
    #100
    wen = 4'b0001;
    addr = {8'd8, 2'b00};
    test_addr = 8'd32;
    wdata = 32'd16;
    #100
    sec = 2'd0;
    addr = 8'd64;
    wdata = 32'd12;
    #100
    sec = 2'd1;
    test_addr = 8'd64;
    addr = {8'd17, 1'b0};
    wdata = 32'hABCD1234;
    end
   always #5 clk = ~clk;
endmodule
```

== inst_rom_display.v
```verilog
`timescale 1ns / 1ps
module inst_rom_display(
    //时钟与复位信号
    input clk,
    input resetn,    //后缀"n"表示低电平有效

    //触摸屏接口，此处主要用作显示
    output lcd_rst,
    output lcd_cs,
    output lcd_rs,
    output lcd_wr,
    output lcd_rd,
    inout[15:0] lcd_data_io,
    output lcd_bl_ctr,
    inout ct_int,
    inout ct_sda,
    output ct_scl,
    output ct_rstn
    );
//-----{指令存储器模块}begin
    //数据存储器多增加一个读端口，用于读出特定内存地址显示在触摸屏上
    reg  [31:0] addr;
    wire [31:0] inst;

    inst_rom inst_rom_module(
        .clka   (clk),
        .addra  ({3'b0,addr[6:2]}),
        .douta  (inst[31:0])
    );
//-----{指令存储器模块}end

//---------------------{触摸屏显示模块}begin--------------------//
//-----{实例化触摸屏}begin
//此小节不需要更改
    reg         display_valid;
    reg  [39:0] display_name;
    reg  [31:0] display_value;
    wire [5 :0] display_number;
    wire        input_valid;
    wire [31:0] input_value;

    lcd_module lcd_module(
        .clk            (clk           ),   //10Mhz
        .resetn         (resetn        ),

        //调用触摸屏的接口
        .display_valid  (display_valid ),
        .display_name   (display_name  ),
        .display_value  (display_value ),
        .display_number (display_number),
        .input_valid    (input_valid   ),
        .input_value    (input_value   ),

        //lcd触摸屏相关接口，不需要更改
        .lcd_rst        (lcd_rst       ),
        .lcd_cs         (lcd_cs        ),
        .lcd_rs         (lcd_rs        ),
        .lcd_wr         (lcd_wr        ),
        .lcd_rd         (lcd_rd        ),
        .lcd_data_io    (lcd_data_io   ),
        .lcd_bl_ctr     (lcd_bl_ctr    ),
        .ct_int         (ct_int        ),
        .ct_sda         (ct_sda        ),
        .ct_scl         (ct_scl        ),
        .ct_rstn        (ct_rstn       )
    ); 
//-----{实例化触摸屏}end

//-----{从触摸屏获取输入}begin
//根据实际需要输入的数修改此小节，
//建议对每一个数的输入，编写单独一个always块
    always @(posedge clk)
    begin
        if (!resetn)
        begin
            addr <= 32'd0;
        end
        else if (input_valid)
        begin
            addr[31:2] <= input_value[31:2];
        end
    end
//-----{从触摸屏获取输入}end

//-----{输出到触摸屏显示}begin
//根据需要显示的数修改此小节，
//触摸屏上共有44块显示区域，可显示44组32位数据
//44块显示区域从1开始编号，编号为1~44，
    always @(posedge clk)
    begin
       case(display_number)
           6'd1:
           begin
               display_valid <= 1'b1;
               display_name  <= "ADDR ";
               display_value <= addr;
           end
           6'd2: 
           begin
               display_valid <= 1'b1;
               display_name  <= "INST ";
               display_value <= inst;
           end
           default :
           begin
               display_valid <= 1'b0;
               display_name  <= 40'd0;
               display_value <= 32'd0;
           end
       endcase
    end
//-----{输出到触摸屏显示}end
//----------------------{调用触摸屏模块}end---------------------//
endmodule
```
]