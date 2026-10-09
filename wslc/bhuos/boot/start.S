/*
 * Copyright (C) 2001 MontaVista Software Inc.
 * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net
 *
 * 本文件为系统引导阶段的 MIPS 汇编入口代码，负责建立异常向量、
 * 关闭中断与监视器、初始化缓存/堆栈并跳转到 C 入口 main。
 * 仅添加中文注释，不改动任何指令或伪指令的语义。
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */

#include <asm/regdef.h>        // 引入 MIPS 寄存器别名（如 t0/k0/sp 等）
#include <asm/cp0regdef.h>     // 引入 CP0 寄存器编号与字段常量（如 CP0_STATUS）
#include <asm/asm.h>           // 引入汇编辅助宏（NESTED/LEAF/END/NOP 等）

.section .text.exc_vec3        // 定义异常向量段，放置“通用异常入口”代码
NESTED(except_vec3, 0, sp)     // 定义可嵌套异常处理入口：名字/帧大小=0/保存基准寄存器sp
		.set	noat            // 临时关闭汇编器对 $at 寄存器的隐式使用（手工管理）
		.set	noreorder       // 关闭指令重排，确保分支延迟槽等顺序严格按书写执行
		/*
		 * 推迟寄存器保存：仅在确定需要时再保存，减少现场开销。
		 */
1:	// j 1b                   // 若需要可自旋回到标签1（此处保持注释而不跳转）
	nop                        // 占位的空操作，对齐/延迟槽安全填充

		mfc0	k1,CP0_CAUSE    // 读取 CP0 CAUSE，得到当前异常原因码
		la	k0,exception_handlers // 加载异常分发表基地址到 k0
		/*
		 * MIPS 传统最多支持 32 类异常，此处分派表按原因码（5:2 位）
		 * 进行索引，将来亦可扩展为软件异常分派。
		 */

		andi	k1,0x7c         // 提取 CAUSE[6:2]（异常码）作为字节偏移
		addu	k0,k1           // 表基地址 + 偏移，得到当前异常的处理例程入口地址项
		lw	k0,(k0)          // 取出真正的处理例程入口地址到 k0
		NOP                 // 宏 NOP：部分工具链需要显式延迟，保持安全
		jr	k0              // 跳转到具体异常处理函数
		nop                 // 延迟槽填充（保持流水线语义正确）
END(except_vec3)              // 结束 except_vec3 符号定义与堆栈框架描述
		.set	at              // 重新允许汇编器使用 $at 寄存器


.data                       // 进入普通数据段，定义一些全局变量
			.globl mCONTEXT   // 导出 mCONTEXT：保存当前上下文（如当前栈顶/入口）
mCONTEXT:                   // mCONTEXT 符号地址
			.word 0          // 预留 1 个字（32 位），初值 0

			.globl delay      // 导出 delay：可由测试/延时使用的全局变量占位
delay:                     // delay 符号地址
			.word 0          // 预留 1 个字，初值 0

			.globl tlbra      // 导出 tlbra：记录最近一次 TLB 相关信息的占位变量
tlbra:                     // tlbra 符号地址
			.word 0          // 预留 1 个字，初值 0

			.section .data.stk // 单独的栈空间段，便于链接脚本放置到合适位置
KERNEL_STACK:              // 内核栈起始符号
			.space 0x8000    // 预留 32KB 栈空间（0x8000 字节）


			.text            // 回到代码段，定义启动入口
LEAF(_start)               // 定义叶子函数 _start（无保存被调者寄存器的调用约定）
	
	.set	mips2            // 指示使用 MIPS II 指令集特性
	.set	reorder          // 允许编译器/汇编器做安全的指令重排（以下显式控制关键处再关闭）

	/* Disable interrupts */ // 关闭所有中断，进入受控引导环境
	mtc0	zero, CP0_STATUS // 状态寄存器清零：IE=0，禁用全局中断并设为内核态

        /* Disable watch exception. */ // 关闭监视点异常，避免意外陷入
        mtc0    zero, CP0_WATCHLO     // 清 WATCHLO（地址/掩码）
        mtc0    zero, CP0_WATCHHI     // 清 WATCHHI（控制位）

	/* disable kernel mode cache */ // 配置内核态缓存行为（关闭或设为直写直取以简化引导）
	mfc0	t0, CP0_CONFIG     // 读出 CONFIG 寄存器到 t0
	and	t0, ~0x7          // 清低 3 位 K0 域（缓存策略选择位）
	ori	t0, 0x2           // 设为 0b010：通常含义为直写直取/非缓存（依具体核而定）
	mtc0	t0, CP0_CONFIG     // 回写配置，立即生效或在同步后生效

	/* set up stack */       // 建立引导期栈顶（与链接脚本/内存布局一致）
	li	sp, 0x80400000        // 将内核栈顶地址装入 sp

	li		t0,0x80400000     // 记录当前“上下文”的基址（此处简单记为栈顶）
	sw		t0,mCONTEXT       // 保存到全局变量 mCONTEXT，供 C 代码调试/参考
	
	/* jump to main */       // 跳转到 C 入口函数 main，开始内核初始化
	jal	main                // 调用 main（返回则继续执行下方死循环）
			                  // 空白行仅为可读性
loop:                      // 若 main 返回，进入自旋，防止落入未知区域
	j	loop                  // 无条件跳回 loop，自旋等待
	nop                      // 分支延迟槽填充，保证流水线语义
END(_start)                // 结束 _start 的符号与元信息定义
