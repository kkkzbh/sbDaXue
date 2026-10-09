#ifndef _TRAP_H_ // 头文件防重包含开始
#define _TRAP_H_ // 定义本头文件的防重包含宏

#define T_DIVIDE   0  // 除零错误
#define T_DEBUG    1  // 调试异常
#define T_NMI      2  // 不可屏蔽中断
#define T_BRKPT    3  // 断点
#define T_OFLOW    4  // 溢出
#define T_BOUND    5  // 边界检查失败
#define T_ILLOP    6  // 非法操作码
#define T_DEVICE   7  // 设备不可用
#define T_DBLFLT   8  // 双重故障

#define T_TSS     10  // 任务状态段无效
#define T_SEGNP   11  // 段不存在
#define T_STACK   12  // 栈异常
#define T_GPFLT   13  // 一般保护错误
#define T_PGFLT   14  // 缺页异常

#define T_FPERR   16  // 浮点错误
#define T_ALIGN   17  // 对齐检查失败
#define T_MCHK    18  // 机器检查

#define T_SYSCALL 0x30 // 系统调用陷入号
#define T_DEFAULT 500  // 兜底异常号

#ifndef __ASSEMBLER__ // 仅在 C 语言环境下可见

#include <types.h> // 基础类型定义

struct Trapframe { // 中断/异常现场保存区
    unsigned long regs[32];      // 通用寄存器集合（32 个）
    unsigned long cp0_status;    // CP0 Status 寄存器
    unsigned long hi;            // 乘除法高位寄存器 HI
    unsigned long lo;            // 乘除法低位寄存器 LO
    unsigned long cp0_badvaddr;  // 错误地址（如缺页时的 VA）
    unsigned long cp0_cause;     // 异常原因码
    unsigned long cp0_epc;       // 异常返回地址 EPC
    unsigned long pc;            // 进入异常时的 PC
}; // 结构体结束

void* set_except_vector(int n, void* addr); // 设置第 n 类异常的入口地址，返回旧入口
void  trap_init(void);                      // 初始化异常处理与向量表

#endif // 结束对 __ASSEMBLER__ 的条件编译

// 下列宏给出 Trapframe 中各字段的字节偏移（用于汇编访问）
#define TF_REG0      0
#define TF_REG1      (TF_REG0  + 4)
#define TF_REG2      (TF_REG1  + 4)
#define TF_REG3      (TF_REG2  + 4)
#define TF_REG4      (TF_REG3  + 4)
#define TF_REG5      (TF_REG4  + 4)
#define TF_REG6      (TF_REG5  + 4)
#define TF_REG7      (TF_REG6  + 4)
#define TF_REG8      (TF_REG7  + 4)
#define TF_REG9      (TF_REG8  + 4)
#define TF_REG10     (TF_REG9  + 4)
#define TF_REG11     (TF_REG10 + 4)
#define TF_REG12     (TF_REG11 + 4)
#define TF_REG13     (TF_REG12 + 4)
#define TF_REG14     (TF_REG13 + 4)
#define TF_REG15     (TF_REG14 + 4)
#define TF_REG16     (TF_REG15 + 4)
#define TF_REG17     (TF_REG16 + 4)
#define TF_REG18     (TF_REG17 + 4)
#define TF_REG19     (TF_REG18 + 4)
#define TF_REG20     (TF_REG19 + 4)
#define TF_REG21     (TF_REG20 + 4)
#define TF_REG22     (TF_REG21 + 4)
#define TF_REG23     (TF_REG22 + 4)
#define TF_REG24     (TF_REG23 + 4)
#define TF_REG25     (TF_REG24 + 4)
#define TF_REG26     (TF_REG25 + 4)
#define TF_REG27     (TF_REG26 + 4)
#define TF_REG28     (TF_REG27 + 4)
#define TF_REG29     (TF_REG28 + 4)
#define TF_REG30     (TF_REG29 + 4)
#define TF_REG31     (TF_REG30 + 4)

#define TF_STATUS    (TF_REG31 + 4)   // cp0_status 偏移
#define TF_HI        (TF_STATUS + 4)  // hi 偏移
#define TF_LO        (TF_HI + 4)      // lo 偏移
#define TF_BADVADDR  (TF_LO + 4)      // cp0_badvaddr 偏移
#define TF_CAUSE     (TF_BADVADDR + 4)// cp0_cause 偏移
#define TF_EPC       (TF_CAUSE + 4)   // cp0_epc 偏移
#define TF_PC        (TF_EPC + 4)     // pc 偏移

#define TF_SIZE      (TF_PC + 4)      // Trapframe 总大小（字节）
#endif // 结束防重包含
