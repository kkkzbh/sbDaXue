#import "report_template.typ": report

#show: report.with(
  header-text: "实验六：单周期 CPU 设计与实现",
  show-abstract: false,
  show-toc: false,
)

= 实验目的

本实验旨在通过设计和实现一个单周期 MIPS CPU 来达到以下目标：

+ 理解 MIPS 指令结构，理解 MIPS 指令集中常用指令的功能和编码，学会对这些
+ 了解熟悉 MIPS 体系的处理器结构，如延迟槽，哈佛结构的概念。
+ 熟悉并掌握单周期 CPU 的原理和设计。
+ 进一步加强运用 verilog 语言进行电路设计的能力。
+ 为后续设计多周期 cpu 的实验打下基础。

= 实验原理

== MIPS 指令格式

MIPS 指令集包含三种基本格式：

*R 型指令（寄存器型）：*
```
[31:26] [25:21] [20:16] [15:11] [10:6] [5:0]
  op     rs      rt      rd     shamt  funct
```

*I 型指令（立即数型）：*
```
[31:26] [25:21] [20:16] [15:0]
  op     rs      rt    immediate
```

*J 型指令（跳转型）：*
```
[31:26] [25:0]
  op    address
```

== 单周期 CPU 架构

单周期 CPU 在一个时钟周期内完成一条指令的执行，主要组成部件包括：

1. *程序计数器（PC）*：存储当前指令地址
2. *指令存储器*：存储程序指令
3. *寄存器文件*：32个通用寄存器
4. *ALU*：算术逻辑运算单元
5. *数据存储器*：存储数据
6. *控制单元*：产生各种控制信号

#figure(
  image("cpujg.svg", width: 78%),
  caption: [单周期CPU结构图]
)

== 基础指令特性归纳

#figure(
  table(
    columns: 8,
    align: center,
    [*指令*], [*类型*], [*操作码*], [*RegWre*], [*RegDst*], [*AluSrcA*], [*AluSrcB*], [*ALU操作*],
    [ADDU], [R], [000000], [1], [1], [0], [0], [0001],
    [SUBU], [R], [000000], [1], [1], [0], [0], [0010],
    [SLT], [R], [000000], [1], [1], [0], [0], [0011],
    [AND], [R], [000000], [1], [1], [0], [0], [0100],
    [NOR], [R], [000000], [1], [1], [0], [0], [0101],
    [OR], [R], [000000], [1], [1], [0], [0], [0110],
    [XOR], [R], [000000], [1], [1], [0], [0], [0111],
    [SLL], [R], [000000], [1], [1], [1], [0], [1000],
    [SRL], [R], [000000], [1], [1], [1], [0], [1001],
    [ADDIU], [I], [001001], [1], [0], [0], [1], [0001],
    [SLTI], [I], [001010], [1], [0], [0], [1], [0011],
    [LW], [I], [100011], [1], [0], [0], [1], [0001],
    [SW], [I], [101011], [0], [0], [0], [1], [0001],
    [BEQ], [I], [000100], [0], [0], [0], [0], [0010],
    [BNE], [I], [000101], [0], [0], [0], [0], [0010],
    [J], [J], [000010], [0], [0], [0], [0], [0000],
  ),
  caption: [基础指令特性归纳表],
  kind: table,
)

== 控制信号说明

- *RegWre*：寄存器写使能，1表示允许写入寄存器
- *RegDst*：写寄存器地址选择，0选择rt，1选择rd
- *AluSrcA*：ALU操作数A选择，0选择寄存器数据，1选择移位量
- *AluSrcB*：ALU操作数B选择，0选择寄存器数据，1选择立即数
- *ExtSel*：立即数扩展选择，0为零扩展，1为符号扩展
- *mRD/mWR*：数据存储器读/写使能
- *DBDataSrc*：写回数据选择，0选择ALU结果，1选择存储器数据
- *PCSrc*：PC更新方式选择

= 实验过程

== 模块设计

本实验设计了以下主要模块：

1. *SingleCycleCPU*：顶层CPU模块，连接各个子模块
2. *PC*：程序计数器模块，管理指令地址
3. *instructionMemory*：指令存储器，包含预设的测试程序
4. *regfile*：寄存器文件，实现32个通用寄存器
5. *Alu*：算术逻辑单元，执行各种运算
6. *ControlUnit*：控制单元，根据指令生成控制信号
7. *DataMemory*：数据存储器，支持加载和存储操作
8. *SignZeroExtend*：立即数扩展模块

