#include <asm/regdef.h> // 中文注释：寄存器别名
#include "../include/asm/cp0regdef.h" // 中文注释：CP0 寄存器定义（相对路径）
#include <asm/asm.h> // 中文注释：汇编宏与框架
#include <trap.h> // 中文注释：Trapframe 字段偏移等
			.data
			.global	KERNEL_SP; // 中文注释：导出内核栈指针符号
KERNEL_SP:
			.word		0 // 中文注释：保存当前内核栈指针的存储单元



		.text
		.set noreorder // 中文注释：禁止指令重排
LEAF(env_pop_tf) // 中文注释：恢复 Trapframe 并返回用户态
.set	mips1          
	nop    // 中文注释：占位（对应去除的调试跳转）
		move		k0,a0 // 中文注释：k0 指向 Trapframe
		mtc0	a1,CP0_ENTRYHI // 中文注释：设置 ENTRYHI（ASID/高位 VPN）

		mfc0	t0,CP0_STATUS                    // 中文注释：读取状态寄存器
		ori	t0,0x3                          // 中文注释：置位 IE/EXL 位以便后续安全更新
		xori	t0,0x3                          // 中文注释：清除 EXL/IE 恢复正常
		mtc0	t0,CP0_STATUS                    // 中文注释：写回状态寄存器
				 
		lw	v1,TF_LO(k0)                                       // 中文注释：恢复 LO
		mtlo	v1                               // 中文注释：写 LO
		lw	v0,TF_HI(k0)                     // 中文注释：读取 HI
		lw	v1,TF_EPC(k0)                    // 中文注释：读取 EPC
		mthi	v0                               // 中文注释：写 HI
		mtc0	v1,CP0_EPC                       // 中文注释：写 EPC（返回地址）
		lw	$31,TF_REG31(k0)                 // 中文注释：恢复 $ra
		lw	$30,TF_REG30(k0)     // 中文注释：恢复 $s8/fp 
		lw	$29,TF_REG29(k0)            // 中文注释：恢复 $sp
		lw	$28,TF_REG28(k0)                 // 中文注释：恢复 $gp
		lw	$25,TF_REG25(k0)                 // 中文注释：恢复 t9
		lw	$24,TF_REG24(k0)                 // 中文注释：恢复 $s8 以外的通用寄存器（按表）
		lw	$23,TF_REG23(k0)                 
		lw	$22,TF_REG22(k0)                 
		lw	$21,TF_REG21(k0)                 
		lw	$20,TF_REG20(k0)                 
		lw	$19,TF_REG19(k0)                 
		lw	$18,TF_REG18(k0)                 
		lw	$17,TF_REG17(k0)                 
		lw	$16,TF_REG16(k0)                 
		lw	$15,TF_REG15(k0)                 
		lw	$14,TF_REG14(k0)                 
		lw	$13,TF_REG13(k0)                 
		lw	$12,TF_REG12(k0)                 
		lw	$11,TF_REG11(k0)                 
		lw	$10,TF_REG10(k0)                 
		lw	$9,TF_REG9(k0)                   
		lw	$8,TF_REG8(k0)                   
		lw	$7,TF_REG7(k0)                   
		lw	$6,TF_REG6(k0)                   
		lw	$5,TF_REG5(k0)                   
		lw	$4,TF_REG4(k0)                   
		lw	$3,TF_REG3(k0)                   
		lw	$2,TF_REG2(k0)                   
		lw	$1,TF_REG1(k0) // 中文注释：按 Trapframe 恢复所有寄存器

		lw	k1,TF_PC(k0) // 中文注释：取出要返回的 PC

		lw	k0,TF_STATUS(k0)                 // 中文注释：读取保存的 Status
		nop					 // 中文注释：避免相关性冒险
		mtc0	k0,CP0_STATUS // 中文注释：写回 Status

		j	k1 // 中文注释：跳转回用户态指令地址
		rfe // 中文注释：从异常返回，恢复模式位
		nop // 中文注释：延迟槽

END(env_pop_tf)

LEAF(lcontext) // 中文注释：保存当前地址空间上下文指针（mCONTEXT）
		.extern	mCONTEXT
		sw		a0,mCONTEXT // 中文注释：将 a0 存入全局 mCONTEXT
		jr	ra // 中文注释：返回
		nop // 中文注释：延迟槽
END(lcontext)

