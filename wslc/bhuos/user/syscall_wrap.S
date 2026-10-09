#include <asm/regdef.h>
#include <asm/cp0regdef.h>
#include <asm/asm.h>


LEAF(msyscall)
    // 执行一次 `syscall` 指令并从 msyscall 返回（按约定寄存器传参）
//	sw	a0, 0(sp)    // 如需保存参数可压栈（保留为注释）
//	sw	a1, 4(sp)
//	sw	a2, 8(sp)
//	sw	a3, 12(sp)
	syscall           // 触发陷阱进入内核
	jr	ra            // 从内核返回后回到调用点
	nop               // 延迟槽指令
END(msyscall)

