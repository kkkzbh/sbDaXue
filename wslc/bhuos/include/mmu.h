#ifndef _MMU_H_ // 头文件防重包含开始
#define _MMU_H_ // 定义本头文件的防重包含宏

// 页面与页目录参数
#define BY2PG   4096           // 每页 4KB
#define PDMAP   (4*1024*1024)  // 一个页目录项覆盖 4MB
#define PGSHIFT 12             // 页内偏移位数（log2(BY2PG)）
#define PDSHIFT 22             // 目录对齐位数（log2(PDMAP)）

// 从虚拟地址中提取索引
#define PDX(va) ((((u_long)(va)) >> 22) & 0x03FF) // 页目录索引（高 10 位）
#define PTX(va) ((((u_long)(va)) >> 12) & 0x03FF) // 页表索引（中 10 位）

#define PTE_ADDR(pte) ((u_long)(pte) & ~0xFFF) // PTE 对应的物理页框基址

// 页号相关（去除页内偏移）
#define PPN(va)  (((u_long)(va)) >> 12) // 物理/虚拟页号
#define VPN(va)  PPN(va)                // 同义宏：虚拟页号

// 供 TLB EntryLo 使用的 PFN
#define VA2PFN(va) (((u_long)(va)) & 0xFFFFF000) // 清零低 12 位得到 PFN
#define PTE2PT    1024                           // 每个目录项对应 1024 个 PTE

// PTE 标志位（硬件/约定）
#define PTE_G       0x0100 // 全局页
#define PTE_V       0x0200 // 有效
#define PTE_R       0x0400 // 可写/脏（0 表示只读）
#define PTE_D       0x0002 // 文件缓存脏标记
#define PTE_COW     0x0001 // 写时复制
#define PTE_UC      0x0800 // 不经缓存
#define PTE_LIBRARY 0x0004 // 共享页

// 内核与用户关键地址常量
#define KERNBASE  0x80010000 // 内核镜像基址（链接脚本一致）
#define VPT       (ULIM + PDMAP)   // 内核页表自映射窗口
#define KSTACKTOP (VPT - 0x100)    // 内核栈顶（向下增长）
#define KSTKSIZE  (8*BY2PG)        // 内核栈大小：8 页
#define ULIM      0x80000000       // 内核高半区起始

#define UVPT   (ULIM - PDMAP) // 用户只读自映射页表窗口
#define UPAGES (UVPT - PDMAP) // 物理页描述数组（struct Page[]）
#define UENVS  (UPAGES - PDMAP)// 进程控制块数组

#define UTOP       UENVS           // 用户地址空间上界
#define UXSTACKTOP (UTOP)          // 用户异常栈顶
#define TIMESTACK  0x82000000      // 计时器中断栈（特殊用途）

#define USTACKTOP (UTOP - 2*BY2PG) // 普通用户栈顶
#define UTEXT     0x00400000       // 用户程序文本起始地址

// 错误码（为兼容使用场景在此并列保留）
#define E_UNSPECIFIED 1  // 未知错误
#define E_BAD_ENV     2  // 环境不存在或不可用
#define E_INVAL       3  // 参数无效
#define E_NO_MEM      4  // 内存不足
#define E_NO_FREE_ENV 5  // 环境数量已达上限
#define E_IPC_NOT_RECV 6 // 目标未在接收 IPC
#define E_NO_DISK     7  // 磁盘空间不足
#define E_MAX_OPEN    8  // 打开的文件过多
#define E_NOT_FOUND   9  // 未找到文件/块
#define E_BAD_PATH    10 // 路径无效
#define E_FILE_EXISTS 11 // 文件已存在
#define E_NOT_EXEC    12 // 非可执行文件
#define MAXERROR      12 // 错误码最大值

#ifndef __ASSEMBLER__ // 仅在 C 语言环境下可见

#include "types.h" // 基础类型定义
void bcopy(const void* src, void* dst, size_t n); // 字节拷贝
void bzero(void* p, size_t n);                   // 置零 n 字节

extern char  bootstacktop[], bootstack[]; // 启动期栈的上下界（链接脚本符号）
extern u_long npage;                      // 物理页数量

typedef u_long Pde; // 页目录项
typedef u_long Pte; // 页表项

extern volatile Pte* vpt[]; // 自映射页表窗口
extern volatile Pde* vpd[]; // 自映射页目录窗口

// 内核虚拟地址 -> 物理地址（要求地址在 ULIM 以上）
#define PADDR(kva)                                   \
({                                                  \
    u_long a = (u_long)(kva);                       \
    if (a < ULIM)                                   \
        panic("PADDR called with invalid kva %08lx", a); \
    a - ULIM;                                       \
})

// 物理地址 -> 内核虚拟地址（要求 PPN(pa) < npage）
#define KADDR(pa)                                    \
({                                                  \
    u_long ppn = PPN(pa);                           \
    if (ppn >= npage)                               \
        panic("KADDR called with invalid pa %08lx", (u_long)pa); \
    (pa) + ULIM;                                    \
})

#define assert(x) do { if (!(x)) panic("assertion failed: %s", #x); } while (0) // 断言失败直接 panic

#define TRUP(_p)                                     \
({                                                  \
    register typeof((_p)) __m_p = (_p);             \
    (u_int)__m_p > ULIM ? (typeof(_p))ULIM : __m_p; \
}) // 将用户指针截断到用户空间上界

extern void tlb_out(u_int entryhi); // 按 entryhi 失效对应的 TLB 项
#endif // 结束 __ASSEMBLER__ 条件编译
#endif // 结束防重包含

