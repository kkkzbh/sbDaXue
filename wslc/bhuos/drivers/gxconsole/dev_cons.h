#ifndef	TESTMACHINE_CONS_H  // 头文件保护：防止重复包含
#define	TESTMACHINE_CONS_H  // 定义保护宏

/*
 *  文件说明：GXemul 中 "cons"（控制台）设备使用的寄存器常量定义
 *  许可：公共领域（Public Domain）
 *  作用：提供控制台设备的基地址、寄存器空间大小及关键寄存器偏移
 */


//#define	DEV_CONS_ADDRESS		0x180003f8   // 旧版/备选控制台基地址（保留以供参考）
#define	DEV_CONS_ADDRESS		0x10000000   // 控制台设备基地址（物理）
#define	DEV_CONS_LENGTH			0x0000000000000020  // 寄存器空间长度：32 字节
#define	    DEV_CONS_PUTGETCHAR		    0x0000  // 读/写单字符寄存器的偏移
#define	    DEV_CONS_HALT		    0x0010  // 写入非零/任意值以触发停止


#endif	/*  TESTMACHINE_CONS_H —— 头文件保护结束 */
