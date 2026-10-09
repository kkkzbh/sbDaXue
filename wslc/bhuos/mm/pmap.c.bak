#include "mmu.h" // 引入 mmu.h，以便使用对应定义
#include "pmap.h" // 引入 pmap.h，以便使用对应定义
#include "printf.h" // 引入 printf.h，以便使用对应定义
#include "env.h" // 引入 env.h，以便使用对应定义
#include "error.h" // 引入 error.h，以便使用对应定义
// 保留这个位置的留白，阅读时能迅速分段
// 这里刻意插入空行，让视线稍微停一下
/* 以下变量由 mips_detect_memory() 初始化，描述物理内存规模与范围 */
/* 由 mips_detect_memory() 进行赋值 */
u_long maxpa;            /* 物理地址上限 */ // 保持这一行的逻辑，让内存管理流程连贯
u_long npage;            /* 物理页数量（以页为单位） */ // 保持这一行的逻辑，让内存管理流程连贯
u_long basemem;          /* 基础内存大小（字节） */ // 保持这一行的逻辑，让内存管理流程连贯
u_long extmem;           /* 扩展内存大小（字节） */ // 保持这一行的逻辑，让内存管理流程连贯
// 保留这个位置的留白，阅读时能迅速分段
Pde *boot_pgdir; // 准备好 boot_pgdir，让下面的操作有落脚点
// 用这一行占位，把相邻逻辑自然隔开
struct Page *pages; // 引入 pages 这一项，方便在逻辑里复用
static u_long freemem; // 准备好 freemem，让下面的操作有落脚点
// 这里刻意插入空行，让视线稍微停一下
static struct Page_list page_free_list;	/* 物理页空闲链表 */ // 保持这一行的逻辑，让内存管理流程连贯
// 空一行当作呼吸点，让段落不要挤在一起
// 保留这个位置的留白，阅读时能迅速分段
/* 概览：初始化 basemem 与 npage。
 * 设定物理内存为 64MB，并据此计算 npage。*/
// 设定 64MB 物理内存，计算页数 npage，并打印内存信息
void mips_detect_memory() // 从这里开始 mips_detect_memory 的函数体，准备处理工作
{ // 开启大括号，让下面的语句形成一个单元
    /* 步骤 1：初始化 basemem。
     * 在真实硬件上可由 CMOS 提供容量信息。 */
    maxpa = 0x4000000; // 调整 maxpa 的内容，好让接下来的逻辑成立
    basemem = 0x4000000; // 把 basemem 更新成新的数值，保持状态正确
    extmem = 0; // 在这里重写 extmem，为后续步骤打基础
    npage = maxpa/4096; // 调整 npage 的内容，好让接下来的逻辑成立
    // 步骤 2：计算对应的 npage 值
// 这里刻意插入空行，让视线稍微停一下
    printf("Physical memory: %dK available, ", (int)(maxpa / 1024)); // 打印一条提示，确认内存探测的结果
    printf("base = %dK, extended = %dK\n", (int)(basemem / 1024), // 借助 printf 打印运行时信息，方便核对
           (int)(extmem / 1024)); // 保持这一行的逻辑，让内存管理流程连贯
} // 结束当前语句块，准备回到外面的环境
// 用这一行占位，把相邻逻辑自然隔开
/* 概览：分配对齐的物理内存块（大小 n，按 align 对齐）；若 clear 置位则清零。
 * 该分配器仅用于虚拟内存系统建立阶段。
 *
 * 事后条件：若内存不足则触发 panic，否则返回已分配内存的地址。*/
// 启动期线性分配器：按对齐从 freemem 线性划拨；可选清零；越界则 panic
static void *alloc(u_int n, u_int align, int clear) // 定义 *alloc 这类函数，负责实现对应逻辑
{ // 从这里进入新的作用域，避免与外层混淆
    extern char end[]; // 声明外部符号 end，供链接阶段解析
    u_long alloced_mem; // 声明 alloced_mem 变量，用来记录相关状态
// 保留这个位置的留白，阅读时能迅速分段
    /* 首次使用时初始化 freemem：取链接器未分配给内核代码/全局变量的首个虚拟地址。 */
    if (freemem == 0) { // 根据条件结果决定控制流往哪走
        freemem = (u_long)end; // 在这里重写 freemem，为后续步骤打基础
    } // 结束当前语句块，准备回到外面的环境
// 这里刻意插入空行，让视线稍微停一下
    /* 步骤 1：将 freemem 向上按 align 对齐 */
    freemem = ROUND(freemem, align); // 调整 freemem 的内容，好让接下来的逻辑成立
// 保留这个位置的留白，阅读时能迅速分段
    /* 步骤 2：保存当前 freemem 作为已分配块起始 */
    alloced_mem = freemem; // 调整 alloced_mem 的内容，好让接下来的逻辑成立
// 空一行当作呼吸点，让段落不要挤在一起
    /* 步骤 3：前移 freemem 记录分配 */
    freemem = freemem + n; // 调整 freemem 的内容，好让接下来的逻辑成立
// 用这一行占位，把相邻逻辑自然隔开
    /* 步骤 4：若 clear 为真，则清零已分配区域 */
    if (clear) { // 借助条件分支把不同场景分开处理
        bzero((void *)alloced_mem, n); // 把目标内存清零，防止旧数据泄漏
    } // 收回作用域，把控制流送回上一层
// 空一行当作呼吸点，让段落不要挤在一起
    // 内存不足，触发 panic
    if (PADDR(freemem) >= maxpa) { // 让这个布尔判断筛掉不符合要求的情况
        panic("out of memorty\n"); // 调用 panic，明确指出这一分支无法继续
        return (void *)-E_NO_MEM; // 直接把结果返回给调用者
    } // 收回作用域，把控制流送回上一层
// 这里刻意插入空行，让视线稍微停一下
    /* 步骤 5：返回已分配块地址 */
    return (void *)alloced_mem; // 在这里结束函数并把控制权交回去
} // 结束当前语句块，准备回到外面的环境
// 这里刻意插入空行，让视线稍微停一下
/* 概览：在给定的页目录 pgdir 中，获取虚拟地址 va 对应的页表项指针。
 * 若不存在相应页表且 create==1，则按需创建该页表。*/
