#include <asm/regdef.h> // 引入 asm/regdef.h，以便使用对应定义
#include <asm/cp0regdef.h> // 引入 asm/cp0regdef.h，以便使用对应定义
#include <asm/asm.h> // 引入 asm/asm.h，以便使用对应定义
// 用这一行占位，把相邻逻辑自然隔开
// 按当前 ASID/虚拟页选择性失效并清空对应 TLB 项
LEAF(tlb_out)               # 进入函数（宏定义，设置入口） // 声明叶子例程入口，按照惯例保存上下文
// 1: j 1b
nop                         # 延迟槽空操作，避免相关冒险 // 用空操作占位，避免紧邻指令相互牵制
	mfc0	k1,CP0_ENTRYHI      # 备份原 EntryHi 到 k1（保存 ASID/VA 高位） // 协调 CP0/TLB 指令，让缺页路径可控
	mtc0	a0,CP0_ENTRYHI      # 将参数 a0 写入 EntryHi（目标 ASID/VA） // 围绕 TLB 的寄存器做读写，保持映射干净
	nop                     # CP0 写后插入 NOP，等待生效 // 用空操作占位，避免紧邻指令相互牵制
	                        # 下面执行 tlbp 探测并可能 tlbwi 覆写
	# 根据 EntryHi 在 TLB 中探测匹配项（索引写入 CP0_INDEX）
	tlbp                    # TLB probe：按 EntryHi 查找并设置 INDEX // 协调 CP0/TLB 指令，让缺页路径可控
	nop                     # 探测后插入 NOP，避免相关冲突 // 这一句 NOP 只是保持时序稳定
	nop // 插入 NOP 让流水线有时间消除冒险
	nop // 用空操作占位，避免紧邻指令相互牵制
	nop // 这一句 NOP 只是保持时序稳定
	mfc0	k0,CP0_INDEX        # 读取探测到的索引 INDEX 至 k0 // 围绕 TLB 的寄存器做读写，保持映射干净
	# 若未命中（INDEX 为负），跳转 NOFOUND
	bltz	k0,NOFOUND          # 未命中则无需清除，直接收尾 // 根据分支条件决定是否跳转到标签
	nop                     # 延迟槽 NOP // 插入 NOP 让流水线有时间消除冒险
	# 命中：构造空条目写回以实现失效
	mtc0	zero,CP0_ENTRYHI    # 清空 EntryHi（匹配键） // 协调 CP0/TLB 指令，让缺页路径可控
	mtc0	zero,CP0_ENTRYLO0   # 清空低半页（EntryLo0） // 围绕 TLB 的寄存器做读写，保持映射干净
	nop                     # CP0 写后 NOP // 用空操作占位，避免紧邻指令相互牵制
	# 按索引写回覆盖（wipe）
	tlbwi                   # TLB write indexed：用空条目覆盖 // 操作 TLB 项，确保地址转换缓存最新
NOFOUND:                  # 未命中路径标签 // 这个标签供分支或异常路径直接跳转
// 保留这个位置的留白，阅读时能迅速分段
	mtc0	k1,CP0_ENTRYHI      # 恢复原 EntryHi（恢复 ASID/VA） // 围绕 TLB 的寄存器做读写，保持映射干净
// 用这一行占位，把相邻逻辑自然隔开
	j	ra                    # 返回调用者 // 跳转到目标地址，衔接控制流
	nop                     # 延迟槽 NOP // 插入 NOP 让流水线有时间消除冒险
END(tlb_out)              # 函数结束（宏定义，设置出口） // 标记叶子例程结束，收尾符号
