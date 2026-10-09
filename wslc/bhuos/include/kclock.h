#ifndef _KCLOCK_H_ // 头文件防重包含开始
#define _KCLOCK_H_ // 定义本头文件的防重包含宏

#define IO_RTC 0xb5000100 // 实时时钟（RTC）寄存器基地址

#ifndef __ASSEMBLER__ // 仅在 C 语言环境下声明
void kclock_init(void); // 初始化时钟/计时器
#endif // 结束 __ASSEMBLER__ 条件

#endif // 结束防重包含
