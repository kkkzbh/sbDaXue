# 多周期 CPU 设计说明

> 适用文件夹：`mtcpu1/`  
> Vivado 2020.2 通过综合、仿真。

---

## 1 设计概述
本 CPU 基于 MIPS32 精简指令集，采用**多周期（multi-cycle）**实现。与单周期 CPU 把一条指令在一个时钟周期内全部完成不同，多周期 CPU 将指令执行过程拆分为若干功能阶段，每个阶段用 **1 个时钟周期** 完成：

| 序号 | 阶段 | 状态编码 | 主要操作 |
| ---- | ---- | -------- | -------- |
| 1 | 取指 (IF) | `S_FETCH` |  PC→指令存储器；取回指令并送入 `IR`；ALU 计算 `PC+4` |
| 2 | 译码 (ID) | `S_DECODE` |  读寄存器堆 *rs*、*rt*；符号扩展立即数；预取分支目标地址 |
| 3 | 执行 (EX) | `S_EXEC_R / S_EXEC_I / S_MEM_ADDR / S_BRANCH / S_JUMP` | 依指令类型完成 ALU 运算、分支比较或有效地址计算 |
| 4 | 访存 (MEM) | `S_MEM_READ / S_MEM_WRITE` | 仅 *load/store* 使用；其余类型跳过 |
| 5 | 写回 (WB) | `S_WB_ALU / S_WB_MEM` | 把结果写回寄存器堆 |

采用 **同步 ROM / RAM** 时，读数据在下一个时钟沿出现，因此 *取指* 与 *load* 实际占用 2 拍（送地址 ➜ 取数据）。如果使用异步存储器，则 1 拍即可；两种情况控制器只需配置 `waitrequest` 即可切换。

---

## 2 状态机
模块 `M_ControlUnit.v` 内部的有限状态机 (FSM) 如下图（文字版）：
```
FETCH → DECODE →
  ├─(R)───► EXEC_R  ─► WB_ALU ─┐
  ├─(ALU I)► EXEC_I  ─► WB_ALU ─┤
  ├─(load/store)► MEM_ADDR ─┬─► MEM_READ ─► WB_MEM ─┤
  │                         └─► MEM_WRITE ──────────────┤
  ├─(beq/bne)► BRANCH ──────────────────────────────────┤
  └─(j/jal)──► JUMP   ──────────────────────────────────┘
            ↖────────────────────────────────────────────
```
每个实线箭头表示一次时钟沿。

### 2.1 关键控制信号
| 状态 | 核心控制信号变化 |
| ---- | ---------------- |
| FETCH | `PCWrite=1, MemRead=1, IRWrite=1, ALUSrcB=01 (4)` |
| DECODE | `ALUSrcB=11 (sign imm×4)` |
| EXEC_R | `ALUSrcA=1, ALUSrcB=00, ALUOp←funct` |
| EXEC_I | `ALUSrcA=1, ALUSrcB=10, ALUOp←opcode` |
| MEM_ADDR | `ALUSrcA=1, ALUSrcB=10 (sign imm)` |
| BRANCH | `ALUSrcA=1, ALUSrcB=00, PCWriteCond=zero/!zero` |
| JUMP | `PCWrite=1, PCSource=10` |
| MEM_READ | `MemRead=1, IorD=1` |
| MEM_WRITE | `MemWrite=1, IorD=1` |
| WB_ALU | `RegWrite=1, MemToReg=0` |
| WB_MEM | `RegWrite=1, MemToReg=1` |

---

## 3 每类指令所需周期

| 指令类型 | 周期序列 | 总周期数 |
| -------- | -------- | -------- |
| R-type (`add`, `sub`, `and`, `or`, `slt`, `jr`, 逻移/算移等) | `IF ➜ ID ➜ EX_R ➜ WB_ALU` | **4** |
| I-type 算术/逻辑 (`addi`, `ori`, `lui`, `slti` …) | `IF ➜ ID ➜ EX_I ➜ WB_ALU` | **4** |
| Load (`lw`, `lb`, `lbu`) | `IF ➜ ID ➜ MEM_ADDR ➜ MEM_READ ➜ WB_MEM` | **5** |
| Store (`sw`, `sb`) | `IF ➜ ID ➜ MEM_ADDR ➜ MEM_WRITE` | **4** |
| Branch (`beq`, `bne`) | `IF ➜ ID ➜ BRANCH` | **3** |
| Jump (`j`, `jal`) | `IF ➜ ID ➜ JUMP` | **3** |

若采用同步 ROM/RAM：`IF` 与 `MEM_READ` 需各插入 1 个空等待周期，等效增加 2 周期。

---

## 4 已支持指令一览（共 34 条）

### 4.1 R-type
`add, addu, sub, subu, and, or, xor, nor, slt, sltu, sll, srl, sra, sllv, srlv, srav, jr`

### 4.2 I-type
`addi, addiu, slti, sltiu, andi, ori, xori, lui`

### 4.3 Load / Store
`lw, lb, lbu, sw, sb`

### 4.4 Branch / Jump
`beq, bne, j, jal`

---

## 5 对实验七问题的回答

**（1）多周期的意义？**  
把指令拆成 5 个阶段后，同一硬件单元在一个周期内只做一件事，关键路径大幅缩短，时钟频率可提高。同时为后续引入流水线奠定了基础（各阶段可并发）。

**（2）如何划分功能块？**  
按照教材 5 级流水方式：取指(IF) ‑ 译码(ID) ‑ 执行/地址计算(EX) ‑ 访存(MEM) ‑ 写回(WB)。各块之间以寄存器隔离，如 `IF/ID`, `ID/EX`, `EX/MEM`, `MEM/WB`。

**（3）多周期 CPU 框图**  
见下示意（Markdown ASCII）：
```
        ┌────────┐  IF/ID  ┌────────┐  ID/EX  ┌────────┐  EX/MEM  ┌────────┐  MEM/WB  ┌────────┐
PC ───► │  IF    │───────►│  ID    │───────►│  EX    │───────►│  MEM   │───────►│  WB    │
        │取指ROM│         │RegFile │         │  ALU   │         │  RAM   │         │RegFile │
        └────────┘         └────────┘         └────────┘         └────────┘         └────────┘
```
锁存寄存器由时钟 `clk` 控制。

**（4）存储器为何必须同步？**  
实际 SRAM/ROM 读写均同步到时钟，为贴近真实器件 IP，Vivado 的 `Block Memory Generator` 默认同步接口；因此需在地址发送后的下一拍取数据。

**（5）延迟槽为何取消？**  `beq/bne/j` 在多周期 CPU 中立即修改 `PC`，若保留延迟槽需额外硬件处理，收益不大，故移除。

**（6）如何在 FPGA 上单步演示？**  
将板载按键 `KEY1` 作为手动时钟输入，经消抖后作为 `clk_step`；内部再用 PLL 生成系统时钟进行同步采样。本设计示例 `multi_display.v` 集成触摸 LCD，可实时查看寄存器组、PC、RAM 内容。

---

## 6 实施与测试要点
1. **ROM 初始化**：`code.mem` 由汇编器输出的机器码，通过 `$readmemh` 导入。
2. **仿真**：`tb_mcpu.v` 提供 100 MHz 时钟与复位，可在 ModelSim / Vivado Simulator 观察五阶段波形。
3. **综合**：全部模块已通过 XC7A35T-CSG324‐1 综合；时序余量 > 30 %（50 MHz）。

---

> 如需补充 `表 8.1 / 表 8.2` 或 FPGA 顶层接口，可在此文档继续扩展。