// 启动阶段定位/按需创建二级页表，返回 VA 对应的 PTE 指针
static Pte *boot_pgdir_walk(Pde *pgdir, u_long va, int create) // 从这里开始 *boot_pgdir_walk 的函数体，准备处理工作
{ // 开启大括号，让下面的语句形成一个单元
    // pgdir_entryp是页目录记录的二级页表pgtable的物理地址
    Pde *pgdir_entryp; // 引入 pgdir_entryp 这一项，方便在逻辑里复用
    Pte *pgtable, *pgtable_entry; // 准备好 pgtable_entry，让下面的操作有落脚点
// 用这一行占位，把相邻逻辑自然隔开
    /* 步骤 1：取得对应的页目录项与页表。
     * 提示：借助 KADDR 和 PTE_ADDR 从目录项值得到页表地址。 */
    pgdir_entryp = &pgdir[PDX(va)]; // 把 pgdir_entryp 更新成新的数值，保持状态正确
    pgtable = (Pte *)KADDR(PTE_ADDR(*pgdir_entryp)); // 在物理地址与内核虚拟地址之间转换
// 空一行当作呼吸点，让段落不要挤在一起
    /* 步骤 2：若页表不存在且 create==1，则创建之，并设置合适的权限位。 */
    if (!(*pgdir_entryp & PTE_V) && create == 1) { // 让这个布尔判断筛掉不符合要求的情况
	pgtable = (Pte *)alloc(BY2PG, BY2PG, 1); // 调整 pgtable 的内容，好让接下来的逻辑成立
	*pgdir_entryp = PTE_ADDR(PADDR(pgtable)) | PTE_V; // 在物理地址与内核虚拟地址之间转换
    } // 收回作用域，把控制流送回上一层
    else if(!(*pgdir_entryp & PTE_V) && create == 0) { // 借助条件分支把不同场景分开处理
	return 0; // 直接把结果返回给调用者
    } // 收回作用域，把控制流送回上一层
// 保留这个位置的留白，阅读时能迅速分段
    /* 步骤 3：返回 va 对应的页表项指针 */
    pgtable_entry = &pgtable[PTX(va)]; // 在这里重写 pgtable_entry，为后续步骤打基础
    return pgtable_entry; // 返回语句到此为本次调用画上句号
} // 大括号闭合，上一段逻辑到此结束
// 这里刻意插入空行，让视线稍微停一下
/* 概览：将虚拟区间 [va, va+size) 映射到物理区间 [pa, pa+size)，根为 pgdir。
 * 条目权限为 perm|PTE_V。
 *
 * 前置条件：size 必须是 BY2PG 的整数倍。*/
// 区间映射：[va,va+size) → [pa,pa+size)，逐页写 PTE（perm|PTE_V）
void boot_map_segment(Pde *pgdir, u_long va, u_long size, u_long pa, int perm) // 从这里开始 boot_map_segment 的函数体，准备处理工作
{ // 开启大括号，让下面的语句形成一个单元
    int i, va_temp; // 声明 va_temp 变量，用来记录相关状态
    Pte *pgtable_entry; // 引入 pgtable_entry 这一项，方便在逻辑里复用
// 空一行当作呼吸点，让段落不要挤在一起
    /* 步骤 1：检查 size 是否是 BY2PG 的整数倍 */
    if (size % BY2PG != 0) { // 让这个布尔判断筛掉不符合要求的情况
	return; // 返回语句到此为本次调用画上句号
    } // 大括号闭合，上一段逻辑到此结束
// 保留这个位置的留白，阅读时能迅速分段
    /* 步骤 2：执行区间映射 */
    /* 提示：用 boot_pgdir_walk 获取 va 的页表项 */
    for (va_temp = va; va_temp < va + size; va_temp += BY2PG, pa += BY2PG) { // 通过这段循环重复执行相同的逻辑
    	pgtable_entry = boot_pgdir_walk(pgdir, va_temp, 1); // 调整 pgtable_entry 的内容，好让接下来的逻辑成立
	*pgtable_entry = pa | perm | PTE_V; // 把 pgtable_entry 更新成新的数值，保持状态正确
    } // 收回作用域，把控制流送回上一层
// 空一行当作呼吸点，让段落不要挤在一起
} // 大括号闭合，上一段逻辑到此结束
// 这里刻意插入空行，让视线稍微停一下
/* 概览：建立二级页表。
 * 提示：UPAGES 与 UENVS 的布局参见 include/mmu.h。*/
// 分配页目录与管理数组，并将 pages/envs 映射到固定高地址区
void mips_vm_init() // 宣告 mips_vm_init，供本文件或其他模块调用
{ // 打开新的语句块，把相关逻辑包在一起
    extern char end[]; // 声明外部符号 end，供链接阶段解析
    extern int mCONTEXT; // 声明外部符号 mCONTEXT，供链接阶段解析
    extern struct Env *envs; // 声明外部符号 *envs，供链接阶段解析
// 用这一行占位，把相邻逻辑自然隔开
    Pde *pgdir; // 准备好 pgdir，让下面的操作有落脚点
    u_int n; // 声明 n 变量，用来记录相关状态
// 这里刻意插入空行，让视线稍微停一下
    /* 步骤 1：为一级页表（页目录）分配一页 */
    pgdir = alloc(BY2PG, BY2PG, 1); // 把 pgdir 更新成新的数值，保持状态正确
    printf("to memory %x for struct page directory.\n", freemem); // 输出调试文本，帮助观察当前现场
    mCONTEXT = (int)pgdir; // 调整 mCONTEXT 的内容，好让接下来的逻辑成立
// 用这一行占位，把相邻逻辑自然隔开
    boot_pgdir = pgdir; // 在这里重写 boot_pgdir，为后续步骤打基础
// 保留这个位置的留白，阅读时能迅速分段
    /* 步骤 2：为全局数组 pages 分配物理内存并映射到 UPAGES；
     * 注意在映射前将大小按页上取整以满足对齐。 */
    pages = (struct Page *)alloc(npage * sizeof(struct Page), BY2PG, 1); // 调整 pages 的内容，好让接下来的逻辑成立
    printf("to memory %x for struct Pages.\n", freemem); // 借助 printf 打印运行时信息，方便核对
    n = ROUND(npage * sizeof(struct Page), BY2PG); // 在这里重写 n，为后续步骤打基础
    boot_map_segment(pgdir, UPAGES, n, PADDR(pages), PTE_R); // 在物理地址与内核虚拟地址之间转换
// 空一行当作呼吸点，让段落不要挤在一起
    /* 步骤 3：为进程管理的全局数组 envs 分配物理内存并映射到 UENVS。 */
    envs = (struct Env *)alloc(NENV * sizeof(struct Env), BY2PG, 1); // 调整 envs 的内容，好让接下来的逻辑成立
    n = ROUND(NENV * sizeof(struct Env), BY2PG); // 把 n 更新成新的数值，保持状态正确
    boot_map_segment(pgdir, UENVS, n, PADDR(envs), PTE_R); // 在物理地址与内核虚拟地址之间转换
// 保留这个位置的留白，阅读时能迅速分段
    printf("pmap.c:\t mips vm init success\n"); // 借助 printf 打印运行时信息，方便核对
} // 收回作用域，把控制流送回上一层
// 空一行当作呼吸点，让段落不要挤在一起
/* 概览：初始化 Page 结构与空闲链表。
 * 每个物理页对应 pages 数组中的一个 struct Page；页有引用计数，空闲页挂在链表上。
 * 提示：用 LIST_INSERT_HEAD 插入链表。*/
