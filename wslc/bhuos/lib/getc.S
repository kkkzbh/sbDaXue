#include <asm/regdef.h> // 中文注释：通用寄存器别名定义
#include <asm/cp0regdef.h> // 中文注释：MIPS CP0 寄存器定义
#include <asm/asm.h> // 中文注释：汇编帮助宏与属性

.set noreorder // 中文注释：禁止编译器/汇编器重排指令
LEAF(sys_cgetc) // 中文注释：定义叶子函数 sys_cgetc（从设备读取一个字节）

1:	lb	t0, 0x90000000 // 中文注释：从内存映射 I/O 地址读取一字节到 t0
	beqz	t0, 1b // 中文注释：若为 0 则忙等待，继续轮询
	nop // 中文注释：延迟槽空指令
	move	v0,t0 // 中文注释：返回值放入 v0
	jr	ra // 中文注释：返回到调用者
	nop // 中文注释：延迟槽空指令
END(sys_cgetc) // 中文注释：函数结束标记 