=== SingleCycleCPU 顶层模块
- 职责：作为系统集成层，将 PC、指令存储器、寄存器文件、ALU、数据存储器及控制单元联结成完整数据通路。
- 关键接口：
  - `clk`、`Reset`：全局时钟与复位。
  - `test_addr` / `test_addr1`：用于在板上实时访问 DataMemory 与 RegFile 的调试端口。
  - `test_data` / `test_data1`：对应读取出的 32-bit 调试数据。
- 运行流程：
 1. 时钟上升沿 PC 输出地址 → 指令存储器读取指令。
 2. ControlUnit 根据 `opcode/func` 生成控制信号。
 3. RegFile/ALU/DataMemory 在同一周期内完成取数、运算、访存与结果写回。
 4. `PCSrc` 选择下条 PC（顺序、分支或跳转）。

=== PC 模块
- 32-bit 寄存器，在时钟上升沿根据 `PCWre` 决定是否写入。
- `PCSrc` 取值：
- - 0：PC+4（顺序执行）
- - 1：PC+4+SignExt(Imm)\<\<2（分支）
- - 2：\{PC[31:28], Addr26, 2'b00\}（Jump）
- 复位时置 0，`halt` 指令 (`opcode=0x3F`) 通过将 `PCWre` 置 0 停止更新。

=== instructionMemory
- 256×32 ROM，哈佛结构独立于数据总线。
- 支持字地址访问：`addr[31:2]` 用作索引，低两位补 0 保证字对齐。
- 通过参数化 `mem[]` 直接在 Verilog 源中初始化 43 条测试指令，便于仿真与上板。

=== regfile
- 32×32 通用寄存器，双端异步读、单端同步写。
- 写端口：时钟上升沿且 `RegWre` 有效时写入 `wdata` 至 `waddr`（由 `RegDst` 选择 rd/rt）。
- 读端口：组合逻辑形式，`raddr1/2` 变化立即反映至 `rdata1/2`，满足单周期时序要求。

=== ALU
- 支持 9 类运算：加、减、SLT、AND、NOR、OR、XOR、SLL、SRL。
- 操作数选择：
  - `AluSrcA`：0→`rs` 数据，1→`sa` (移位量)。
  - `AluSrcB`：0→`rt` 数据，1→扩展立即数。
- `Alu_Op`（4-bit）编码与控制单元一一对应，例如 `0001` 为无符号加法、`0010` 为无符号减法。
- 额外输出 `zero` 标志用于 BEQ/BNE 分支判定。

=== ControlUnit
- 纯组合逻辑，根据 `opcode` 与 `func` 立即给出全部控制信号。
- 分支类指令 (BEQ/BNE) 通过 `zero` 决定 `PCSrc`，Jump 指令直接置 `PCSrc=2`。
- `halt` 指令令 `PCWre=0`，并关闭访存与寄存器写入。

=== DataMemory
- 256×32 字地址 RAM，支持同步读写：
  - `mRD` 为 1 时读取 `DataOut`，并通过 `DBDataSrc` 选入写回通路。
  - `mWR` 为 1 时将 `DataIn` 在时钟上升沿写入 `DAddr` 对应地址。
- `DB` 为外部统一写回数据线（ALU 结果或读出的存储器数据）。

=== SignZeroExtend
- 根据 `ExtSel` 选择符号扩展或零扩展，将 16-bit 立即数扩展至 32-bit。
- 分支/跳转位移统一在 PC 模块内再左移两位，保持字对齐。

== CPU支持指令详情

本CPU所支持的指令集如下表所示，涵盖了R型、I型和J型指令，能够完成基本的算术逻辑、内存访问和分支跳转功能。

#figure(
  image("supported_instructions.svg", width: 100%),
  caption: [CPU支持指令详情表],
  kind: table,
)

== 测试程序设计与预期结果

=== 测试程序

设计了一个综合测试程序，包含42条指令，测试所有实现的指令类型：

