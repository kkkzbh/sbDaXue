实验二要点（供后续实验三参考）

- 地址空间与窗口
  - 关键常量：`ULIM=0x80000000`、`UVPT/UPAGES/UENVS` 三个只读/元数据窗口各占 `PDMAP=4MB`。
  - 内核自映射窗口 `VPT` 与内核栈 `KSTACKTOP/KSTKSIZE` 已在 include/mmu.h 固化。

- 物理页管理
  - 结构：`struct Page { pp_link; pp_ref; }`，全体数组 `pages[npage]`。
  - 空闲链：`page_free_list`（LIST_* 宏），分配：`page_alloc` 清零但不自增 `pp_ref`；释放：`page_free` 仅在 `pp_ref==0` 时回收。
  - 常用内联：`page2pa/pa2page/va2pa/page2kva`（include/pmap.h）。

- 初始化序（调用栈）
  1) `mips_detect_memory` → 设置 `maxpa/npage/basemem/extmem`；
  2) `mips_vm_init` → `alloc` 出页目录、`pages[]`、`envs[]` 并 `boot_map_segment` 到 `UPAGES/UENVS`；
  3) `page_init` → 对 `freemem` 以下的页置 `pp_ref=1`，其余挂入 `page_free_list`。

- 页表与映射
  - 启动期：`boot_pgdir_walk`（不存在则 `alloc` 页表）；运行期：`pgdir_walk`（不存在且允许时 `page_alloc` 页表并 `pp_ref++`）。
  - 建立映射：`page_insert(pgdir, pp, va, perm)`，若冲突先 `page_remove`，后 `tlb_invalidate`。

- TLB 路径
  - Miss 入口：`handle_tlb` → `do_refill`（lib/genex.S）→ 若 PTE 无效则调用 `pageout(va, mCONTEXT)` 分配页并 `page_insert`；
  - 刷写：`mtc0 EntryLo0` + `tlbwr`；失效：`tlb_out(entryhi)`（mm/tlb_asm.S）。

- 编写/阅读文档的约定
  - 代码片段统一用 LaTeX \codefilerange 从仓库相对路径引用，避免复制失真。
  - 宏与关键函数的语义以 include/mmu.h、include/pmap.h、mm/pmap.c 为准。

对实验三的提示

- 若扩展用户态页故障处理、IPC 或共享库页（`PTE_LIBRARY`/COW），需严格维护 `pp_ref` 与 `tlb_invalidate` 的配合。
- 若新增页替换策略或惰性分配，复用 `pageout` 路径，保持异常重试点与 `tlbwr` 时序。

实验二文档补充要点

- 已在 `doc/2/main.tex` 逐条核对 SY 中的宏/全局变量定义，可直接引用对应 `\codefilerange`（queue.h、mmu.h、pmap.h 等）避免重新查源码。
- 物理内存分配流程明确为 “`page_free_list` 弹出 → `page2kva` + `bzero` 清零 → 调用方维护 `pp_ref`”，释放时则依据 `pp_ref` 选择保留或 `LIST_INSERT_HEAD` 回链。
- TLB refill 由 `lib/genex.S:do_refill` + `mm/pmap.c:pageout` 协作，缺页时循环调用 `pageout` 直到 `PTE_V` 置位；`tlb_out` 仍负责按 ASID 精确失效。
- 启动/运行期页表维护接口已整理（`boot_pgdir_walk`、`pgdir_walk`、`boot_map_segment`），未来扩展功能（如自定义映射或 COW）时按该三函数的 BFS 调用分析即可定位依赖。
