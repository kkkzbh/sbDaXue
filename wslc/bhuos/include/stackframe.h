#include <asm/regdef.h>     // 通用寄存器别名定义
#include <asm/cp0regdef.h>  // CP0 寄存器字段定义
#include <asm/asm.h>        // 汇编辅助宏（LEAF/NESTED 等）
#include <trap.h>           // Trapframe 偏移宏

.macro STI                // 开中断（设置 Status.IE）并确保内核位有效
	mfc0	t0, CP0_STATUS   // 读取 CP0 Status
	li	t1, (STATUS_CU0 | 0x1) // 准备置位：保持内核模式并打开全局中断
	or	t0, t1            // 合并标志
	mtc0	t0, CP0_STATUS   // 写回 CP0 Status
.endm                     // 宏结束


.macro CLI                // 关中断（清除 Status.IE）
	mfc0	t0, CP0_STATUS   // 读取 CP0 Status
	li	t1, (STATUS_CU0 | 0x1) // 保持内核位，其余按位操作
	or	t0, t1            // 先确保 CU0/IE 位有效
	xor	t0, 0x1          // 翻转 IE 置 0
	mtc0	t0, CP0_STATUS   // 写回 CP0 Status
.endm                     // 宏结束

.macro SAVE_ALL            // 保存通用寄存器与关键 CP0 寄存器到 Trapframe
	mfc0	k0, CP0_STATUS  // 取 Status，检测异常来源
	sll	k0, 3           // 移位辅助判断
	bltz	k0, 1f         // 小于 0 则跳到 1（分支延迟槽下一条 nop）
	nop                 // 延迟槽
1:                      // 标签 1
	move	k0, sp        // 备份当前 sp
	get_sp             // 根据异常来源切换到内核栈
	move	k1, sp        // 保存新的 sp
	subu	sp, k1, TF_SIZE // 为 Trapframe 预留空间
	sw	k0, TF_REG29(sp)  // 保存原 sp 到 tf
	sw	$2, TF_REG2(sp)   // 保存 v0
	mfc0	v0, CP0_STATUS  // 读取 Status
	sw	v0, TF_STATUS(sp) // 保存 Status
	mfc0	v0, CP0_CAUSE   // 读取 Cause
	sw	v0, TF_CAUSE(sp)  // 保存 Cause
	mfc0	v0, CP0_EPC     // 读取 EPC
	sw	v0, TF_EPC(sp)    // 保存 EPC
	mfc0	v0, CP0_BADVADDR // 读取错误地址
	sw	v0, TF_BADVADDR(sp) // 保存错误地址
	mfhi	v0              // 读取 HI
	sw	v0, TF_HI(sp)     // 保存 HI
	mflo	v0              // 读取 LO
	sw	v0, TF_LO(sp)     // 保存 LO
	sw	$0,  TF_REG0(sp)  // 保存 r0
	sw	$1,  TF_REG1(sp)  // 保存 r1
	sw	$3,  TF_REG3(sp)  // 保存 r3
	sw	$4,  TF_REG4(sp)  // 保存 r4
	sw	$5,  TF_REG5(sp)  // 保存 r5
	sw	$6,  TF_REG6(sp)  // 保存 r6
	sw	$7,  TF_REG7(sp)  // 保存 r7
	sw	$8,  TF_REG8(sp)  // 保存 r8
	sw	$9,  TF_REG9(sp)  // 保存 r9
	sw	$10, TF_REG10(sp) // 保存 r10
	sw	$11, TF_REG11(sp) // 保存 r11
	sw	$12, TF_REG12(sp) // 保存 r12
	sw	$13, TF_REG13(sp) // 保存 r13
	sw	$14, TF_REG14(sp) // 保存 r14
	sw	$15, TF_REG15(sp) // 保存 r15
	sw	$16, TF_REG16(sp) // 保存 r16
	sw	$17, TF_REG17(sp) // 保存 r17
	sw	$18, TF_REG18(sp) // 保存 r18
	sw	$19, TF_REG19(sp) // 保存 r19
	sw	$20, TF_REG20(sp) // 保存 r20
	sw	$21, TF_REG21(sp) // 保存 r21
	sw	$22, TF_REG22(sp) // 保存 r22
	sw	$23, TF_REG23(sp) // 保存 r23
	sw	$24, TF_REG24(sp) // 保存 r24
	sw	$25, TF_REG25(sp) // 保存 r25
	sw	$26, TF_REG26(sp) // 保存 r26
	sw	$27, TF_REG27(sp) // 保存 r27
	sw	$28, TF_REG28(sp) // 保存 r28
	sw	$30, TF_REG30(sp) // 保存 r30
	sw	$31, TF_REG31(sp) // 保存 r31