#figure(
  table(
    columns: 4,
    align: left,
    [*地址*], [*汇编指令*], [*机器码(hex)*], [*功能说明*],
    [0], [addi \$30, \$0, 0], [241E0000], [初始化基址],
    [1], [addi \$1, \$0, 5], [24010005], [设置\$1=5],
    [2], [addi \$2, \$0, 7], [24020007], [设置\$2=7],
    [3], [addu \$3, \$1, \$2], [00221821], [\$3=\$1+\$2],
    [4], [sw \$3, 16(\$30)], [AFC30010], [存MEM16],
    [5], [subu \$4, \$2, \$1], [00412023], [\$4=\$2-\$1],
    [6], [sw \$4, 17(\$30)], [AFC40011], [存MEM17],
    [7], [slt \$5, \$1, \$2], [0022282A], [\$5=(\$1\<\$2)],
    [8], [sw \$5, 18(\$30)], [AFC50012], [存MEM18],
    [9], [and \$6, \$1, \$2], [00223024], [\$6=\$1\&\$2],
    [10], [sw \$6, 19(\$30)], [AFC60013], [存MEM19],
    [11], [nor \$7, \$1, \$2], [00223827], [\$7=~(\$1\|\$2)],
    [12], [sw \$7, 20(\$30)], [AFC70014], [存MEM20],
    [13], [or \$8, \$1, \$2], [00224025], [\$8=\$1\|\$2],
  ),
  caption: [测试汇编程序（0-19）],
  kind: table,
)

#pagebreak()

#figure(
  table(
    columns: 4,
    align: left,
    [*地址*], [*汇编指令*], [*机器码(hex)*], [*功能说明*],
    [14], [sw \$8, 21(\$30)], [AFC80015], [存MEM21],
    [15], [xor \$9, \$1, \$2], [00224826], [\$9=\$1\^\$2],
    [16], [sw \$9, 22(\$30)], [AFC90016], [存MEM22],
    [17], [sll \$10, \$1, 2], [00015080], [\$10=\$1\<\<2],
    [18], [sw \$10, 23(\$30)], [AFCA0017], [存MEM23],
    [19], [srl \$11, \$2, 1], [00025842], [\$11=\$2>>1],
    [20], [sw \$11, 24(\$30)], [AFCB0018], [存MEM24],
    [21], [addiu \$12, \$0, 100], [240C0064], [\$12=100],
    [22], [sw \$12, 25(\$30)], [AFCC0019], [存MEM25],
    [23], [slti \$13, \$1, 10], [282D000A], [设置\$13],
    [24], [sw \$13, 26(\$30)], [AFCD001A], [存MEM26],
    [25], [lw \$14, 16(\$30)], [8FCE0010], [\$14=MEM16],
    [26], [sw \$14, 27(\$30)], [AFCE001B], [存MEM27],
    [27], [addi \$15, \$0, 0], [240F0000], [初始化\$15],
    [28], [beq \$1, \$1, 2], [10210002], [相等跳2],
    [29], [addi \$15, \$0, 1], [240F0001], [设置\$15=1],
    [30], [addi \$16, \$0, 1], [24080001], [设置\$16=1],
    [31], [sw \$15, 28(\$30)], [AFCF001C], [存MEM28],
    [32], [addi \$17, \$0, 0], [24110000], [初始化\$17],
    [33], [bne \$1, \$2, 2], [14220002], [不等跳2],
    [34], [addi \$17, \$0, 1], [24110001], [设置\$17=1],
    [35], [addi \$18, \$0, 1], [24120001], [设置\$18=1],
    [36], [sw \$17, 29(\$30)], [AFD1001D], [存MEM29],
    [37], [j 40], [08000028], [跳转40],
    [38], [addi \$19, \$0, 1], [24130001], [设置\$19=1],
    [39], [addi \$20, \$0, 1], [24140001], [设置\$20=1],
    [40], [addi \$21, \$0, 5], [24150005], [设置\$21=5],
    [41], [sw \$21, 30(\$30)], [AFD5001E], [存MEM30],
    [42], [halt], [FFFFFFFF], [终止],
  ),
  caption: [测试汇编程序（20-42）],
  kind: table,
)

测试程序涵盖了：
- *R型指令*：ADDU, SUBU, SLT, AND, NOR, OR, XOR, SLL, SRL
- *I型指令*：ADDIU, SLTI, LW, SW, BEQ, BNE
- *J型指令*：J（无条件跳转）

=== 预期结果

根据 `instructionMemory.v` 中定义的测试程序，在程序执行完毕（遇到halt指令）后，数据存储器（DataMemory）中特定地址的值应如下表所示。这些值反映了各类指令（算术、逻辑、访存、分支和跳转）的正确执行结果。