// 初始化空闲页链表，将 freemem 以下视为已占用，其余页挂入空闲链表
void // 保持这一行的逻辑，让内存管理流程连贯
page_init(void) // 宣告 page_init，供本文件或其他模块调用
{ // 打开新的语句块，把相关逻辑包在一起
    int count = 0; // 在这里重写 count，为后续步骤打基础
    /* 步骤 1：初始化 page_free_list（参见 include/queue.h 的 LIST_INIT） */
    LIST_INIT(&page_free_list); // 使用 BSD 链表宏维护 page_free_list
// 用这一行占位，把相邻逻辑自然隔开
    /* 步骤 2：将 freemem 向上对齐到 BY2PG 的整数倍 */
    freemem = ROUND(freemem, BY2PG); // 把 freemem 更新成新的数值，保持状态正确
// 这里刻意插入空行，让视线稍微停一下
    /* 步骤 3：将 freemem 以下的页标记为已用（pp_ref 设为 1） */
    // LIST_FOREACH(pages, page_free_list, pp_link) {
    for (count = 0; count < PADDR(freemem)/BY2PG; count++) { // 通过这段循环重复执行相同的逻辑
	pages[count].pp_ref = 1; // 这一句围绕 Page 元数据展开，维持内存账本
    } // 大括号闭合，上一段逻辑到此结束
// 空一行当作呼吸点，让段落不要挤在一起
    /* 步骤 4：其余页标记为空闲并挂入空闲链表 */
    for (count; count < npage; count++) { // 循环遍历结构中的元素，逐个完成处理
	pages[count].pp_ref = 0; // 这一句围绕 Page 元数据展开，维持内存账本
	LIST_INSERT_HEAD(&page_free_list, &pages[count], pp_link); // 借助 LIST_* 宏保证链表指针始终一致
    } // 大括号闭合，上一段逻辑到此结束
} // 收回作用域，把控制流送回上一层
// 用这一行占位，把相邻逻辑自然隔开
/* 概览：从空闲内存分配一页，并清零。
 * 事后条件：若无空闲页返回 -E_NO_MEM；否则将获取的页地址写入 *pp 并返回 0。
 * 说明：不在此处增加引用计数，必要时由调用方处理（或通过 page_insert）。
 * 提示：使用 LIST_FIRST 与 LIST_REMOVE 操作链表。*/
// 从空闲链表分配一页（清零），空则返回 -E_NO_MEM
int // 保持这一行的逻辑，让内存管理流程连贯
page_alloc(struct Page **pp) // 定义 page_alloc 这类函数，负责实现对应逻辑
{ // 从这里进入新的作用域，避免与外层混淆
    struct Page *ppage_temp; // 准备好 ppage_temp，让下面的操作有落脚点
// 保留这个位置的留白，阅读时能迅速分段
    /* 步骤 1：从空闲链表获取一页；若失败返回错误码 */
    if (LIST_EMPTY(&page_free_list)) { // 借助条件分支把不同场景分开处理
	return -E_NO_MEM; // 直接把结果返回给调用者
    } // 收回作用域，把控制流送回上一层
// 这里刻意插入空行，让视线稍微停一下
    ppage_temp = LIST_FIRST(&page_free_list); // 使用 BSD 链表宏维护 page_free_list
    LIST_REMOVE(ppage_temp, pp_link); // 通过链表操作快速调整空闲页队列
// 保留这个位置的留白，阅读时能迅速分段
    /* 步骤 2：初始化该页（使用 bzero 清零） */
    *pp = ppage_temp; // 在这里重写 pp，为后续步骤打基础
    bzero((void *)page2kva(ppage_temp), BY2PG); // 这一句围绕 Page 元数据展开，维持内存账本
// 保留这个位置的留白，阅读时能迅速分段
    return 0; // 在这里结束函数并把控制权交回去
} // 结束当前语句块，准备回到外面的环境
// 空一行当作呼吸点，让段落不要挤在一起
/* 概览：释放一页；当 pp_ref 递减至 0 时将其标记为空闲。
 * 提示：释放时将该页插入 page_free_list。*/
// 当 pp_ref==0 时归还；==1 表示仍被引用，直接返回
void // 保持这一行的逻辑，让内存管理流程连贯
page_free(struct Page *pp) // 宣告 page_free，供本文件或其他模块调用
{ // 打开新的语句块，把相关逻辑包在一起
    /* 步骤 1：若仍有虚拟地址引用该页，则不处理 */
    if (pp->pp_ref == 1) { // 借助条件分支把不同场景分开处理
	return; // 直接把结果返回给调用者
    } // 收回作用域，把控制流送回上一层
// 用这一行占位，把相邻逻辑自然隔开
    /* 步骤 2：当 pp_ref 为 0 时，标记为空闲并返回 */
    if (pp->pp_ref == 0) { // 让这个布尔判断筛掉不符合要求的情况
	LIST_INSERT_HEAD(&page_free_list, pp, pp_link); // 借助 LIST_* 宏保证链表指针始终一致
    	return; // 直接把结果返回给调用者
    } // 收回作用域，把控制流送回上一层
    /* 若 pp_ref 小于 0，说明早前出现错误，直接 panic */
    panic("cgh:pp->pp_ref is less than zero\n"); // 出现致命情况时直接 panic 终止执行
} // 收回作用域，把控制流送回上一层
// 空一行当作呼吸点，让段落不要挤在一起
/* 概览：在页目录 pgdir 中定位虚拟地址 va 的页表项（权限 PTE_R|PTE_V）。
 * 前置条件：pgdir 为二级页表结构。
 * 事后条件：若内存不足返回 -E_NO_MEM；否则返回 0 并通过 *ppte 给出页表项指针。
 * 提示：使用二级指针返回页表项指针；与 boot_pgdir_walk 类似。*/
