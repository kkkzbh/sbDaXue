#include <asm/regdef.h> // 中文注释：寄存器别名
#include <asm/cp0regdef.h> // 中文注释：CP0 寄存器定义
#include <asm/asm.h> // 中文注释：汇编宏与属性
#include <stackframe.h> // 中文注释：Trapframe 字段偏移

.macro	__build_clear_sti // 中文注释：宏——打开中断
	STI // 中文注释：允许中断
.endm

.macro	__build_clear_cli // 中文注释：宏——关闭中断
	CLI // 中文注释：禁止中断
.endm

.macro	BUILD_HANDLER exception handler clear // 中文注释：异常入口构造宏
	.align	5 // 中文注释：按 32 字节对齐
	NESTED(handle_\exception, TF_SIZE, sp)  // 中文注释：定义异常入口符号

nop // 中文注释：占位

	SAVE_ALL				 // 中文注释：保存全部寄存器
	__build_clear_\clear // 中文注释：根据参数开/关中断
	.set	at // 中文注释：允许使用 $at
	move	a0, sp // 中文注释：a0 = Trapframe 指针
	jal	\handler // 中文注释：调用对应的 C 处理函数
	nop // 中文注释：延迟槽
	j	ret_from_exception // 中文注释：跳到通用返回路径
	nop // 中文注释：延迟槽
	END(handle_\exception)
.endm

FEXPORT(ret_from_exception) // 中文注释：导出异常返回路径
	.set noat // 中文注释：暂禁 $at 自动使用
	.set noreorder // 中文注释：不重排
	RESTORE_SOME // 中文注释：恢复部分寄存器
	.set at // 中文注释：恢复 $at
	lw	k0,TF_EPC(sp) // 中文注释：取 EPC
	lw	sp,TF_REG29(sp) // 中文注释：恢复 sp（释放异常栈）
	nop // 中文注释：占位
	jr	k0 // 中文注释：跳回 EPC
	rfe // 中文注释：从异常返回



.set noreorder // 中文注释：不重排
.align	5 // 中文注释：入口对齐
NESTED(handle_int, TF_SIZE, sp) // 中文注释：硬件中断处理入口

nop // 中文注释：占位

SAVE_ALL // 中文注释：保存寄存器
CLI // 中文注释：关闭中断
.set	at // 中文注释：允许 $at
mfc0	t0, CP0_CAUSE // 中文注释：读 CAUSE
mfc0	t2, CP0_STATUS // 中文注释：读 STATUS
and	t0, t2 // 中文注释：屏蔽关闭的中断

andi	t1, t0, STATUSF_IP4 // 中文注释：判断 IP4（时钟中断）
bnez	t1, timer_irq // 中文注释：若为时钟中断则跳转
nop // 中文注释：延迟槽
END(handle_int) // 中文注释：结束

	.extern delay

timer_irq: // 中文注释：时钟中断处理

1:	j	sched_yield // 中文注释：触发调度
	nop
	/*li t1, 0xff
	lw    t0, delay
	addu  t0, 1
	sw	t0, delay
	beq	t0,t1,1f	
	nop*/
	j	ret_from_exception // 中文注释：从异常返回
	nop // 中文注释：延迟槽

LEAF(do_reserved) // 中文注释：保留异常占位
END(do_reserved)

	.extern tlbra
.set	noreorder
NESTED(do_refill,0 , sp)
			//li	k1, '?'
			//sb	k1, 0x90000000
			.extern	mCONTEXT
//this "1" is important
1:			//j 1b
			nop
			lw		k1,mCONTEXT
			and		k1,0xfffff000
				mfc0		k0,CP0_BADVADDR
				srl		k0,20
				and		k0,0xfffffffc
			addu		k0,k1
			
			lw		k1,0(k0)
			nop
					move		t0,k1
					and		t0,0x0200
					beqz		t0,NOPAGE
			nop
			and		k1,0xfffff000
				mfc0		k0,CP0_BADVADDR
				srl		k0,10
				and		k0,0xfffffffc
				and		k0,0x00000fff
			addu		k0,k1

			or		k0,0x80000000
			lw		k1,0(k0)
			nop
					move		t0,k1
					and		t0,0x0200
					beqz		t0,NOPAGE
			nop
			move		k0,k1
			and		k0,0x1
			beqz		k0,NoCOW
			nop
			and		k1,0xfffffbff
NoCOW:
			mtc0		k1,CP0_ENTRYLO0
			nop
			tlbwr

			j		2f
			nop
NOPAGE:
//3: j 3b
nop // 中文注释：延迟槽
				mfc0		a0,CP0_BADVADDR // 中文注释：a0 = 故障地址
				lw		a1,mCONTEXT // 中文注释：a1 = 地址空间上下文
				nop // 中文注释：延迟槽
				
			sw	 	ra,tlbra
			jal		pageout
			nop
//3: j 3b
nop // 中文注释：占位（调试分支去除）
				lw		ra,tlbra // 中文注释：恢复返回地址
				nop // 中文注释：延迟槽

				j	1b // 中文注释：回到重试点
2:			nop // 中文注释：延迟槽

				jr		ra // 中文注释：返回上一层
				nop // 中文注释：延迟槽
END(do_refill) // 中文注释：TLB 重填处理结束



BUILD_HANDLER reserved do_reserved cli // 中文注释：保留异常入口
BUILD_HANDLER tlb	do_refill	cli // 中文注释：TLB 异常入口
BUILD_HANDLER mod	page_fault_handler cli // 中文注释：修改异常入口
