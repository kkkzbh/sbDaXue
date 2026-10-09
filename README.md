# sbDaXue · 大学代码与课程实验合集

这里整理了我从大一、大二开始积累的课程作业、课程设计、实验代码、算法练习和个人学习项目。内容覆盖 C/C++、数据结构、算法竞赛、计算机组成、FPGA、数据库、C#、Java、Unity、数学建模、操作系统与计算机网络等方向。

仓库保留各项目的原有目录和代码组织，便于对照当时的作业、报告和实验过程。各目录属于独立工程，使用的语言版本、开发工具和运行平台不同。

**已确认的课程时间：** `huffmancode` 是 **2024 年大一下学期《数据结构》课程设计**。其他项目先按内容分类，具体年级、学期和课程归属以项目自身说明及报告为准；合集也收录后续学习代码。

## 从这里开始

| 方向 | 目录 | 做了什么 |
| --- | --- | --- |
| C 语言综合课设 | [homework](homework)、[C语言大作业/作业/综合实验客房管理系统](C%E8%AF%AD%E8%A8%80%E5%A4%A7%E4%BD%9C%E4%B8%9A/%E4%BD%9C%E4%B8%9A/%E7%BB%BC%E5%90%88%E5%AE%9E%E9%AA%8C%E5%AE%A2%E6%88%BF%E7%AE%A1%E7%90%86%E7%B3%BB%E7%BB%9F) | 客房管理、账户与房间信息处理；较完整版本还包含排序和统计模块。 |
| 通讯录 | [Contacts](Contacts) | 联系人信息管理、菜单交互与文件读写。 |
| C 语言小游戏 | [Game/for tie](Game/for%20tie) | 三子棋和扫雷，练习二维数组、游戏状态判断与交互循环。 |
| 大一下数据结构课设 | [huffmancode](huffmancode) | 文件压缩与解压：Huffman、RLE、LZ77，以及 LZ77 + Huffman 组合实现。 |
| 数据结构与算法库 | [DTS](DTS)、[homework-DS](homework-DS)、[java](java)、[Stack](Stack)、[Firstcpp](Firstcpp)、[函数库](%E5%87%BD%E6%95%B0%E5%BA%93)、[算法库](%E7%AE%97%E6%B3%95%E5%BA%93) | 链表、栈、队列、树、堆、图、多项式和算法片段。 |
| 算法竞赛与习题 | [luogu](luogu)、[luogu2](luogu2)、[csp](csp)、[wslc/CL25018](wslc/CL25018)、[wslc/matij](wslc/matij)、[wslc/考试专用](wslc/%E8%80%83%E8%AF%95%E4%B8%93%E7%94%A8) | 题目实现、算法模板与考试练习。 |
| CPU 与计算机组成 | [ccu](ccu) | 单周期、多周期、流水线 CPU，存储器和顶层连接实验。 |
| 数字电路与 FPGA | [CS_ALU](CS_ALU)、[CS_ALU_TRUE](CS_ALU_TRUE)、[CS_adder](CS_adder)、[data_ram](data_ram)、[wslc/VHDL](wslc/VHDL) | ALU、加法器、RAM、编码器、显示控制及综合实验。 |
| 数据库 | [SQL](SQL) | 建表、查询、更新、视图、完整性约束、触发器和存储过程。 |
| C# 与桌面程序 | [FirstCS](FirstCS)、[FirstWinFrom](FirstWinFrom)、[highCS](highCS)、[tryCsharp](tryCsharp)、[rand_cs](rand_cs)、[HuiJia](HuiJia) | 面向对象、银行账户继承、数组与员工类、WinForms/WPF 窗口。 |
| Java | [PRJAVA](PRJAVA) | Java 基础练习与 Swing 绘图程序。 |
| Unity 游戏 | [My project](My%20project)、[My project-2024-7-25](My%20project-2024-7-25)、[mla](mla) | 坦克/射击、平台跳跃和马里奥风格游戏练习。 |
| 数学建模与数值计算 | [matlab](matlab)、[wslc/python](wslc/python) | 矩阵运算、优化、微分方程及 2024 国赛 B 题建模代码。 |
| 操作系统 | [wslc/os](wslc/os)、[wslc/bhuos](wslc/bhuos) | 个人系统学习项目和 MIPS 教学操作系统实验。 |
| 网络与并发 | [wslc/cs144/minnow](wslc/cs144/minnow)、[wslc/concurrency](wslc/concurrency)、[wslc/net](wslc/net)、[wslc/qq](wslc/qq) | CS144 网络实验、并发模块、客户端与服务端练习。 |
| 博弈论 | [wslc/gamet](wslc/gamet) | 矩阵博弈、博弈树、均衡分析及实验报告。 |