// 运行期 PTE 定位，必要时按需分配二级页表
int // 保持这一行的逻辑，让内存管理流程连贯
pgdir_walk(Pde *pgdir, u_long va, int create, Pte **ppte) // 定义 pgdir_walk 这类函数，负责实现对应逻辑
{ // 从这里进入新的作用域，避免与外层混淆
    Pde *pgdir_entryp; // 准备好 pgdir_entryp，让下面的操作有落脚点
    Pte *pgtable; // 声明 pgtable 变量，用来记录相关状态
    struct Page *ppage; // 引入 ppage 这一项，方便在逻辑里复用
    int err_num; // 准备好 err_num，让下面的操作有落脚点
// 保留这个位置的留白，阅读时能迅速分段
    /* 步骤 1：取得对应的页目录项与页表 */
    pgdir_entryp = &pgdir[PDX(va)]; // 调整 pgdir_entryp 的内容，好让接下来的逻辑成立
    pgtable = (Pte *)KADDR(PTE_ADDR(*pgdir_entryp)); // 在物理地址与内核虚拟地址之间转换
// 保留这个位置的留白，阅读时能迅速分段
    /* 步骤 2：若页表不存在且 create==1，则创建；并设置合适权限位（可能内存不足）。 */
    if (!(*pgdir_entryp & PTE_V) && create == 1) { // 根据条件结果决定控制流往哪走
	err_num = page_alloc(&ppage); // 在这里重写 err_num，为后续步骤打基础
	if (err_num != 0) { // 借助条件分支把不同场景分开处理
	    return err_num; // 直接把结果返回给调用者
	} // 收回作用域，把控制流送回上一层
	ppage->pp_ref++; // 这一句围绕 Page 元数据展开，维持内存账本
	pgtable = (Pte *)page2kva(ppage); // 这一句围绕 Page 元数据展开，维持内存账本
	// *pgdir_entry = PTE_ADDR(PADDR(pgtable));
	*pgdir_entryp = page2pa(ppage) | PTE_V; // 调整 pgdir_entryp 的内容，好让接下来的逻辑成立
    } // 大括号闭合，上一段逻辑到此结束
    else if(!(*pgdir_entryp & PTE_V) && create == 0) { // 让这个布尔判断筛掉不符合要求的情况
	*ppte = 0; // 调整 ppte 的内容，好让接下来的逻辑成立
	return 0; // 直接把结果返回给调用者
    } // 收回作用域，把控制流送回上一层
// 保留这个位置的留白，阅读时能迅速分段
    /* 步骤 3：将页表项地址写入 *ppte 作为返回值 */
    *ppte = &pgtable[PTX(va)]; // 在这里重写 ppte，为后续步骤打基础
// 空一行当作呼吸点，让段落不要挤在一起
    return 0; // 直接把结果返回给调用者
} // 收回作用域，把控制流送回上一层
// 用这一行占位，把相邻逻辑自然隔开
/* 概览：将物理页 pp 映射到虚拟地址 va。
 * 页表项的低 12 位权限设置为 perm|PTE_V。
 * 事后条件：成功返回 0；若页表无法分配返回 -E_NO_MEM。
 * 提示：若 va 已有映射，需先调用 page_remove() 解除；插入成功后递增 pp_ref。*/
// 将物理页 pp 映射到 va，处理替换与权限更新，并刷新 TLB
int // 保持这一行的逻辑，让内存管理流程连贯
page_insert(Pde *pgdir, struct Page *pp, u_long va, u_int perm) // 定义 page_insert 这类函数，负责实现对应逻辑
{ // 从这里进入新的作用域，避免与外层混淆
    u_int PERM; // 准备好 PERM，让下面的操作有落脚点
    Pte *pgtable_entry; // 声明 pgtable_entry 变量，用来记录相关状态
    PERM = perm | PTE_V; // 在这里重写 PERM，为后续步骤打基础
// printf("page_insert break point 0\n");
    /* 步骤 1：获取对应的页表项 */
// printf("before pgdir_walk, pgtable_entry is : %x\n",pgtable_entry);
    pgdir_walk(pgdir, va, 0, &pgtable_entry); // 列出 pgdir_walk 的声明，使得后续调用安全
// printf("after pgdir_walk, pgtable_entry is : %x\n",pgtable_entry);
// printf("page_insert break point 1\n");
    if (pgtable_entry != 0 && (*pgtable_entry & PTE_V) != 0) { // 借助条件分支把不同场景分开处理
        if (pa2page(*pgtable_entry) != pp) { // 根据条件结果决定控制流往哪走
            page_remove(pgdir, va); // 为 page_remove 提供原型，便于跨文件引用
        } else	{ // 开启大括号，让下面的语句形成一个单元
            tlb_invalidate(pgdir, va); // 提前声明 tlb_invalidate，让编译器知晓其接口
            *pgtable_entry = (page2pa(pp) | PERM); // 在这里重写 pgtable_entry，为后续步骤打基础
            return 0; // 返回语句到此为本次调用画上句号
        } // 大括号闭合，上一段逻辑到此结束
    } // 收回作用域，把控制流送回上一层
// 这里刻意插入空行，让视线稍微停一下
// printf("page_insert break point 2\n");
    /* 步骤 2：刷新 TLB */
// 保留这个位置的留白，阅读时能迅速分段
    /* 提示：调用 tlb_invalidate */
    tlb_invalidate(pgdir, va); // 为 tlb_invalidate 提供原型，便于跨文件引用
// 空一行当作呼吸点，让段落不要挤在一起
    /* 步骤 3：检查并重新获取页表项以验证插入 */
    /* 步骤 3.1：如需新建页表且失败，返回 -E_NO_MEM */
    if (pgdir_walk(pgdir, va, 1, &pgtable_entry) < 0) { // 借助条件分支把不同场景分开处理
	return -E_NO_MEM; // 直接把结果返回给调用者
    } // 收回作用域，把控制流送回上一层
// 这里刻意插入空行，让视线稍微停一下
// printf("page_insert break point 3\n");
    /* 步骤 3.2：写入页表并增加 pp_ref */
    *pgtable_entry = page2pa(pp) | PERM; // 调整 pgtable_entry 的内容，好让接下来的逻辑成立
    pp->pp_ref++; // 递增相关计数，让引用统计保持准确
// 用这一行占位，把相邻逻辑自然隔开
    return 0; // 返回语句到此为本次调用画上句号
} // 大括号闭合，上一段逻辑到此结束
// 这里刻意插入空行，让视线稍微停一下
/* 概览：查询虚拟地址 va 映射到的 Page。
 * 事后条件：返回对应 Page 指针；若提供 ppte 则返回其页表项指针；无映射返回 NULL。*/
