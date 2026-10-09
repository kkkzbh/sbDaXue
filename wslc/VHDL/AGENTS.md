# Repository Guidelines

## Project Structure & Module Organization
- Top-level VHDL experiments live in `exp2`–`exp8`; each folder contains the design (`*.vhd`), supporting Quartus project files (`*.qsf`), and reference assets (schematics, screenshots, simulation captures).  
- `exp2` and some later labs also include dedicated testbenches named with the `_tb.vhd` suffix.  
- Reusable single-file examples sit at the repo root (for example `vhdl_first.vhd`). Create new work in its own `expX` folder to keep artifacts isolated.

## Build, Test, and Development Commands
- Quartus Prime compile (from an experiment directory):  
  `quartus_sh --flow compile <project>` — uses the matching `.qsf` (e.g., `transcode_led` in `exp7`).  
- Simulate with GHDL (portable choice when ModelSim is unavailable):  
  `ghdl -a exp2/full_adder.vhd exp2/full_adder_tb.vhd`  
  `ghdl -e full_adder_tb`  
  `ghdl -r full_adder_tb --vcd=wave.vcd` — produces a VCD for GTKWave.  
- Quick lint/style check: `ghdl -s <files>` to fail fast on syntax issues.

## Coding Style & Naming Conventions
- Indent two spaces; align `port`/`generic` lists vertically for readability.  
- Uppercase VHDL keywords (`ENTITY`, `ARCHITECTURE`, `PROCESS`); keep signal and entity names in lower_snake_case to match existing files (`full_adder`, `ff_jk`).  
- Always `use ieee.std_logic_1164.all;` and prefer `std_logic_vector` for buses.  
- Place testbenches in the same folder as the unit under test and suffix them `_tb.vhd`.

## Testing Guidelines
- Provide a minimal self-checking testbench for every new entity. Drive edge cases (all zeros/ones, carries, invalid codes) and assert expected outputs.  
- Name test architectures `arch_tb` and processes `stimulus`/`checker` for clarity.  
- Keep generated waves (`*.vcd`, ModelSim `work/` directory) out of version control; regenerate when needed using the commands above.

## Commit & Pull Request Guidelines
- Use concise, present-tense Conventional Commit-style summaries: `feat: add 16-to-4 encoder`, `test: cover ripple-carry carry-out`.  
- One experiment or logical change per commit; include the experiment folder in the message when relevant (`chore: tidy exp5 assets`).  
- PRs should describe intent, list key files touched, note simulation/compile results, and link any tracking issue. Attach screenshots of timing or simulation outputs when they influence review.

## Security & Configuration Tips
- Never commit Quartus build outputs (`db/`, `incremental_db/`, `output_files/`) or temporary archives; add them to your ignore rules.  
- Keep pin assignments and device selections inside `.qsf` committed files; avoid hard-coding machine-specific absolute paths.  
- When sharing waveforms or media, prefer compressed images over large raw captures to keep the repo lightweight.

## 必须了解！

FPGA可编程逻辑阵列芯片的型号为：EP3C16Q240C8。
单步时钟输入引脚是引脚 211，每按动一次单步时钟按钮，将产生一个时钟方波脉冲。 
连续时钟输入引脚是引脚 210，时钟频率为24MHz。        
复位脉冲输入引脚是引脚 151，每按动一次复位按钮，则产生一个复位正脉冲（一个短暂的、从低电平跳变为高电平再恢复低电平的电信号，且这个信号的作用是让电路 / 系统回到初始状态（复位））。
蜂鸣器输出引脚是引脚 174。        
以下是其他功能信号的引脚。


波动开关（KD1-KD20）引脚为：37、38、41、43、44、45、49、50、51、52、55、56、57、64、65、68、69、70、71、72。         
LED数码管段选（a、b、c、d、e、f、g、dp），低电平有效，引脚为：173、171、168、167、166、164、162、160。         
LED数码管字选（LDC1、 LDC2 、 LDC3 、 LDC4、 LDC5 、 LDC6 ），低电平有效，引脚为：148、147、146、145、144、143。
LED发光管（LDD1、 LDD2 、 LDD3 、 LDD4 、 LDD5 、 LDD6、LDD7、LDD8 ），低电平有效，引脚为：85、84、83、82、81、80、78、73。                  


LED阵列行选（r1-r16），低电平有效，引脚为：142、137、135、134、132、131、128、127、126、120、119、118、117、113、112、111。         
LED阵列列选（c1- c16），低电平有效，引脚为：110、109、108、106、103、102、101、100、99、98、95、94、93、88、87、86。
键盘阵列行扫描（Key_r1-Key_r4），低电平有效，引脚为：18、19、20、21。         
键盘阵列列扫描（Key_c1- Key_c4），引脚为：9、6、5、4。
