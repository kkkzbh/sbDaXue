#include "lib.h"  // 引入 pageref 所需的页表/页数组符号

int
pageref(void *v)  // 返回虚拟地址 v 对应物理页的引用计数
{
	u_int pte;  // 临时存放页表项

	if (!((* vpd)[PDX(v)]&PTE_V))  // 目录项无效则未映射
		return 0;
	pte = (* vpt)[VPN(v)];  // 读取页表项
	if (!(pte&PTE_V))  // 页表项无效则未映射
		return 0;
	return pages[PPN(pte)].pp_ref;  // 通过物理页号索引全局页数组，返回引用计数
}