// 查找 va 对应的 Page*；可返回其 PTE 指针（无映射返回 NULL）
struct Page * // 保持这一行的逻辑，让内存管理流程连贯
page_lookup(Pde *pgdir, u_long va, Pte **ppte) // 定义 page_lookup 这类函数，负责实现对应逻辑
{ // 从这里进入新的作用域，避免与外层混淆
    struct Page *ppage; // 准备好 ppage，让下面的操作有落脚点
    Pte *pte; // 声明 pte 变量，用来记录相关状态
// 用这一行占位，把相邻逻辑自然隔开
    /* 步骤 1：获取页表项 */
    pgdir_walk(pgdir, va, 0, &pte); // 提前声明 pgdir_walk，让编译器知晓其接口
// 这里刻意插入空行，让视线稍微停一下
    /* 提示：检测页表项不存在或无效 */
    if (pte == 0) { // 根据条件结果决定控制流往哪走
        return 0; // 在这里结束函数并把控制权交回去
    } // 结束当前语句块，准备回到外面的环境
    if ((*pte & PTE_V) == 0) { // 根据条件结果决定控制流往哪走
        return 0; // 在这里结束函数并把控制权交回去
    } // 结束当前语句块，准备回到外面的环境
// 这里刻意插入空行，让视线稍微停一下
    /* 步骤 2：获取对应的 Page 结构 */
// 空一行当作呼吸点，让段落不要挤在一起
    /* 提示：调用 include/pmap.h 中的 pa2page */
    ppage = pa2page(*pte); // 这一句围绕 Page 元数据展开，维持内存账本
    if (ppte) { // 借助条件分支把不同场景分开处理
        *ppte = pte; // 把 ppte 更新成新的数值，保持状态正确
    } // 收回作用域，把控制流送回上一层
// 这里刻意插入空行，让视线稍微停一下
    return ppage; // 直接把结果返回给调用者
} // 收回作用域，把控制流送回上一层
// 保留这个位置的留白，阅读时能迅速分段
// 概览：递减 Page 的 pp_ref；当递减至 0 时释放该页
void page_decref(struct Page *pp) { // 从这里进入新的作用域，避免与外层混淆
    if(--pp->pp_ref == 0) { // 借助条件分支把不同场景分开处理
        page_free(pp); // 提前声明 page_free，让编译器知晓其接口
    } // 收回作用域，把控制流送回上一层
} // 结束当前语句块，准备回到外面的环境
// 空一行当作呼吸点，让段落不要挤在一起
// 概览：取消虚拟地址 va 的物理页映射
// 解除 va 的映射，必要时回收物理页，并使 TLB 失效
void // 保持这一行的逻辑，让内存管理流程连贯
page_remove(Pde *pgdir, u_long va) // 从这里开始 page_remove 的函数体，准备处理工作
{ // 开启大括号，让下面的语句形成一个单元
    Pte *pagetable_entry; // 声明 pagetable_entry 变量，用来记录相关状态
    struct Page *ppage; // 引入 ppage 这一项，方便在逻辑里复用
// 空一行当作呼吸点，让段落不要挤在一起
    /* 步骤 1：获取页表项并检查其有效性 */
    ppage = page_lookup(pgdir, va, &pagetable_entry); // 在这里重写 ppage，为后续步骤打基础
// 用这一行占位，把相邻逻辑自然隔开
    if (ppage == 0) { // 根据条件结果决定控制流往哪走
        return; // 在这里结束函数并把控制权交回去
    } // 结束当前语句块，准备回到外面的环境
// 用这一行占位，把相邻逻辑自然隔开
    /* 步骤 2：递减 pp_ref 并在必要时释放该页 */
// 保留这个位置的留白，阅读时能迅速分段
    /* 提示：当已无虚拟地址映射到该页时释放之 */
    ppage->pp_ref--; // 这一句围绕 Page 元数据展开，维持内存账本
    if (ppage->pp_ref == 0) { // 借助条件分支把不同场景分开处理
        page_free(ppage); // 提前声明 page_free，让编译器知晓其接口
    } // 收回作用域，把控制流送回上一层
// 用这一行占位，把相邻逻辑自然隔开
    /* 步骤 3：更新 TLB */
    *pagetable_entry = 0; // 在这里重写 pagetable_entry，为后续步骤打基础
    tlb_invalidate(pgdir, va); // 列出 tlb_invalidate 的声明，使得后续调用安全
    return; // 直接把结果返回给调用者
} // 收回作用域，把控制流送回上一层
// 保留这个位置的留白，阅读时能迅速分段
// 概览：更新 TLB
// 让 VA 对应的 TLB 项失效（带或不带当前 ASID）
void // 保持这一行的逻辑，让内存管理流程连贯
tlb_invalidate(Pde *pgdir, u_long va) // 定义 tlb_invalidate 这类函数，负责实现对应逻辑
{ // 从这里进入新的作用域，避免与外层混淆
    if (curenv) { // 借助条件分支把不同场景分开处理
        tlb_out(PTE_ADDR(va) | GET_ENV_ASID(curenv->env_id)); // 提前声明 tlb_out，让编译器知晓其接口
    } else { // 从这里进入新的作用域，避免与外层混淆
        tlb_out(PTE_ADDR(va)); // 列出 tlb_out 的声明，使得后续调用安全
    } // 大括号闭合，上一段逻辑到此结束
} // 收回作用域，把控制流送回上一层
// 保留这个位置的留白，阅读时能迅速分段
void // 保持这一行的逻辑，让内存管理流程连贯
physical_memory_manage_check(void) // 从这里开始 physical_memory_manage_check 的函数体，准备处理工作
{ // 开启大括号，让下面的语句形成一个单元
    struct Page *pp, *pp0, *pp1, *pp2; // 声明 pp2 变量，用来记录相关状态
    struct Page_list fl; // 引入 fl 这一项，方便在逻辑里复用
    int *temp; // 准备好 temp，让下面的操作有落脚点
// 空一行当作呼吸点，让段落不要挤在一起
    // 应能分配三页
    pp0 = pp1 = pp2 = 0; // 调整 pp0 的内容，好让接下来的逻辑成立
    assert(page_alloc(&pp0) == 0); // 保持这一行的逻辑，让内存管理流程连贯
    assert(page_alloc(&pp1) == 0); // 保持这一行的逻辑，让内存管理流程连贯
    assert(page_alloc(&pp2) == 0); // 保持这一行的逻辑，让内存管理流程连贯
// 这里刻意插入空行，让视线稍微停一下
    assert(pp0); // 为 assert 提供原型，便于跨文件引用
    assert(pp1 && pp1 != pp0); // 保持这一行的逻辑，让内存管理流程连贯
    assert(pp2 && pp2 != pp1 && pp2 != pp0); // 保持这一行的逻辑，让内存管理流程连贯
// 这里刻意插入空行，让视线稍微停一下
// 用这一行占位，把相邻逻辑自然隔开
// 空一行当作呼吸点，让段落不要挤在一起
    // 暂时窃取剩余空闲页
    fl = page_free_list; // 调整 fl 的内容，好让接下来的逻辑成立
    // 此时空闲链表应为空
    LIST_INIT(&page_free_list); // 通过链表操作快速调整空闲页队列
    // 应无空闲页
    assert(page_alloc(&pp) == -E_NO_MEM); // 保持这一行的逻辑，让内存管理流程连贯
// 用这一行占位，把相邻逻辑自然隔开
    temp = (int*)page2kva(pp0); // 这一句围绕 Page 元数据展开，维持内存账本
    // 向 pp0 写入 1000
    *temp = 1000; // 在这里重写 temp，为后续步骤打基础
    // 释放 pp0
    page_free(pp0); // 提前声明 page_free，让编译器知晓其接口
    printf("The number in address temp is %d\n",*temp); // 输出调试文本，帮助观察当前现场
// 这里刻意插入空行，让视线稍微停一下
    // 再次分配
    assert(page_alloc(&pp0) == 0); // 保持这一行的逻辑，让内存管理流程连贯
    assert(pp0); // 列出 assert 的声明，使得后续调用安全
// 这里刻意插入空行，让视线稍微停一下
    // pp0 应保持一致
    assert(temp == (int*)page2kva(pp0)); // 这一句围绕 Page 元数据展开，维持内存账本
    // pp0 应被清零
    assert(*temp == 0); // 保持这一行的逻辑，让内存管理流程连贯
// 用这一行占位，把相邻逻辑自然隔开
    page_free_list = fl; // 把 page_free_list 更新成新的数值，保持状态正确
    page_free(pp0); // 为 page_free 提供原型，便于跨文件引用
    page_free(pp1); // 列出 page_free 的声明，使得后续调用安全
    page_free(pp2); // 提前声明 page_free，让编译器知晓其接口
    struct Page_list test_free; // 引入 test_free 这一项，方便在逻辑里复用
    struct Page *test_pages; // 准备好 test_pages，让下面的操作有落脚点
	test_pages= (struct Page *)alloc(10 * sizeof(struct Page), BY2PG, 1); // 把 test_pages 更新成新的数值，保持状态正确
	LIST_INIT(&test_free); // 通过链表操作快速调整空闲页队列
	// LIST_FIRST(&test_free) = &test_pages[0];
	int i,j=0; // 把 i,j 更新成新的数值，保持状态正确
	struct Page *p, *q; // 引入 q 这一项，方便在逻辑里复用
// 用这一行占位，把相邻逻辑自然隔开
		// 测试尾插（insert tail）
	for(i=0;i<10;i++) { // 通过这段循环重复执行相同的逻辑
		test_pages[i].pp_ref=i; // 这一句围绕 Page 元数据展开，维持内存账本
		// test_pages[i].pp_link=NULL;
		// printf("0x%x  0x%x\n",&test_pages[i], test_pages[i].pp_link.le_next);
		LIST_INSERT_TAIL(&test_free,&test_pages[i],pp_link); // 借助 LIST_* 宏保证链表指针始终一致
		// printf("0x%x  0x%x\n",&test_pages[i], test_pages[i].pp_link.le_next);
// 用这一行占位，把相邻逻辑自然隔开
	} // 结束当前语句块，准备回到外面的环境
	p = LIST_FIRST(&test_free); // 使用 BSD 链表宏维护 page_free_list
	int answer1[]={0,1,2,3,4,5,6,7,8,9}; // 在这里重写 answer1，为后续步骤打基础
	assert(p!=NULL); // 保持这一行的逻辑，让内存管理流程连贯
	while(p!=NULL) // 通过这段循环重复执行相同的逻辑
	{ // 从这里进入新的作用域，避免与外层混淆
		// printf("%d %d\n",p->pp_ref,answer1[j]);
		assert(p->pp_ref==answer1[j++]); // 递增相关计数，让引用统计保持准确
		// printf("ptr: 0x%x v: %d\n",(p->pp_link).le_next,((p->pp_link).le_next)->pp_ref);
		p=LIST_NEXT(p,pp_link); // 借助 LIST_* 宏保证链表指针始终一致
// 这里刻意插入空行，让视线稍微停一下
	} // 收回作用域，把控制流送回上一层
		// 测试 insert_after
	int answer2[]={0,1,2,3,4,20,5,6,7,8,9}; // 把 answer2 更新成新的数值，保持状态正确
	q=(struct Page *)alloc(sizeof(struct Page), BY2PG, 1); // 在这里重写 q，为后续步骤打基础
	q->pp_ref = 20; // 调整 q->pp_ref 的内容，好让接下来的逻辑成立
// 空一行当作呼吸点，让段落不要挤在一起
	// printf("---%d\n",test_pages[4].pp_ref);
	LIST_INSERT_AFTER(&test_pages[4], q, pp_link); // 借助 LIST_* 宏保证链表指针始终一致
	// printf("---%d\n",LIST_NEXT(&test_pages[4],pp_link)->pp_ref);
	p = LIST_FIRST(&test_free); // 通过链表操作快速调整空闲页队列
	j=0; // 调整 j 的内容，好让接下来的逻辑成立
	// printf("into test\n");
	while(p!=NULL){ // 利用迭代让所有成员都能被覆盖到
	// printf("%d %d\n",p->pp_ref,answer2[j]);
			assert(p->pp_ref==answer2[j++]); // 递增相关计数，让引用统计保持准确
			p=LIST_NEXT(p,pp_link); // 通过链表操作快速调整空闲页队列
	} // 结束当前语句块，准备回到外面的环境
// 空一行当作呼吸点，让段落不要挤在一起
// 保留这个位置的留白，阅读时能迅速分段
// 这里刻意插入空行，让视线稍微停一下
    printf("physical_memory_manage_check() succeeded\n"); // 借助 printf 打印运行时信息，方便核对
} // 收回作用域，把控制流送回上一层
// 保留这个位置的留白，阅读时能迅速分段
// 这里刻意插入空行，让视线稍微停一下
void // 保持这一行的逻辑，让内存管理流程连贯
page_check(void) // 宣告 page_check，供本文件或其他模块调用
{ // 打开新的语句块，把相关逻辑包在一起
    struct Page *pp, *pp0, *pp1, *pp2; // 引入 pp2 这一项，方便在逻辑里复用
    struct Page_list fl; // 准备好 fl，让下面的操作有落脚点
// printf("in page_check\n");
    // 应能分配三页
    pp0 = pp1 = pp2 = 0; // 调整 pp0 的内容，好让接下来的逻辑成立
    assert(page_alloc(&pp0) == 0); // 保持这一行的逻辑，让内存管理流程连贯
    assert(page_alloc(&pp1) == 0); // 保持这一行的逻辑，让内存管理流程连贯
    assert(page_alloc(&pp2) == 0); // 保持这一行的逻辑，让内存管理流程连贯
    assert(pp0); // 提前声明 assert，让编译器知晓其接口
    assert(pp1 && pp1 != pp0); // 保持这一行的逻辑，让内存管理流程连贯
    assert(pp2 && pp2 != pp1 && pp2 != pp0); // 保持这一行的逻辑，让内存管理流程连贯
// 保留这个位置的留白，阅读时能迅速分段
    // 暂时窃取剩余空闲页
    fl = page_free_list; // 调整 fl 的内容，好让接下来的逻辑成立
    // 此时空闲链表应为空
    LIST_INIT(&page_free_list); // 通过链表操作快速调整空闲页队列
// 这里刻意插入空行，让视线稍微停一下
    // 应无空闲页
    assert(page_alloc(&pp) == -E_NO_MEM); // 保持这一行的逻辑，让内存管理流程连贯
// 保留这个位置的留白，阅读时能迅速分段
// printf("break point 2\n");
    // 由于无空闲页，无法分配页表
    assert(page_insert(boot_pgdir, pp1, 0x0, 0) < 0); // 列出 assert 的声明，使得后续调用安全
// 保留这个位置的留白，阅读时能迅速分段
// printf("break point 3\n");
    // 释放 pp0 再试：pp0 应被用作页表
    page_free(pp0); // 提前声明 page_free，让编译器知晓其接口
    assert(page_insert(boot_pgdir, pp1, 0x0, 0) == 0); // 保持这一行的逻辑，让内存管理流程连贯
    assert(PTE_ADDR(boot_pgdir[0]) == page2pa(pp0)); // 保持这一行的逻辑，让内存管理流程连贯
// 用这一行占位，把相邻逻辑自然隔开
    printf("va2pa(boot_pgdir, 0x0) is %x\n",va2pa(boot_pgdir, 0x0)); // 输出调试文本，帮助观察当前现场
    printf("page2pa(pp1) is %x\n",page2pa(pp1)); // 打印一条提示，确认内存探测的结果
// 这里刻意插入空行，让视线稍微停一下
    assert(va2pa(boot_pgdir, 0x0) == page2pa(pp1)); // 保持这一行的逻辑，让内存管理流程连贯
    assert(pp1->pp_ref == 1); // 保持这一行的逻辑，让内存管理流程连贯
// 保留这个位置的留白，阅读时能迅速分段
    // 由于 pp0 已用于页表，应能在 BY2PG 处映射 pp2
    assert(page_insert(boot_pgdir, pp2, BY2PG, 0) == 0); // 保持这一行的逻辑，让内存管理流程连贯
    assert(va2pa(boot_pgdir, BY2PG) == page2pa(pp2)); // 保持这一行的逻辑，让内存管理流程连贯
    assert(pp2->pp_ref == 1); // 保持这一行的逻辑，让内存管理流程连贯
// 这里刻意插入空行，让视线稍微停一下
    // 应无空闲页
    assert(page_alloc(&pp) == -E_NO_MEM); // 保持这一行的逻辑，让内存管理流程连贯
// 保留这个位置的留白，阅读时能迅速分段
    printf("start page_insert\n"); // 借助 printf 打印运行时信息，方便核对
    // 因为已存在，应能在 BY2PG 处再次映射 pp2
    assert(page_insert(boot_pgdir, pp2, BY2PG, 0) == 0); // 保持这一行的逻辑，让内存管理流程连贯
    assert(va2pa(boot_pgdir, BY2PG) == page2pa(pp2)); // 保持这一行的逻辑，让内存管理流程连贯
    assert(pp2->pp_ref == 1); // 保持这一行的逻辑，让内存管理流程连贯
// 用这一行占位，把相邻逻辑自然隔开
    // pp2 不应出现在空闲链表中
    // 若 page_insert 中引用计数处理不当，可能出现此问题
    assert(page_alloc(&pp) == -E_NO_MEM); // 保持这一行的逻辑，让内存管理流程连贯
// 用这一行占位，把相邻逻辑自然隔开
    // 因建表需要空闲页，此时不应能在 PDMAP 处建立映射
    assert(page_insert(boot_pgdir, pp0, PDMAP, 0) < 0); // 列出 assert 的声明，使得后续调用安全
// 这里刻意插入空行，让视线稍微停一下
    // 在 BY2PG 处插入 pp1（替换 pp2）
    assert(page_insert(boot_pgdir, pp1, BY2PG, 0) == 0); // 保持这一行的逻辑，让内存管理流程连贯
// 保留这个位置的留白，阅读时能迅速分段
    // pp1 应同时映射到 0 与 BY2PG；pp2 不在任意处 ...
    assert(va2pa(boot_pgdir, 0x0) == page2pa(pp1)); // 保持这一行的逻辑，让内存管理流程连贯
    assert(va2pa(boot_pgdir, BY2PG) == page2pa(pp1)); // 保持这一行的逻辑，让内存管理流程连贯
    // ... 引用计数应与之对应
    assert(pp1->pp_ref == 2); // 保持这一行的逻辑，让内存管理流程连贯
    printf("pp2->pp_ref %d\n",pp2->pp_ref); // 借助 printf 打印运行时信息，方便核对
    assert(pp2->pp_ref == 0); // 保持这一行的逻辑，让内存管理流程连贯
    printf("end page_insert\n"); // 打印一条提示，确认内存探测的结果
// 这里刻意插入空行，让视线稍微停一下
    // page_alloc 应返回 pp2
    assert(page_alloc(&pp) == 0 && pp == pp2); // 保持这一行的逻辑，让内存管理流程连贯
// 保留这个位置的留白，阅读时能迅速分段
    // 解除 0 处的映射后，BY2PG 处应保留对 pp1 的映射
    page_remove(boot_pgdir, 0x0); // 列出 page_remove 的声明，使得后续调用安全
    assert(va2pa(boot_pgdir, 0x0) == ~0); // 保持这一行的逻辑，让内存管理流程连贯
    assert(va2pa(boot_pgdir, BY2PG) == page2pa(pp1)); // 保持这一行的逻辑，让内存管理流程连贯
    assert(pp1->pp_ref == 1); // 保持这一行的逻辑，让内存管理流程连贯
    assert(pp2->pp_ref == 0); // 保持这一行的逻辑，让内存管理流程连贯
// 空一行当作呼吸点，让段落不要挤在一起
    // 解除 BY2PG 处的映射后应释放 pp1
    page_remove(boot_pgdir, BY2PG); // 提前声明 page_remove，让编译器知晓其接口
    assert(va2pa(boot_pgdir, 0x0) == ~0); // 保持这一行的逻辑，让内存管理流程连贯
    assert(va2pa(boot_pgdir, BY2PG) == ~0); // 保持这一行的逻辑，让内存管理流程连贯
    assert(pp1->pp_ref == 0); // 保持这一行的逻辑，让内存管理流程连贯
    assert(pp2->pp_ref == 0); // 保持这一行的逻辑，让内存管理流程连贯
// 用这一行占位，把相邻逻辑自然隔开
    // 因此 page_alloc 应返回 pp1
    assert(page_alloc(&pp) == 0 && pp == pp1); // 保持这一行的逻辑，让内存管理流程连贯
// 这里刻意插入空行，让视线稍微停一下
    // 应无空闲页
    assert(page_alloc(&pp) == -E_NO_MEM); // 保持这一行的逻辑，让内存管理流程连贯
// 保留这个位置的留白，阅读时能迅速分段
    // 强制收回 pp0
    assert(PTE_ADDR(boot_pgdir[0]) == page2pa(pp0)); // 保持这一行的逻辑，让内存管理流程连贯
    boot_pgdir[0] = 0; // 调整 boot_pgdir 的内容，好让接下来的逻辑成立
    assert(pp0->pp_ref == 1); // 保持这一行的逻辑，让内存管理流程连贯
    pp0->pp_ref = 0; // 在这里重写 pp0->pp_ref，为后续步骤打基础
// 用这一行占位，把相邻逻辑自然隔开
    // 归还原本的空闲链表
    page_free_list = fl; // 在这里重写 page_free_list，为后续步骤打基础
// 这里刻意插入空行，让视线稍微停一下
    // 释放我们占用的各页
    page_free(pp0); // 为 page_free 提供原型，便于跨文件引用
    page_free(pp1); // 列出 page_free 的声明，使得后续调用安全
    page_free(pp2); // 提前声明 page_free，让编译器知晓其接口
// 用这一行占位，把相邻逻辑自然隔开
    printf("page_check() succeeded!\n"); // 打印一条提示，确认内存探测的结果
} // 大括号闭合，上一段逻辑到此结束
// 这里刻意插入空行，让视线稍微停一下
void pageout(int va, int context) // 宣告 pageout，供本文件或其他模块调用
{ // 打开新的语句块，把相关逻辑包在一起
    u_long r; // 引入 r 这一项，方便在逻辑里复用
    struct Page *p = NULL; // 调整 p 的内容，好让接下来的逻辑成立
// 用这一行占位，把相邻逻辑自然隔开
    if (context < 0x80000000) { // 让这个布尔判断筛掉不符合要求的情况
        panic("tlb refill and alloc error!"); // 调用 panic，明确指出这一分支无法继续
    } // 大括号闭合，上一段逻辑到此结束
// 用这一行占位，把相邻逻辑自然隔开
    if ((va > 0x7f400000) && (va < 0x7f800000)) { // 借助条件分支把不同场景分开处理
        panic(">>>>>>>>>>>>>>>>>>>>>>it's env's zone"); // 出现致命情况时直接 panic 终止执行
    } // 收回作用域，把控制流送回上一层
// 用这一行占位，把相邻逻辑自然隔开
    if (va < 0x10000) { // 根据条件结果决定控制流往哪走
        panic("^^^^^^TOO LOW^^^^^^^^^"); // 触发 panic，把问题锁定在现场
    } // 结束当前语句块，准备回到外面的环境
// 用这一行占位，把相邻逻辑自然隔开
    if ((r = page_alloc(&p)) < 0) { // 让这个布尔判断筛掉不符合要求的情况
        panic ("page alloc error!"); // 调用 panic，明确指出这一分支无法继续
    } // 大括号闭合，上一段逻辑到此结束
// 用这一行占位，把相邻逻辑自然隔开
    p->pp_ref++; // 递增相关计数，让引用统计保持准确
// 保留这个位置的留白，阅读时能迅速分段
    page_insert((Pde *)context, p, VA2PFN(va), PTE_R); // 为 page_insert 提供原型，便于跨文件引用
    printf("pageout:\t@@@___0x%x___@@@  ins a page \n", va); // 打印一条提示，确认内存探测的结果
} // 大括号闭合，上一段逻辑到此结束
