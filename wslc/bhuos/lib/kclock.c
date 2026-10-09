// 中文注释：运行时钟与相关 NVRAM 操作（本实验仅启用时钟初始化）
#include <kclock.h> // 中文注释：时钟与定时器相关寄存器/常量定义

extern void set_timer(); // 中文注释：在汇编中设置时钟中断源、内核栈等

void
kclock_init(void) // 中文注释：初始化内核时钟（设置时钟中断）
{
	set_timer(); // 中文注释：调用底层汇编例程使能时钟与相关状态位
}

