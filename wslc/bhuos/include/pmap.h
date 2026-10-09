#ifndef _PMAP_H_ // 头文件防重包含开始
#define _PMAP_H_ // 定义本头文件的防重包含宏

#include "types.h"  // 基础类型
#include "queue.h"  // 链表宏
#include "mmu.h"    // 内存管理常量与宏
#include "printf.h" // 调试输出

// 维护空闲页的链表类型与结点嵌入字段
LIST_HEAD(Page_list, Page);              // 页链表头类型
typedef LIST_ENTRY(Page) Page_LIST_entry_t; // 每个 Page 的链表指针字段类型

// 每个物理页的元信息（链表链接与引用计数）
struct Page { // 物理页描述符
    Page_LIST_entry_t pp_link; // 空闲链表指针
    u_short pp_ref;            // 被页表引用的次数（仅运行期分配的页有效）
}; // 结构体结束

extern struct Page* pages; // 所有物理页的描述符数组

// Page* -> 物理页号（相对 pages[] 基址的偏移）
static inline u_long page2ppn(struct Page* pp) { return pp - pages; }

// Page* -> 物理地址（页号左移 12 得到页框基址）
static inline u_long page2pa(struct Page* pp) { return page2ppn(pp) << PGSHIFT; }

// 物理地址 -> Page*（越界检查：PPN(pa) 必须小于 npage）
static inline struct Page* pa2page(u_long pa) {
    if (PPN(pa) >= npage)
        panic("pa2page called with invalid pa: %x", pa);
    return &pages[PPN(pa)];
}

// Page* -> 可访问的内核虚拟地址（通过 KADDR 恒等映射）
static inline u_long page2kva(struct Page* pp) { return KADDR(page2pa(pp)); }

// 查询页表得到 VA 对应的物理地址；无映射时返回 ~0
static inline u_long va2pa(Pde* pgdir, u_long va) {
    Pte* p;
    pgdir = &pgdir[PDX(va)];
    if (!(*pgdir & PTE_V))
        return ~0;
    p = (Pte*)KADDR(PTE_ADDR(*pgdir));
    if (!(p[PTX(va)] & PTE_V))
        return ~0;
    return PTE_ADDR(p[PTX(va)]);
}

// 原型声明
void mips_detect_memory(void); // 探测物理内存布局
void mips_vm_init(void);       // 初始化虚拟内存结构
void mips_init(void);          // 平台初始化入口
void page_init(void);          // 初始化物理页分配器
void page_check(void);         // 自检页分配与回收逻辑
int  page_alloc(struct Page** pp); // 分配一页（返回页面指针）
void page_free(struct Page* pp);   // 释放一页
void page_decref(struct Page* pp); // 引用计数减一，为零则释放
int  pgdir_walk(Pde* pgdir, u_long va, int create, Pte** ppte); // 查找/按需创建二级 PTE
int  page_insert(Pde* pgdir, struct Page* pp, u_long va, u_int perm); // 建立映射
struct Page* page_lookup(Pde* pgdir, u_long va, Pte** ppte); // 查找映射并可返回 PTE 指针
void page_remove(Pde* pgdir, u_long va); // 解除映射
void tlb_invalidate(Pde* pgdir, u_long va); // 失效相应 TLB 项

void boot_map_segment(Pde* pgdir, u_long va, u_long size, u_long pa, int perm); // 启动期大段映射

extern struct Page* pages; // 所有物理页描述符数组（再次声明）

#endif // 结束防重包含
