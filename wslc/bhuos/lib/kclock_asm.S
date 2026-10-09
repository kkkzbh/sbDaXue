#include <asm/regdef.h> // 中文注释：通用寄存器别名定义
#include <asm/cp0regdef.h> // 中文注释：CP0 寄存器与位定义
#include <asm/asm.h> // 中文注释：汇编框架宏
#include <kclock.h> // 中文注释：时钟相关常量与符号



.macro	setup_c0_status set clr // 中文注释：设置 CP0_STATUS 的指定位（先 OR 后 XOR 清除）
	.set	push // 中文注释：保存当前汇编选项
	mfc0	t0, CP0_STATUS // 中文注释：读出 CP0 Status 到 t0
	or	t0, \set|\clr // 中文注释：先置位 set 和 clr 指定的位
	xor	t0, \clr // 中文注释：再对 clr 指定的位取反达到清零效果
	mtc0	t0, CP0_STATUS			 // 中文注释：写回 CP0 Status
	.set	pop // 中文注释：恢复汇编选项
.endm

	.text // 中文注释：代码段开始
LEAF(set_timer) // 中文注释：设置定时器与内核栈指针

	li t0, 0x01 // 中文注释：装载常数 1 到 t0
	sb t0, 0xb5000100 // 中文注释：向设备寄存器写入以使能时钟（内存映射 IO）
	sw	sp, KERNEL_SP // 中文注释：保存当前内核栈指针到全局符号 KERNEL_SP
setup_c0_status STATUS_CU0|0x1001 0 // 中文注释：打开内核态/中断等必要状态位
	jr ra // 中文注释：返回调用者

	nop // 中文注释：延迟槽空指令
END(set_timer) // 中文注释：函数结束