#figure(
  table(
    columns: 2,
    align: center,
    [*存储器地址*], [*预期的32位值 (十进制)*],
    [16], [12],
    [17], [2],
    [18], [1],
    [19], [5],
    [20], [-8],
    [21], [7],
    [22], [2],
    [23], [20],
    [24], [3],
    [25], [100],
    [26], [1],
    [27], [12],
    [28], [0],
    [29], [0],
    [30], [5],
  ),
  caption: [数据存储器预期结果],
  kind: table,
)

== CPU结构图

单周期CPU的完整数据通路包含以下关键连接：

1. PC模块输出32位地址到指令存储器
2. 指令存储器解析指令并输出各字段
3. 寄存器文件根据rs和rt读取操作数
4. ALU执行运算并输出结果和零标志
5. 数据存储器支持加载和存储操作
6. 控制单元生成所有控制信号
7. 多路选择器根据控制信号选择数据路径

#figure(
  image("sig32.svg", width: 65%),
  caption: [32位单周期CPU数据通路图]
)

= 实验结果

== 仿真验证

通过Vivado仿真验证了CPU的正确性：

1. *初始化阶段*：PC从0开始，成功读取第一条指令
2. *R型指令测试*：
   - ADDU指令：成功计算5+7=12
   - SUBU指令：成功计算7-5=2
   - SLT指令：成功比较5\<7，结果为1
   - 位运算指令：AND, OR, XOR, NOR等均正确执行
   - 移位指令：SLL和SRL正确执行左移和右移操作

3. *I型指令测试*：
   - ADDIU指令：立即数加法正确执行
   - SLTI指令：立即数比较正确执行
   - LW/SW指令：数据存储器读写操作正常
   - BEQ/BNE指令：分支跳转逻辑正确

4. *J型指令测试*：
   - J指令：无条件跳转正确执行，程序跳转到目标地址

== 关键仿真波形分析

为了直观地验证CPU的正确性，我们通过Vivado进行了波形仿真，并将关键信号的动态变化记录在下图中。该波形图展示了程序执行过程中，PC值的变化、指令的读取以及通过`sw`指令写入数据存储器的最终结果。

#figure(
  image("sim.png", width: 100%),
  caption: [CPU仿真波形图]
)

从上方的仿真波形图可以看出：
- *时钟与复位*: `clk` 信号规律性地翻转，为CPU提供时钟基准。`Reset` 信号在初始阶段为高电平，将PC复位至0，随后拉低，CPU开始从0地址处执行指令。
- *指令执行流程*: `addr` 信号即为PC的值，在每个时钟上升沿后，PC会更新为下一条指令的地址（顺序执行则+4，发生跳转则更新为目标地址）。指令存储器根据`addr`取出对应的`instruction`。
- *数据存储与验证*: 我们通过 `test_addr` 端口来指定要观察的数据存储器地址，其对应的32位数据通过 `test_data` 端口输出。仿真结果清晰地展示了测试程序中各条`sw`指令的执行效果：
  - 当 `test_addr` 设置为16时，`test_data` 显示为 `h0000_000C` (十进制12)，这对应 `addu` 指令 `5+7` 的结果。
  - 当 `test_addr` 设置为17时，`test_data` 显示为 `h0000_0002` (十进制2)，对应 `subu` 指令 `7-5` 的结果。
  - 当 `test_addr` 设置为20时，`test_data` 显示为 `hFFFF_FFF8` (十进制-8)，对应 `nor` 指令 `~ (5 | 7)` 的结果。
- *分支与跳转*: 波形图也验证了`beq`、`bne`和`j`指令的正确性。例如，在执行`j 40`指令后，`addr`（PC）直接从37跳转到了40，跳过了38和39两条指令。

综上所述，仿真波形与我们"预期结果"部分表格中的数据完全一致，证明了CPU数据通路和控制逻辑设计的正确性。

== 上板验证

将设计下载到FPGA实验箱后，我们对硬件进行了实体验证。为了展示CPU执行测试程序后的最终状态，我们将`test_data`端口连接到实验箱的数码管，并设计了一个简单的显示模块，能够展示关键内存地址 (`test_addr`) 上的内存值。

#figure(
  image("board.png", width: 47%),
  caption: [FPGA上板验证实物图]
)

上图的实物照片记录了验证的最终结果。在CPU执行完所有测试指令并进入暂停状态后，板上的数码管清晰地显示了预设的关键内存地址的最终值。例如，图中可以验证地址16的值为12 (`hC`)，地址17的值为2 (`h2`)等。所有在板上观察到的数据均与仿真波形和预期结果完全一致，这从物理层面最终验证了CPU设计的正确性和稳定性。

