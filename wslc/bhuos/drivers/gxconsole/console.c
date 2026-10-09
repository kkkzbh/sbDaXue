/*
 *  文件说明：GXemul 控制台最小示例（Hello World）
 *  版权/许可：公共领域（Public Domain）
 *  目的：演示通过内存映射 I/O 向模拟器控制台输出字符，并提供停止接口
 *  备注：本文件仅添加中文注释，不更改任何可执行语义
 */

#include "dev_cons.h"  // 引入控制台设备的寄存器基地址与偏移量定义

/* 说明：将常量强制转换为 32 位有符号整数是为了在 64 位编译模式下
 *       在 MIPS 架构上得到正确的符号扩展，从而形成期望的高半区偏移。
 */
#define	PHYSADDR_OFFSET		((signed int)0x80000000)  // 物理地址偏移（KSEG0/KSEG1 基址偏移）


#define	PUTCHAR_ADDRESS		(PHYSADDR_OFFSET +    /* 输出字符寄存器的物理总线地址 */ \
				DEV_CONS_ADDRESS + DEV_CONS_PUTGETCHAR)  // 控制台字符寄存器偏移
#define	HALT_ADDRESS		(PHYSADDR_OFFSET +    /* 触发停止的寄存器物理总线地址 */ \
				DEV_CONS_ADDRESS + DEV_CONS_HALT)       // 控制台停止寄存器偏移


void printcharc(char ch)  // 将单个字符写入控制台设备
{
	// 函数体开始
	*((volatile unsigned char *) PUTCHAR_ADDRESS) = ch;  // 通过 MMIO 向字符寄存器写入 ch
}	// 函数体结束


void halt(void)  // 请求模拟器/硬件停止运行
{
	// 函数体开始
	*((volatile unsigned char *) HALT_ADDRESS) = 0;  // 向停止寄存器写入任意值（此处为 0）
}	// 函数体结束


void printstr(char *s)  // 逐字符输出以 '\0' 结尾的字符串
{
	// 函数体开始
	while (*s)                 // 当前字符非空终止符时继续
		printcharc(*s++);   // 输出当前字符并自增指针
}	// 函数体结束
