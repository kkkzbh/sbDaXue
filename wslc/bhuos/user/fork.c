// 在用户态实现 fork：复制地址空间与缺页处理设置

#include "lib.h"  // 运行库与系统调用
#include <mmu.h>   // 页表/权限宏
#include <env.h>   // 环境结构与常量


/* ----------------- 辅助函数 ---------------- */

/* 概述：从 src 复制 len 字节到 dst。
 * 约束：src/dst 非空且不重叠；若重叠行为未定义。
 */
void user_bcopy(const void *src, void *dst, size_t len)
{
	void *max;

		writef("~~~~~~~~~~~~~~~~ src:%x dst:%x len:%x\n",(int)src,(int)dst,len);
	max = dst + len;

int i;
for (i = 0; i < len; i++) {
	*(char *)(dst + i) = *(char*)(src + i);
}
return;

		// 尽可能按机器字大小复制（优化路径）
	if (((int)src % 4 == 0) && ((int)dst % 4 == 0)) {
		while (dst + 3 < max) {
			*(int *)dst = *(int *)src;
			dst += 4;
			src += 4;
		}
	}

		// 复制剩余的 0~3 字节
	while (dst < max) {
		*(char *)dst = *(char *)src;
		dst += 1;
		src += 1;
	}

	//for(;;);
}

/* 概述：将从 v 起始的 n 个字节清零。
 * 条件：v 为有效可写地址。
 */
void user_bzero(void *v, u_int n)
{
	char *p;
	int m;

	p = v;
	m = n;

	while (--m >= 0) {
		*p++ = 0;
	}
}
/*--------------------------------------------------------------*/

/* 概述：用户态缺页处理。若缺页页为写时复制（COW），则为自身映射一份可写副本。
 * 入参：va 为触发异常的地址。
 * 行为：若非 COW 页则 user_panic；否则在临时地址分配页、复制内容、
 *       再映射回原地址为可写页，最后撤销临时映射。
 */
static void
pgfault(u_int va)
{
	u_int *tmp;
	u_int perm;
	u_int r;

	va = ROUNDDOWN(va, BY2PG);
	tmp = UXSTACKTOP - 2 * BY2PG;

	perm = ((*vpt)[VPN(va)]) & 0xfff | PTE_V | PTE_R;
	// writef("fork.c:pgfault():\t va:%x\n",va);
   	if (!(perm & PTE_COW)) {
		user_panic("va should be a PTE_COW page\n");
		return;
	} 
	    // 在临时位置分配一页
	r = syscall_mem_alloc(syscall_getenvid(), tmp, perm & (~PTE_COW));
	if (r < 0) {
		user_panic("fork.c pgfault:syscall_mem_alloc error!\n");
	}
		// 复制原页内容
	user_bcopy(va, tmp, BY2PG);	
	    // 将新页映射回原地址（去除 COW）
	r = syscall_mem_map(syscall_getenvid(), tmp, syscall_getenvid(), va, perm & (~PTE_COW));
	if (r < 0) {
		user_panic("fork.c pgfault:syscall_mem_map error!\n");
	}
	
	    // 取消临时映射
	r = syscall_mem_unmap(syscall_getenvid(), tmp);
	if (r < 0) {
		user_panic("fork.c pgfault:syscall_mem_unmap error!\n");
	}
}

/* 概述：将自身的虚拟页 pn（pn*BY2PG）映射到目标 envid 的同一虚拟地址。
 * 要求：若该页可写或为 COW，新旧两个映射均应标记为 COW；
 *       若带有 PTE_LIBRARY（共享库页），需保持共享读权限。
 */