== 性能分析

本单周期CPU设计的特点：
- *优点*：结构简单，易于理解和实现，每条指令在一个时钟周期内完成
- *缺点*：时钟周期受最长指令路径限制，频率较低
- *资源使用*：在FPGA上占用资源合理，满足教学实验要求

= 源码

== 顶层模块 - SingleCycleCPU.v

```verilog
`timescale 1ns / 1ps

module SingleCycleCPU(
        input clk,Reset,
        input [31:0]test_addr,//取存储器地址
        input [4:0]test_addr1,//取寄存器地址
        output [31:0] test_data,
        output [31:0]test_data1
    );
     wire [31:0] instruction;
     wire [31:0]sort;
     wire [31:0] addr;
     wire [1:0]PCSrc;
     wire zero;
     wire [31:0]Out1;
     wire [31:0]Out2;
     wire [4:0]rs;
     wire [4:0]rt;
        
    wire [5:0] opCode;
    wire [31:0] Result;
    wire [4:0] rd;
    wire Extsel, Alu_SrcA, Alu_SrcB;
    wire RD,WR;
    wire [5:0]Func;
    wire PCWre;

    wire [31:0]extendImm;
    wire[3:0] Alu_Op;
    wire[31:0] DataOut,DB;
    wire[15:0] Imm;
    wire[4:0] sa;
    wire DBDataSrc, RegWre,RegDst;

    assign sort=(opCode==6'b111111)?32'd1:32'd0;
    
    PC ins(
       .clk(clk),
       .Reset(Reset),
       .PCWre(PCWre),
       .PCSrc(PCSrc),
       .Imm(extendImm),
       .addr(addr),
       .instruction(instruction)
    );
    
   instructionMemory ins1(
       .addr({2'b0,addr[31:2]}),   
       .opCode(opCode),   
       .rs(rs), 
       .rt(rt),
       .rd(rd),
       .immediate(Imm),
       .sa(sa),
       .Func(Func),
       .instruction(instruction)
    );
    
    regfile ins2(
       .clk(clk),
       .RegWre(RegWre),
       .raddr1(rs),
       .raddr2(rt),
       .rdata1(Out1),
       .rdata2(Out2),
       .waddr(RegDst ? rd : rt),
       .wdata(DB),
       .test_addr(test_addr1),
       .test_data(test_data1)
    );
    
    Alu ins3(
       .Alu_SrcA(Alu_SrcA),
       .Alu_SrcB(Alu_SrcB),
       .ReadData1(Out1),
       .ReadData2(Out2),
       .sa(sa),
       .extend(extendImm),
       .Alu_Op(Alu_Op),
       .zero(zero),
       .Alu_Result(Result)
    );
    
    SignZeroExtend ins4(
    .Imm(Imm),
    .Extsel(Extsel),
    .extendImm(extendImm)
    );
    
    DataMemory ins5(
        .clk(clk),
        .wenr(RD),
        .wenw(WR),
        .DBDataSrc(DBDataSrc),
        .DAddr(Result),
        .DataIn(Out2),
        .DataOut(DataOut),
        .DB(DB),
        .test_addr(test_addr),
        .test_data(test_data)
    );
    
    ControlUnit ins6(
        .opCode(opCode),
        .zero(zero),
        .Func(Func),
        .PCWre(PCWre),
        .AluSrcA(Alu_SrcA),
        .AluSrcB(Alu_SrcB),    
        .DBDataSrc(DBDataSrc),
        .RegWre(RegWre), 
        .mRD(RD),
        .mWR(WR),
        .ExtSel(Extsel),
        .RegDst(RegDst),
        .PCSrc(PCSrc),
        .Alu_Op(Alu_Op)
    );
endmodule
```

== 控制单元模块 - ControlUnit.v

```verilog
`timescale 1ns / 1ps

module ControlUnit(
    input [5:0] opCode,
    input zero,
    input [5:0] Func,
    output reg PCWre,
    output reg AluSrcA,
    output reg AluSrcB,    
    output reg DBDataSrc,
    output reg RegWre,
    output reg mRD,
    output reg mWR,
    output reg ExtSel,
    output reg RegDst,
    output reg [1:0]PCSrc,
    output reg [3:0]Alu_Op
    );
   initial begin
        PCWre=1;
         mRD=0;
         mWR=0;
         DBDataSrc=0;
   end
   always@(*)
   begin
       PCWre = (opCode == 6'b111111) ? 0 : 1;   //halt
        mWR = (opCode == 6'b101011) ? 1 : 0;     //写存储器使能
        mRD = (opCode == 6'b100011) ? 1 : 0;     //读使能
        DBDataSrc = (opCode == 6'b100011) ? 1 : 0;
        
        if(opCode==6'b000000&&Func==6'b100001)//ADDU
        begin
             ExtSel = 0;
             RegDst = 1;
             RegWre = 1;
             AluSrcA = 0;
             AluSrcB = 0;
             PCSrc = 2'b00;
             Alu_Op = 4'b0001;
        end
        else if(opCode==6'b000000&&Func==6'b100011)//SUBU
        begin
            ExtSel = 0;
             RegDst = 1;
             RegWre = 1;
             AluSrcA = 0;
             AluSrcB = 0;
             PCSrc = 2'b00;
             Alu_Op = 4'b0010;
        end
        // ... 其他指令的控制逻辑
        else if(opCode==6'b001010)//SLTI指令
        begin
             ExtSel = 1;         // 符号扩展立即数
             RegDst = 0;         // 目标寄存器是rt
             RegWre = 1;         // 需要写寄存器
             AluSrcA = 0;        // ALU操作数A是寄存器rs
             AluSrcB = 1;        // ALU操作数B是立即数
             PCSrc = 2'b00;      // PC+4
             Alu_Op = 4'b0011;   // 使用和SLT相同的ALU操作
        end
        else
        begin
            ExtSel=0;
            RegDst=0;
            RegWre=0;
            AluSrcA=0;
            AluSrcB=0;
            PCSrc=2'b11;
            Alu_Op=0;
        end
   end
endmodule
```

== ALU模块 - Alu.v

```verilog
`timescale 1ns / 1ps

module Alu(
input Alu_SrcA,
    input Alu_SrcB,
    input [31 :0] ReadData1,
    input [31 :0] ReadData2,
    input [4:0] sa,
    input [31:0] extend,
    input [3:0] Alu_Op,
    output  reg zero,
    output  reg[31 :0] Alu_Result
    );
    reg [31:0] Alu_Src1;
    reg [31:0] Alu_Src2;
    always@(*)
    begin
        Alu_Src1 = (Alu_SrcA == 0) ? ReadData1 : sa;
        Alu_Src2 = (Alu_SrcB == 0) ? ReadData2 : extend;
        
        if(Alu_Op==4'b0001)//无符号加法 
            Alu_Result<=Alu_Src1+Alu_Src2;
        else if(Alu_Op==4'b0010)//无符号减法
            Alu_Result<=Alu_Src1-Alu_Src2;
        else if(Alu_Op==4'b0011)//有符号比较
            Alu_Result<=(((Alu_Src1 < Alu_Src2) && (Alu_Src1[31] == Alu_Src2[31] )) ||( ( Alu_Src1[31] ==1 && Alu_Src2[31] == 0))) ? 1:0;
        else if(Alu_Op==4'b0100)//位与
            Alu_Result<=Alu_Src1&Alu_Src2;
        else if(Alu_Op==4'b0101)//位或非
            Alu_Result<=~(Alu_Src1|Alu_Src2);
        else if(Alu_Op==4'b0110)//位或
            Alu_Result<=(Alu_Src1|Alu_Src2);
        else if(Alu_Op==4'b0111)//位异或
            Alu_Result<=(Alu_Src1^Alu_Src2);
        else if(Alu_Op==4'b1000)//逻辑左移
            Alu_Result<=Alu_Src2<<Alu_Src1;
        else if(Alu_Op==4'b1001)//逻辑右移
            Alu_Result<=Alu_Src2>>Alu_Src1;
        else Alu_Result<=31'b0;    
           zero=(Alu_Result==0)?1:0;
    end
endmodule
```

== 存储器模块 - DataMemory.v

```verilog
`timescale 1ns / 1ps

module DataMemory(
    input clk,
    input wenr,           // 读使能信号
    input wenw,           // 写使能信号
    input DBDataSrc,      // 写回数据源选择信号 (0: ALU结果, 1: 存储器数据)
    input [31:0] DAddr,   // 地址输入 (来自ALU结果)
    input [31:0] DataIn,  // 待写入的数据 (来自寄存器rt)
    output reg[31:0] DataOut, // 从存储器读出的数据
    output reg[31:0] DB,      // 写回总线的数据
    input [31:0] test_addr,   // 板上测试用地址
    output reg[31:0] test_data // 板上测试用数据输出
    );
    initial begin
        DB <= 32'h0;
    end

    // 定义一个256x32位的数据存储器 (RAM)
    reg[31:0]ram[255:0];
    integer i;
    // 初始化RAM，将前32个单元清零
    initial begin
        for(i=0;i<=31;i=i+1)
        begin
            ram[i]=0;
        end
    end

    // 读操作 和 写回数据选择 (组合逻辑)
    always@(*)
    begin
        // 读操作: 当读使能(wenr)为1时，根据DAddr从ram中读取数据，否则输出高阻态
        DataOut[31:0] = wenr ? ram[DAddr] : 32'bz; // z 为高阻态

        // 写回数据选择: 根据DBDataSrc信号选择写回的数据源
        // 0: 选择ALU的计算结果 (此时DAddr端口传入的是ALU结果)
        // 1: 选择从数据存储器读出的数据 (DataOut)
        DB = (DBDataSrc == 0) ? DAddr : DataOut;
    end

    // 测试端口逻辑 (组合逻辑)
    always@(*)
    begin
        // 将测试地址test_addr对应的数据输出到test_data
        test_data[31:0] = ram[test_addr];
    end

    // 写操作 (同步时序逻辑)
    always@(posedge clk)
    begin
        // 在时钟上升沿，当写使能(wenw)为1时，执行写操作
        if(wenw)
            begin
                ram[DAddr] = DataIn[31:0];
            end
        //$display("mwr: %d $12 %d %d %d %d", mWR, ram[12], ram[13], ram[14], ram[15]);
    end
endmodule

```

== 寄存器文件模块 - regfile.v

```verilog
`timescale 1ns / 1ps

module regfile(
    input clk,
    input RegWre,           // 寄存器写使能信号
    input [4:0] raddr1,     // 读地址1 (通常为rs)
    input [4:0] raddr2,     // 读地址2 (通常为rt)
    output reg[31:0] rdata1, // 读端口1输出数据
    output reg[31:0] rdata2, // 读端口2输出数据
    input [4:0] test_addr,  // 板上测试用读地址
    output reg[31:0] test_data, // 板上测试用读数据
    input [4:0] waddr,      // 写地址 (rd或rt)
    input [31:0] wdata      // 待写入的数据
    );

    // 定义32个32位的通用寄存器
    reg [31:0] memory[31:0];
    
    // 初始化所有寄存器为0 (主要用于仿真)
    integer i;
    initial begin
        for(i=0; i<=31; i=i+1)
        begin
            memory[i] = 32'h0;
        end
    end

    // 读端口1 (异步读)
    always@(*)
    begin
        rdata1 = memory[raddr1];
    end

    // 读端口2 (异步读)
    always@(*)
    begin
        rdata2 = memory[raddr2];
    end
    
    // 测试端口 (异步读)
    always@(*)
    begin
        test_data = memory[test_addr];
    end

    // 写端口 (同步写)
    always@(posedge clk)
    begin
        // 当写使能有效且目标地址不为0时，在时钟上升沿写入数据
        // MIPS架构中，0号寄存器($zero)恒为0，不可写入
        if(RegWre == 1 && waddr != 5'b0)
        begin
            memory[waddr] <= wdata;
        end
    end

endmodule


```

== 立即数扩展模块 - SignZeroExtend.v

```verilog
`timescale 1ns / 1ps

module SignZeroExtend(
    input [15:0] Imm,       // 输入的16位立即数
    input Extsel,           // 扩展模式选择 (1: 符号扩展, 0: 零扩展)
    output [31:0] extendImm // 输出的32位扩展结果
    );
    
    // 将16位立即数的低16位直接赋给输出
    assign extendImm[15:0] = Imm;
    
    // 根据Extsel信号决定高16位的扩展方式
    // 如果Extsel为1，进行符号扩展：如果Imm的最高位(Imm[15])为1，则高16位全为1，否则全为0
    // 如果Extsel为0，进行零扩展：高16位全为0
    assign extendImm[31:16] = Extsel ? (Imm[15] ? 16'hffff : 16'h0000) : 16'h0000;
    
endmodule

```

== 程序计数器模块 - PC.v

```verilog
`timescale 1ns / 1ps

module PC(
    input clk,
    input Reset,        // 复位信号, 高电平有效
    input PCWre,        // PC写使能 (1: 使能, 0: 禁用)
    input [1:0] PCSrc,  // PC源选择信号 (决定下一条指令地址的来源)
    input [31:0] Imm,   // 符号扩展后的立即数，用于分支计算
    input [31:0] instruction, // 当前指令，用于J型指令寻址
    output reg[31:0] addr     // PC输出的指令地址
    );

   // 初始化PC地址为0
   initial
   begin
       addr = 32'h00000000;
   end

    // PC更新逻辑
    always@(posedge clk)
    begin
        if (Reset) // 复位时，PC清零
        begin
            addr <= 32'h00000000;
        end
        else if(PCWre) // 当PC写使能时，根据PCSrc更新PC
        begin
            case(PCSrc)
                2'b00:  addr <= addr + 4; // 顺序执行, PC = PC + 4
                2'b01:  addr <= addr + 4 + (Imm << 2); // 分支跳转, PC = PC + 4 + offset
                2'b10:  addr <= {(addr + 4)[31:28], instruction[25:0], 2'b00}; // J型跳转
                2'b11:  addr <= addr; // PC保持不变 (用于暂停)
                default: addr <= addr + 4;
            endcase
        end
    end
endmodule

```

== 上板展示模块 - single_display.v

```verilog


module single_display(
    // 时钟与复位信号
    input clk,
    input resetn,    // 低电平有效复位

    // LCD和触摸屏接口，无需修改
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

//-----{LED显示}begin
// (此部分为空)
//-----{LED显示}end

//-----{实例化CPU核}begin
    // 定义连接CPU的测试端口
    wire [31:0] test_addr; // 用于读取DataMemory的地址
    wire [31:0] test_data;  
    wire [4:0]test_addr1; // 用于读取RegFile的地址
    wire [31:0]test_data1;

    // CPU复位信号处理 (开发板为低电平复位，CPU核为高电平复位)
    wire cpu_reset = ~resetn;

    // 实例化单周期CPU
    SingleCycleCPU CPU(
        .clk   (clk       ),
        .Reset (cpu_reset ), // 使用处理后的高电平复位信号
        .test_addr(test_addr),
        .test_addr1(test_addr1),
        .test_data (test_data),
        .test_data1(test_data1)
    );
//-----{实例化CPU核}end

//---------------------{LCD显示模块}begin--------------------//
//-----{实例化LCD驱动}begin
    // 此部分为LCD驱动模块接口，无需修改
    reg         display_valid;
    reg  [39:0] display_name;
    reg  [31:0] display_value;
    wire [5 :0] display_number; // LCD模块当前希望显示的行号
    wire        input_valid;
    wire [31:0] input_value;

    lcd_module lcd_module(
        .clk            (clk           ),
        .resetn         (resetn        ),

        .display_valid  (display_valid ),
        .display_name   (display_name  ),
        .display_value  (display_value ),
        .display_number (display_number),
        .input_valid    (input_valid   ),
        .input_value    (input_value   ),

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
//-----{实例化LCD驱动}end

//-----{从CPU核获取数据}begin
    // display_number由LCD模块产生，范围1-44，用于选择要显示的内容
    // 此处设置，当LCD要显示第1-32行时，对应查看数据存储器的0-31地址
    assign test_addr = display_number - 6'd1;
    // test_addr1的连接可在此处添加
//-----{从CPU核获取数据}end

//-----{准备要在LCD上显示的数据}begin
    // 此处定义了44个显示项，可按需修改
    always @(posedge clk)
    begin
        // display_number是LCD当前要显示的行号 (1-44)
        if ( display_number > 0 && display_number < 33 ) // 显示数据存储器MEM[0]到MEM[31]
        begin
            display_valid <= 1'b1;
            // 修复: "MEM"字符串不能直接赋值，需使用ASCII码。'M'=h4D, 'E'=h45
            display_name[39:16] <= {8'h4D, 8'h45, 8'h4D}; // "MEM"
            // 将地址数值转换为ASCII码用于显示，如地址15(hF)显示为"MEM0F"
            display_name[15: 8] <= {4'b0011, test_addr[7:4]}; // 地址高4位
            display_name[7 : 0] <= {4'b0011, test_addr[3:0]}; // 地址低4位
            display_value       <= test_data;
          end
        else // 其他行不显示
        begin
           display_valid <= 1'b0;
           display_name  <= 40'd0;
           display_value <= 32'd0;
        end
    end
//-----{准备要在LCD上显示的数据}end
//----------------------{LCD显示模块}end---------------------//
endmodule

```