## 主要项目介绍

### 哈夫曼编码与文件压缩课设

`huffmancode` 围绕“读取文件—统计频率—构建编码—压缩保存—解码还原”完成完整的文件处理流程。

- 使用自写堆选择最小权值结点，构建哈夫曼树，通过遍历生成前缀编码。
- 使用自写哈希表维护解码映射，并通过循环缓冲区和二进制读写打包编码位流。
- 实现 RLE 游程编码、LZ77 滑动窗口匹配和 LZ77 + Huffman 组合压缩。
- 提供 Windows 控制台菜单、输入输出路径选择、进度提示与耗时显示。
- 使用 C++20 模板、Concepts、线程和互斥锁练习通用结构与交互程序组织。

源码中的 `deflate` 使用课设自定义格式，与 ZIP、gzip、zlib 不互通。构建条件、算法细节和使用边界见 [哈夫曼课设 README](huffmancode/README.md)。该项目也有[独立仓库](https://github.com/kkkzbh/huffmancode)。

### C 语言项目：客房管理、通讯录与小游戏

`homework` 和 `C语言大作业` 保存了客房管理系统的多个版本及报告。较完整的一份代码位于：

```text
C语言大作业/作业/综合实验客房管理系统/
  homework(12)(6)/homework(12)/homework/homework/
```

该目录包含 `main.c`、账户模块、客房相关头文件、功能实现，以及 `Sort.c/.h` 和 `statistics.c/.h`。不同版本分别保存，方便查看代码组织和功能演进。运行时账户与客房数据文件未纳入本合集，运行前需根据代码准备测试数据。

`Contacts` 练习结构体、动态数据管理、查找和文件读写；`Game/for tie` 包含三子棋与扫雷，练习棋盘表示、胜负/状态判断和循环交互。

### 数据结构、算法与竞赛练习

`DTS`、`homework-DS`、`Stack`、`Firstcpp` 等目录保存线性结构、树与遍历、多项式等练习。**`java` 目录实际主要是 C++ 代码**，包含 AVL 树、堆、图、链表和多项式相关实现，保留原目录名便于追溯。

`luogu`、`luogu2`、`csp` 和 WSL 下的算法目录保存按题号、比赛编号或知识点组织的代码。部分早期文件仅保留题号或临时命名；具体题意需结合文件注释和对应题目阅读。`PK` 还保留随机数据生成与双程序对拍练习。

### CPU、数字电路与 FPGA

`ccu` 包含单周期、多周期、流水线 CPU 及相关存储器工程。`CS_ALU`、`CS_ALU_TRUE`、`CS_adder` 和 `data_ram` 保存 Verilog 设计、测试平台、引脚约束与必要 IP 配置。

`wslc/VHDL` 保存硬件描述语言实验，从加法器、编码器、计数器与移位，到 LED 显示和综合设计，并配有报告及实验截图。仓库保留 `.v`、`.vhd`、`.xdc`、`.qsf`、`.qpf`、`.xci`、`.coe`、`.mem` 等设计输入；生成缓存、编译数据库和演示视频已排除。Vivado 与 Quartus 工程应分别使用对应工具和目标器件打开。

### 数据库、C# 与 Java

`SQL` 通过课程脚本和实验报告记录关系数据库操作，包含查询、视图、数据更新、完整性约束、触发器和存储过程。

`FirstCS` 以银行账户类练习继承与面向对象；`highCS` 保存评分计算、数组、员工类等作业。WinForms/WPF 目录保留设计器、资源、XAML 和项目文件，可以继续在对应的 .NET 开发环境中查看界面。

`PRJAVA` 保存 Java 学习代码和 Swing 绘图程序。语言分类以源码为准，其他名称包含 `java` 的目录可能仍是 C++ 工程。

### Unity 与网页交互

三个 Unity 工程分别保存坦克/射击、平台跳跃教程和马里奥风格练习。每个工程都保留 `Assets` 及 `.meta`、`Packages`、`ProjectSettings`，可根据 `ProjectSettings/ProjectVersion.txt` 选择编辑器版本后重新生成缓存。

[音乐网页在线演示](https://music.kkkzbh.cn/)位于 `网页/QQmusic`，包含 11 首原始音频、播放控制和自动部署配置。

`Web` 包含具有生命值、经验、金币、武器等状态的 JavaScript 文字冒险/RPG 练习；`py` 实际保存 HTML/JavaScript 2048 小游戏。`HTMLCSS`、`网页`、`未知` 等保存页面、样式、脚本与相关素材。

### 数学建模、操作系统、网络和博弈论

`matlab` 与 `wslc/python` 保存数值计算、优化、微分方程、Notebook 和建模结果，包含 2024 国赛 B 题相关内容。

`wslc/os` 保存内核学习代码及 LaTeX 文档；`wslc/bhuos` 保存 MIPS 教学操作系统实验、ELF 读取、内存和文件系统相关代码。系统实验依赖特定工具链和模拟器，应先阅读子工程配置与说明。

`wslc/cs144/minnow` 保存课程框架上的网络实验；`wslc/concurrency`、`wslc/net`、`wslc/qq` 保存并发、网络模块与客户端/服务端代码。并发工程使用的 Asio 头文件及许可证仍放在原依赖路径。

`wslc/gamet` 保存矩阵博弈、博弈树和均衡分析实验，部分实验配有独立 README、图表与报告。

### 其他学习项目

`PyTorchLearn` 包含 MLP、GCN、GAT、HAN 等模型练习；`Torch` 保存 LibTorch/CUDA 张量示例。`AscendWeb` 保存 React、TypeScript 与 Vite 前端，实际运行需要自行配置可用的后端地址。

`kompier` 保存编译器学习、语言设计与词法相关试验；`kontrol` 保存 Qt 图形模式/显卡控制工具；`wslc/ktuple` 保存 C++ 元组与排序便利设施。其余小工程、模板、笔记见下面的完整目录索引。

## 完整目录索引

以下介绍覆盖本次收录的顶层目录和 `wslc` 下的子目录。用途尚不能从现有说明准确确定的项目，保留为基础练习或试验工程。

### 顶层项目与资料

| 目录 | 内容 |
| --- | --- |
| [AscendWeb](AscendWeb) | Ascend的React、TypeScript、Vite前端 |
| [Board](Board) | C++空壳/注释模板，抽样入口没有实质逻辑 |
| [burujava](burujava) | 目录名含java，源码为C++链表练习 |
| [CCCC](CCCC) | C语言练习 |
| [ccccccccccccccccc](ccccccccccccccccc) | C语言零散练习 |
| [ccu](ccu) | 计算机组成实验：单周期、多周期、流水线CPU及存储器 |
| [COB](COB) | C++小练习 |
| [code](code) | 少量C/C++基础代码 |
| [ConcurrencyPy](ConcurrencyPy) | Python输出语法练习，抽样main.py仅包含print调用 |
| [Contacts](Contacts) | C语言通讯录，含查找、添加等菜单操作 |
| [cpeditor](cpeditor) | 小型C++入口/模板 |
| [cpp](cpp) | C++语言试验 |
| [CS_adder](CS_adder) | Verilog加法器、显示与testbench |
| [CS_ALU](CS_ALU) | Verilog算术逻辑单元及显示、仿真工程 |
| [CS_ALU_TRUE](CS_ALU_TRUE) | 另一份ALU工程，含顶层main.v |
| [csp](csp) | CSP相关C++练习 |
| [C语言大作业](C%E8%AF%AD%E8%A8%80%E5%A4%A7%E4%BD%9C%E4%B8%9A) | 客房管理系统的源码、报告及网页学习资料。 |
| [data_ram](data_ram) | Verilog RAM与显示、仿真工程 |
| [Dev666](Dev666) | 2023年题目及C/C++零散练习 |
| [DTS](DTS) | 线性结构等数据结构习题 |
| [e1e111e1](e1e111e1) | 按A/G/J/K/L编号的竞赛题目代码 |
| [emp1](emp1) | C++算法练习/模板 |
| [file](file) | 网页资源及国庆 C 语言练习。 |
| [Firstcpp](Firstcpp) | 链表、多项式等C++数据结构练习 |
| [FirstCS](FirstCS) | C#银行账户继承示例 |
| [FirstWinFrom](FirstWinFrom) | C# WinForms入门工程 |
| [Game](Game) | C语言三子棋与扫雷 |
| [goHome!!](goHome%21%21) | 早期工程配置/资源 |
| [gsclion](gsclion) | CLion C++工程与资源文件 |
| [highCS](highCS) | C#课程作业：评分计算、数组、员工类等 |
| [homework](homework) | C语言客房管理系统的一份源码 |
| [homework-DS](homework-DS) | 树、栈、队列、遍历等数据结构作业 |
| [HTMLCSS](HTMLCSS) | HTML/CSS网页入门练习 |
| [huffmancode](huffmancode) | 大一下数据结构课设：哈夫曼及扩展压缩 |
| [HuiJia](HuiJia) | C#零散练习 |
| [i want go Home](i%20want%20go%20Home) | C++早期练习 |
| [java](java) | C++数据结构与算法库，含AVL、堆、图、链表、多项式等 |
| [kompier](kompier) | 基于LLVM方向的现代C++编译器学习项目 |
| [kontrol](kontrol) | Qt图形模式/显卡控制工具 |
| [kws](kws) | C++小型试验工程 |
| [LaTeX](LaTeX) | LaTeX学习源文件 |
| [learnalg](learnalg) | 算法学习入口 |
| [luogu](luogu) | 洛谷/算法竞赛题解与个人模板 |
| [luogu2](luogu2) | 另一份算法练习工程 |
| [MarkDown](MarkDown) | 英语、写作等学习笔记。 |
| [matlab](matlab) | MATLAB数学建模、数值与矩阵练习 |
| [microchiken](microchiken) | 汇编语言练习 |
| [mla](mla) | Unity马里奥风格平台游戏练习 |
| [month test](month%20test) | 月测C语言代码 |
| [msvc25](msvc25) | MSVC C++练习 |
| [msvc25116](msvc25116) | MSVC/CMake C++练习 |
| [My project](My%20project) | Unity坦克/射击游戏练习 |
| [My project-2024-7-25](My%20project-2024-7-25) | Unity平台跳跃教程工程 |
| [nwdev5.11](nwdev5.11) | Dev-C++相关模板/练习 |
| [PK](PK) | 随机数据生成与双程序对拍练习 |
| [pracpp](pracpp) | 单文件C++练习 |
| [practice](practice) | C语言综合练习 |
| [PRJAVA](PRJAVA) | Java学习代码，包含Swing绘图程序 |
| [Project1](Project1) | C语言零散练习 |
| [Project2](Project2) | C++零散练习 |
| [py](py) | 实际包含HTML/JavaScript 2048小游戏 |
| [PyTorchLearn](PyTorchLearn) | MLP、GCN、GAT、HAN等机器学习练习 |
| [q1](q1) | C++模板及文件重定向练习 |
| [qc](qc) | Qt Widgets窗口入门工程 |
| [QT0](QT0) | Qt入门工程 |
| [QT000](QT000) | Qt入门工程 |
| [rand_cs](rand_cs) | C# WPF窗口工程 |
| [Rcodeblocks](Rcodeblocks) | Code::Blocks C++入门练习 |
| [Reset](Reset) | C/C++基础、矩阵、排序等练习 |
| [rest](rest) | 算法、KMP及按题号组织的习题 |
| [REV](REV) | C++练习/模板 |
| [searchcpp](searchcpp) | C++查找/基础练习 |
| [SQL](SQL) | 数据库课程SQL脚本及实验报告 |
| [Stack](Stack) | C语言栈实现与练习 |
| [TEMPP](TEMPP) | C++模板/试验工程 |
| [test](test) | C/C++测试与格式化输出练习 |
| [test111111](test111111) | C++零散试验 |
| [test2312321](test2312321) | C++零散试验 |
| [thinkboom](thinkboom) | 笔记、演示讲稿及相关资料 |
| [Torch](Torch) | LibTorch/CUDA文件中的张量入门示例 |
| [tourial_test](tourial_test) | C++教程练习 |
| [tryCsharp](tryCsharp) | C#控制台入门 |
| [untitled123](untitled123) | C++试验入口 |
| [vcpy](vcpy) | Python小练习与虚拟环境 |
| [VS2026](VS2026) | C++工具链/语言试验工程 |
| [vs2026f](vs2026f) | Visual Studio C++练习 |
| [Web](Web) | JavaScript文字冒险/RPG交互练习 |
| [winkkk](winkkk) | C++模块/工具链测试，主体大文件为std.ifc |
| [yes!!](yes%21%21) | C语言早期练习 |
| [zc01](zc01) | C++小型练习 |
| [函数库](%E5%87%BD%E6%95%B0%E5%BA%93) | C语言个人函数与练习库 |
| [手撕四阶行列式](%E6%89%8B%E6%92%95%E5%9B%9B%E9%98%B6%E8%A1%8C%E5%88%97%E5%BC%8F) | C语言四阶行列式计算练习 |
| [未知](%E6%9C%AA%E7%9F%A5) | HTML/CSS/JS网页及素材 |
| [算法库](%E7%AE%97%E6%B3%95%E5%BA%93) | C语言算法片段 |
| [网页](%E7%BD%91%E9%A1%B5) | HTML/CSS/JavaScript 页面、播放器界面及网页素材。 |

### Linux / WSL 学习项目

| 目录 | 内容 |
| --- | --- |
| [wslc/bdzx2501](wslc/bdzx2501) | 按编号保存的C++算法题 |
| [wslc/bhuos](wslc/bhuos) | MIPS教学操作系统实验与报告 |
| [wslc/C](wslc/C) | C语言单文件练习 |
| [wslc/CL25018](wslc/CL25018) | C++竞赛题目与模板库 |
| [wslc/concurrency](wslc/concurrency) | C++并发与网络服务试验 |
| [wslc/cs144](wslc/cs144) | CS144/minnow计算机网络实验 |
| [wslc/cursor](wslc/cursor) | C++试验工程 |
| [wslc/dev](wslc/dev) | C++小型试验工程 |
| [wslc/e1](wslc/e1) | C++小型试验工程 |
| [wslc/gamet](wslc/gamet) | 博弈论实验：矩阵、博弈树与均衡分析 |
| [wslc/kkkzbh](wslc/kkkzbh) | C++试验工程 |
| [wslc/ktuple](wslc/ktuple) | C++元组与排序便利设施扩展库 |
| [wslc/learnRM](wslc/learnRM) | 数据库/C++依赖试验，含sqlpp23 |
| [wslc/luogu](wslc/luogu) | Linux侧C++算法工程 |
| [wslc/matij](wslc/matij) | C++题目、Trie练习 |
| [wslc/net](wslc/net) | C++网络试验入口 |
| [wslc/os](wslc/os) | 个人操作系统项目源码、文档与磁盘镜像 |
| [wslc/python](wslc/python) | 数学建模、优化与微分方程练习 |
| [wslc/qq](wslc/qq) | C++客户端/服务端练习 |
| [wslc/test_py_call_cpp](wslc/test_py_call_cpp) | Python调用C++的接口试验 |
| [wslc/tmp](wslc/tmp) | 临时试验文件 |
| [wslc/VHDL](wslc/VHDL) | FPGA/VHDL课程实验、报告、演示视频 |
| [wslc/考试专用](wslc/%E8%80%83%E8%AF%95%E4%B8%93%E7%94%A8) | 算法考试用C++模板 |

### 压缩包中的差异版本

[archive-snapshots](archive-snapshots/README.md) 保存旧压缩包中与展开目录不同的源码、工程配置或资料，并列出原始来源与对应路径。CPU、FPGA 和数学建模的差异文件可由该索引逐项查看。

## 如何使用

1. 根据目录索引选择一个工程，先阅读它自己的 README、作业说明或实验报告。
2. 根据 `.sln` / `.csproj`、`CMakeLists.txt`、`package.json`、Unity 配置或 FPGA 工程文件确定开发环境。
3. 安装该工程实际声明的依赖，配置测试输入及必要的外部服务，再运行其入口程序。

本仓库没有统一构建命令。部分 C/C++ 程序使用 Windows API、特定编译器或较新的语言特性；部分课程代码需要模拟器、开发板或课程框架。归档过程核对了文件内容和目录结构，未逐个编译运行所有工程。

## 收录范围与来源

- 保留学习源码、工程配置、依赖清单、必要素材、实验说明和报告。
- 通过 `.gitignore` 排除构建产物、虚拟环境、依赖安装目录、Unity 缓存、IDE 个人配置、运行账户数据、私密配置及大体积实验数据。
- 子项目以源码快照收录，合集中不包含各子项目原有 Git 历史。
- 课程框架、教学模板、第三方库和游戏素材沿用各自来源与许可。已存在的许可证和来源说明随目录保留；阅读和复用时请一并核对。
- 部分目录含合作作业、教程练习或参考代码，应结合文件署名、注释和课程说明理解各自贡献。仓库名下收录的全部文件不能统一视作独立原创作品。

这个合集用于记录大学期间逐步接触不同语言、算法、系统和开发工具的学习过程。