static void
duppage(u_int envid, u_int pn) 
{
        u_int addr;
        u_int perm;
	u_int r;
	int ra;

//	asm volatile("move %0, $31":"=r"(ra) );
//	writef("%x\n", ra);
writef("debug0\n");
        perm = ((*vpt)[pn]) & 0xfff;
        addr = pn * BY2PG;
writef("debug1\n");
	        // user_panic("duppage not implemented");
//        if(((perm & PTE_R) || (perm & PTE_COW)) && (perm & PTE_V)){
writef("debug2\n");
	if((perm & PTE_R) || (perm & PTE_COW)){
                if(perm & PTE_LIBRARY){
//writef("in fork.c duppage, find PTE_LIBRARY %x %x\n", pn, perm); 
                        perm = PTE_V | PTE_R | PTE_LIBRARY | perm;      //保持共享可写状态
                }   
                else{
                        perm = PTE_V | PTE_R | PTE_COW | perm;  //不保持共享可写状态 PTE_COW
                }   
writef("debug3\n");
                if(syscall_mem_map(0, addr, envid, addr, perm) < 0)
                        user_panic("fork.c/duppage : duppage fail 1 !!\n");
writef("debug4, addr = %x, perm = %x\n", addr, perm);
                r = syscall_mem_map(0, addr, 0, addr, perm);
writef("debug5 r = %d\n",r);
		if (r < 0) {
                        user_panic("fork.c/duppage : duppage fail 2 !!\n");
		}
        }   
        else{
                if(syscall_mem_map(0, addr, envid, addr, perm) < 0)
                        user_panic("fork.c/duppage : duppage fail 3 !!\n");
        }  

	asm volatile("move %0, $29":"=r"(ra) );
	writef("%x\n", ra);
}

/* 概述：用户态 fork。创建子进程，复制地址空间，并为子进程设置缺页处理。
 * 提示：使用 vpd/vpt 与 duppage；别忘了在子进程中修正全局指针 env；
 * 说明：set_pgfault_handler（user/pgfault.c）与 syscall_set_pgfault_handler 含义不同。
 */
extern void __asm_pgfault_handler(void);
int
fork(void)  // 创建子环境并复制地址空间（COW）
{
		// 关键流程：安装 pgfault、分配环境、区分父子路径、按页 duppage、设置异常栈与处理函数、置为 RUNNABLE
	u_int newenvid;
	extern struct Env *envs;
	extern struct Env *env;
	u_int i,j;

writef("in fork\n");
	//The parent installs pgfault using set_pgfault_handler
	set_pgfault_handler(pgfault);

	//alloc a new alloc
	newenvid = syscall_env_alloc();
	if (newenvid < 0) {
		user_panic("fork.c fork: newenvid cannot less than zero!\n");
	} else if (newenvid == 0) {
writef("after env alloc, in son\n");
		newenvid = syscall_getenvid();
		env = &envs[ENVX(newenvid)];
		return 0;
	} else {
writef("after env alloc, in father\n");
writef("father id = %x,newenvid = %x\n", syscall_getenvid(), newenvid);
		for (i = 0; i < USTACKTOP; i += BY2PG) {
			if ((((*vpd)[VPN(i) / 1024]) != 0) && (((*vpt)[VPN(i)]) != 0)) {
writef("go to duppage\n");
				duppage(newenvid, VPN(i));
writef("end duppage\n");
			}
		}
writef("in father after duppage, newenvid is %x\n", newenvid);
		if (syscall_mem_alloc(newenvid, UXSTACKTOP - BY2PG, PTE_V | PTE_R| PTE_LIBRARY) < 0) {
			user_panic("in fork : syscall_mem_alloc UXSTACK fail!\n");
		}
writef("after father mem alloc for son's error stack, newenvid is %x\n", newenvid);
		if (syscall_set_pgfault_handler(newenvid, __asm_pgfault_handler, UXSTACKTOP) < 0) {
			user_panic("in fork : syscall_set_pgfault_handler fail!\n");
		}
writef("after father set pgfault handler for son, newenvid is %x\n", newenvid);
		if (syscall_set_env_status(newenvid, ENV_RUNNABLE) < 0) {
			user_panic("in fork : syscall_set_env_status fail!\n");
		}
writef("after father set env status for son\n");
	}

	return newenvid;
}

// Challenge!
int
sfork(void)
{
	user_panic("sfork not implemented");
	return -E_INVAL;
}