.endm                    // 宏结束

.macro RESTORE_SOME        // 恢复部分寄存器与关键 CP0 状态
	.set	mips1           // 指定指令集级别
	mfc0	t0, CP0_STATUS  // 读取 Status
	ori	t0, 0x3         // 保持内核位/中断位的合法组合
	xori	t0, 0x3         // 清理低两位
	mtc0	t0, CP0_STATUS  // 写回 Status
	lw	v0, TF_STATUS(sp) // 取保存的 Status
	li	v1, 0xff00       // 掩码准备
	and	t0, v1           // 保留高位
	nor	v1, $0, v1      // 取反得到低位掩码
	and	v0, v1           // 清理 v0 对应位
	or	v0, t0            // 合并
	mtc0	v0, CP0_STATUS  // 应用新的 Status
	lw	v1, TF_LO(sp)     // 取 LO
	mtlo	v1              // 恢复 LO
	lw	v0, TF_HI(sp)     // 取 HI
	lw	v1, TF_EPC(sp)    // 取 EPC
	mthi	v0              // 恢复 HI
	mtc0	v1, CP0_EPC     // 恢复 EPC
	lw	$31, TF_REG31(sp) // 恢复 r31
	lw	$30, TF_REG30(sp) // 恢复 r30
	lw	$28, TF_REG28(sp) // 恢复 r28
	lw	$25, TF_REG25(sp) // 恢复 r25
	lw	$24, TF_REG24(sp) // 恢复 r24
	lw	$23, TF_REG23(sp) // 恢复 r23
	lw	$22, TF_REG22(sp) // 恢复 r22
	lw	$21, TF_REG21(sp) // 恢复 r21
	lw	$20, TF_REG20(sp) // 恢复 r20
	lw	$19, TF_REG19(sp) // 恢复 r19
	lw	$18, TF_REG18(sp) // 恢复 r18
	lw	$17, TF_REG17(sp) // 恢复 r17
	lw	$16, TF_REG16(sp) // 恢复 r16
	lw	$15, TF_REG15(sp) // 恢复 r15
	lw	$14, TF_REG14(sp) // 恢复 r14
	lw	$13, TF_REG13(sp) // 恢复 r13
	lw	$12, TF_REG12(sp) // 恢复 r12
	lw	$11, TF_REG11(sp) // 恢复 r11
	lw	$10, TF_REG10(sp) // 恢复 r10
	lw	$9,  TF_REG9(sp)  // 恢复 r9
	lw	$8,  TF_REG8(sp)  // 恢复 r8
	lw	$7,  TF_REG7(sp)  // 恢复 r7
	lw	$6,  TF_REG6(sp)  // 恢复 r6
	lw	$5,  TF_REG5(sp)  // 恢复 r5
	lw	$4,  TF_REG4(sp)  // 恢复 r4
	lw	$3,  TF_REG3(sp)  // 恢复 r3
	lw	$2,  TF_REG2(sp)  // 恢复 r2
	lw	$1,  TF_REG1(sp)  // 恢复 r1
.endm                    // 宏结束
	
.macro RESTORE_ALL        // 恢复所有寄存器并恢复 sp
	RESTORE_SOME           // 部分恢复
	lw	sp, TF_REG29(sp)    // 恢复原栈指针
.endm                    // 宏结束

.set	noreorder           // 禁止延迟槽重排，按顺序发射
.macro RESTORE_ALL_AND_RET // 恢复并返回到 EPC
	RESTORE_SOME           // 部分恢复
	lw	k0, TF_EPC(sp)      // 取 EPC
	lw	sp, TF_REG29(sp)    // 恢复 sp
	jr	k0                  // 跳回 EPC
	rfe                    // 从异常返回
.endm                    // 宏结束


.macro get_sp             // 根据异常来源选择合适的栈指针
	mfc0	k1, CP0_CAUSE   // 读取 Cause
	andi	k1, 0x107C     // 提取相关位
	xori	k1, 0x1000     // 与掩码比较
	bnez	k1, 1f         // 不为零，走 1 分支
	nop                 // 延迟槽
	li	sp, 0x82000000   // 进入内核栈（定值）
	j	2f                // 跳到 2
	nop                 // 延迟槽
1:	bltz	sp, 2f         // 若 sp 为内核态（负数），直接用之
	nop                 // 延迟槽
	lw	sp, KERNEL_SP    // 否则从保存处取出内核 sp
	nop                 // 延迟槽
2:	nop                 // 落点占位
.endm                    // 宏结束
