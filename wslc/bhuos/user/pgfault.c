// 用户态缺页异常处理：使用汇编封装调用 C 函数。
// 汇编封装位于 entry.S 中。

#include "lib.h"
#include <mmu.h>

extern void (*__pgfault_handler)(u_int);       // C 级别的处理回调指针
extern void __asm_pgfault_handler(void);       // 汇编入口（切栈并调用 C 回调）


// 设置用户态缺页处理回调：首次注册需要分配异常栈，并在内核登记汇编入口。
void
set_pgfault_handler(void (*fn)(u_int va))
{
	if (__pgfault_handler == 0) {
		// 映射一页异常栈，栈顶位于 UXSTACKTOP；随后在内核登记汇编入口与栈顶
		if (syscall_mem_alloc(0, UXSTACKTOP - BY2PG, PTE_V | PTE_R) < 0 ||
			syscall_set_pgfault_handler(0, __asm_pgfault_handler, UXSTACKTOP) < 0) {
			writef("cannot set pgfault handler\n");
			return;
		}
	}

	// 保存回调指针，供汇编入口在异常时调用
	__pgfault_handler = fn;
}
