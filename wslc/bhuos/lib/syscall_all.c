#include "../drivers/gxconsole/dev_cons.h" // 中文注释：控制台设备接口
#include <mmu.h> // 中文注释：内存管理单元相关常量/宏
#include <env.h> // 中文注释：环境（进程）管理
#include <printf.h> // 中文注释：内核打印
#include <pmap.h> // 中文注释：页表/物理页操作
#include <trap.h> // 中文注释：Trapframe 与异常
#include <sched.h> // 中文注释：调度器接口

extern char *KERNEL_SP; // 中文注释：内核栈顶指针（符号）
extern struct Env *curenv; // 中文注释：当前运行环境

// 中文注释：向控制台输出一个字符（其余参数按系统调用约定占位）
void sys_putchar(int sysno, int c, int a2, int a3, int a4, int a5)
{
	printcharc((char) c); // 中文注释：输出字符
	return; // 中文注释：返回调用方
}

// 中文注释：内核 memcpy 简化实现（不处理重叠）
void *memcpy(void *destaddr, void const *srcaddr, u_int len)
{
	char *dest = destaddr; // 中文注释：目标指针
	char const *src = srcaddr; // 中文注释：源指针

	while (len-- > 0) { // 中文注释：逐字节拷贝
		*dest++ = *src++; // 中文注释：拷贝并后移
	}

	return destaddr; // 中文注释：返回目标起始地址
}

void _log_trapframe(struct Trapframe *tf) { // 中文注释：调试用，打印部分栈内容
	int i; // 中文注释：循环变量
	printf("Begin dump stack\n"); // 中文注释：开始标记
	for (i = 0; i < 16; i++) { // 中文注释：打印 16 个字
		printf("%x    ", ((int *)tf->regs[29])[i]); // 中文注释：以 sp 为基址读取
	}
	printf("End dump stack\n"); // 中文注释：结束标记
}

// 中文注释：返回当前环境（进程）的 envid
u_int sys_getenvid(void)
{
	return curenv->env_id; // 中文注释：直接读当前环境字段
}

// 中文注释：当前环境让出 CPU（进入调度），不再返回
void sys_yield(void)
{
	struct Trapframe * old; // 中文注释：旧位置（内核栈顶）
	struct Trapframe * new; // 中文注释：新位置（时间中断栈）
   	new = (struct Trapframe *)(TIMESTACK - sizeof(struct Trapframe)); // 中文注释：目标位置
   	old = (struct Trapframe *)(KERNEL_SP - sizeof(struct Trapframe)); // 中文注释：源位置
	bcopy(old, new, sizeof(struct Trapframe)); // 中文注释：复制 Trapframe
	
	sched_yield(); // 中文注释：调用调度器，不返回
}

// 中文注释：销毁指定环境（必须是当前或其子进程）
int sys_env_destroy(int sysno, u_int envid)
{
	int r; // 中文注释：返回码
	struct Env *e; // 中文注释：目标环境指针

	if ((r = envid2env(envid, &e, 1)) < 0) { // 中文注释：检查权限并转换为指针
		return r; // 中文注释：非法 envid
	}

	env_destroy(e); // 中文注释：执行销毁
	return 0; // 中文注释：成功
}

// 中文注释：设置缺页处理入口与用户异常栈顶
int sys_set_pgfault_handler(int sysno, u_int envid, u_int func, u_int xstacktop)
{
	struct Env *env; // 中文注释：目标环境
	int ret; // 中文注释：返回码
	ret = envid2env(envid, &env, 0); // 中文注释：转换 envid
	if (ret < 0) {
		return ret; // 中文注释：失败直接返回
	}	
	
	env->env_pgfault_handler = func; // 中文注释：登记缺页处理入口
	env->env_xstacktop = xstacktop; // 中文注释：登记用户异常栈顶

	return 0; // 中文注释：成功
}

/* Overview:
 * 	Allocate a page of memory and map it at 'va' with permission
 * 'perm' in the address space of 'envid'.
 *
 * 	If a page is already mapped at 'va', that page is unmapped as a
 * side-effect.
 * 
 * Pre-Condition:
 * perm -- PTE_V is required,
 *         PTE_COW is not allowed(return -E_INVAL),
 *         other bits are optional.
 *
 * Post-Condition:
 * Return 0 on success, < 0 on error
 *	- va must be < UTOP
 *	- env may modify its own address space or the address space of its children
 */
int sys_mem_alloc(int sysno, u_int envid, u_int va, u_int perm) // 中文注释：为指定环境在 va 分配并映射一页
{
	// Your code here.
		struct Env *env; // 中文注释：目标环境
		struct Page *ppage; // 中文注释：新分配物理页
		int ret; // 中文注释：返回码
		ret = 0; // 中文注释：初始化返回码
//printf("%x, %x, %x, %x\n", sysno, envid, va, perm);
	if (perm & PTE_COW || !(perm & PTE_V)) {
		printf("in sys_mem_alloc perm error\n");
		return -E_INVAL;
	}
	if (va >= UTOP || va < 0) {
		printf("in sys_mem_alloc va error\n");
		return -E_UNSPECIFIED;
	}
//printf("curenv = %x, envid = %x\n", curenv->env_id, envid);
	ret = envid2env(envid, &env, 0);
//printf("%x\n", env);
	if (ret < 0) {
		printf("in sys_mem_alloc envid error\n");
		return ret;
	}
	ret = page_alloc(&ppage);

	if (ret < 0) {
		printf("in sys_mem_alloc page_alloc error\n");
		return ret;
	}
	
	ret = page_insert(env->env_pgdir, ppage, va, perm);
	if (ret < 0) {
		return ret;
	}
	return 0;
}

/* Overview:
 * 	Map the page of memory at 'srcva' in srcid's address space
 * at 'dstva' in dstid's address space with permission 'perm'.
 * Perm has the same restrictions as in sys_mem_alloc.
 * (Probably we should add a restriction that you can't go from
 * non-writable to writable?)
 *
 * Post-Condition:
 * 	Return 0 on success, < 0 on error.
 *
 * Note:
 * 	Cannot access pages above UTOP.
 */
int sys_mem_map(int sysno, u_int srcid, u_int srcva, u_int dstid, u_int dstva,
				u_int perm, struct Trapframe *tf) // 中文注释：将 srcid 的 srcva 映射到 dstid 的 dstva，权限为 perm
{
	int ret; // 中文注释：返回码
	//printf("%x, %x\n", tf->regs[31], tf->cp0_epc);
	u_int round_srcva, round_dstva; // 中文注释：页对齐后的源/目标虚拟地址
	struct Env *srcenv; // 中文注释：源环境
	struct Env *dstenv; // 中文注释：目标环境
	struct Page *ppage; // 中文注释：源页
	Pte *ppte; // 中文注释：源 PTE 指针
int ra; // 中文注释：调试：栈指针快照
printf("in sys_mem_map\n"); // 中文注释：调试输出
asm volatile("move %0, $29":"=r"(ra)); // 中文注释：读取 $sp
printf("ra = %x\n",ra); // 中文注释：打印 sp 值
	ppage = NULL; // 中文注释：初始化页指针
	ret = 0; // 中文注释：初始化返回码
	round_srcva = ROUNDDOWN(srcva, BY2PG); // 中文注释：源地址对齐
	round_dstva = ROUNDDOWN(dstva, BY2PG); // 中文注释：目标地址对齐

    //your code here
	ret = envid2env(srcid, &srcenv, 0); // 中文注释：取源环境
	if (ret < 0) {
		return ret;
	}

	ret = envid2env(dstid, &dstenv, 0); // 中文注释：取目标环境
	if (ret < 0) {
		return ret;
	}

printf("mem map 0\n");
	ret = (perm & PTE_V); // 中文注释：必须包含有效位
	if (ret == 0) {
		return -E_INVAL;
	}

	if (srcva >= UTOP || srcva < 0) { // 中文注释：检查源地址范围
		return -E_UNSPECIFIED;
	}
	if (dstva >= UTOP || dstva < 0) { // 中文注释：检查目标地址范围
		return -E_UNSPECIFIED;
	}
printf("mem map 1\n");
	ppage = page_lookup(srcenv->env_pgdir, round_srcva, &ppte); // 中文注释：查找源页
	if (ppage == NULL) {
		return -E_UNSPECIFIED;
	}

printf("mem map 2\n");
	if ((perm & PTE_V) && !(*ppte && PTE_V)) { // 中文注释：要求源页有效
		return -E_INVAL;
	}
printf("mem map 3\n");

	ret = page_insert(dstenv->env_pgdir, ppage, round_dstva, perm); // 中文注释：在目标地址空间建立映射
	if (ret < 0) {
		return ret;
	}
printf("end sys_mem_map, ret = %d\n", ret); // 中文注释：打印结果
asm volatile("move %0, $29":"=r"(ra)); // 中文注释：再次读取 sp
printf("ra = %x\n",ra); // 中文注释：打印 sp
	return ret;
}

/* Overview:
 * 	Unmap the page of memory at 'va' in the address space of 'envid'
 * (if no page is mapped, the function silently succeeds)
 *
 * Post-Condition:
 * 	Return 0 on success, < 0 on error.
 *
 * Cannot unmap pages above UTOP.
 */
int sys_mem_unmap(int sysno, u_int envid, u_int va) // 中文注释：解除 envid 地址空间中 va 的映射
{
	int ret; // 中文注释：返回码
	struct Env *env; // 中文注释：目标环境

	if (va >= UTOP || va < 0) { // 中文注释：地址检查
		return -E_UNSPECIFIED; // 中文注释：越界
	}
	
	ret = envid2env(envid, &env, 0); // 中文注释：获取环境
	if (ret < 0) {
		return ret;
	}

	page_remove(env->env_pgdir, va); // 中文注释：从页表移除映射

	tlb_out(PTE_ADDR(va) | GET_ENV_ASID(envid));	 // 中文注释：刷新对应 TLB 项
	return ret; // 中文注释：返回
	//	panic("sys_mem_unmap not implemented");
}

/* Overview:
 * 	Allocate a new environment.
 *
 * Pre-Condition:
 * The new child is left as env_alloc created it, except that
 * status is set to ENV_NOT_RUNNABLE and the register set is copied
 * from the current environment.
 *
 * Post-Condition:
 * 	In the child, the register set is tweaked so sys_env_alloc returns 0.
 * 	Returns envid of new environment, or < 0 on error.
 */
int sys_env_alloc(void) // 中文注释：创建一个新环境（子进程）
{
	int r; // 中文注释：返回码
	struct Env *e; // 中文注释：新环境指针

	r = env_alloc(&e, curenv->env_id); // 中文注释：分配并初始化新环境
	if (r < 0) { // 中文注释：失败返回错误码
		return r;
	}
	
	bcopy(KERNEL_SP - sizeof(struct Trapframe), &(e->env_tf), sizeof(struct Trapframe)); // 中文注释：复制父环境 Trapframe
	e->env_tf.pc = e->env_tf.cp0_epc; // 中文注释：设置返回地址
	e->env_tf.regs[2] = 0; // 中文注释：子进程返回值 v0=0
	e->env_status = ENV_NOT_RUNNABLE; // 中文注释：初始不可运行
	e->env_pri = curenv->env_pri; // 中文注释：继承父优先级
	
	return e->env_id; // 中文注释：返回新环境 ID
}

/* Overview:
 * 	Set envid's env_status to status.
 *
 * Pre-Condition:
 * 	status should be one of `ENV_RUNNABLE`, `ENV_NOT_RUNNABLE` and
 * `ENV_FREE`. Otherwise return -E_INVAL.
 * 
 * Post-Condition:
 * 	Returns 0 on success, < 0 on error.
 * 	Return -E_INVAL if status is not a valid status for an environment.
 * 	The status of environment will be set to `status` on success.
 */
int sys_set_env_status(int sysno, u_int envid, u_int status) // 中文注释：设置环境运行状态
{
	struct Env *env; // 中文注释：目标环境
	int ret; // 中文注释：返回码
//printf("in set env status\n");
	if (status != ENV_RUNNABLE && status != ENV_NOT_RUNNABLE && status != ENV_FREE) { // 中文注释：参数校验
		return -E_INVAL; // 中文注释：非法状态
	}
	
	ret = envid2env(envid, &env, 0); // 中文注释：获取环境
	if (ret < 0) {
		return ret;
	}
	
	env->env_status = status; // 中文注释：更新状态
	if (status == ENV_RUNNABLE) { // 中文注释：若可运行则加入就绪队列
		LIST_INSERT_HEAD(&env_sched_list[0], env, env_sched_link);
	}
//printf("end set env status\n");
	return 0; // 中文注释：成功
	//	panic("sys_env_set_status not implemented");
}

/* Overview:
 * 	Set envid's trap frame to tf.
 *
 * Pre-Condition:
 * 	`tf` should be valid.
 *
 * Post-Condition:
 * 	Returns 0 on success, < 0 on error.
 * 	Return -E_INVAL if the environment cannot be manipulated.
 *
 * Note: This hasn't be used now?
 */
int sys_set_trapframe(int sysno, u_int envid, struct Trapframe *tf) // 中文注释：设置指定环境的 Trapframe（预留）
{

	return 0; // 中文注释：当前实现为占位成功
}

/* Overview:
 * 	Kernel panic with message `msg`. 
 *
 * Pre-Condition:
 * 	msg can't be NULL
 *
 * Post-Condition:
 * 	This function will make the whole system stop.
 */
void sys_panic(int sysno, char *msg) // 中文注释：触发内核 panic 并输出消息
{
	panic("%s", TRUP(msg)); // 中文注释：直接触发内核 panic
}

/* Overview:
 * 	This function enables caller to receive message from 
 * other process. To be more specific, it will flag 
 * the current process so that other process could send 
 * message to it.
 *
 * Pre-Condition:
 * 	`dstva` is valid (Note: NULL is also a valid value for `dstva`).
 * 
 * Post-Condition:
 * 	This syscall will set the current process's status to 
 * ENV_NOT_RUNNABLE, giving up cpu. 
 */
void sys_ipc_recv(int sysno, u_int dstva) // 中文注释：注册接收 IPC，并阻塞等待
{
	if (curenv == NULL) { // 中文注释：健壮性检查
		printf("curenv in sys_ipc_recv is NULL");
		return; // 中文注释：异常情况直接返回
	}
	
	if (dstva == NULL) {
		// 中文注释：允许不接收页映射，仅接收值
	} else if (dstva >= UTOP || dstva < 0) { // 中文注释：地址检查
		return; // 中文注释：非法地址直接返回
	}
	curenv->env_ipc_recving = 1; // 中文注释：标记正在接收
	curenv->env_ipc_dstva = dstva; // 中文注释：记录接收映射地址
	curenv->env_status = ENV_NOT_RUNNABLE; // 中文注释：阻塞当前环境
	LIST_REMOVE(curenv, env_sched_link); // 中文注释：从就绪队列删除
	sys_yield(); // 中文注释：让出 CPU，进入调度
}

/* Overview:
 * 	Try to send 'value' to the target env 'envid'.
 *
 * 	The send fails with a return value of -E_IPC_NOT_RECV if the
 * target has not requested IPC with sys_ipc_recv.
 * 	Otherwise, the send succeeds, and the target's ipc fields are
 * updated as follows:
 *    env_ipc_recving is set to 0 to block future sends
 *    env_ipc_from is set to the sending envid
 *    env_ipc_value is set to the 'value' parameter
 * 	The target environment is marked runnable again.
 *
 * Post-Condition:
 * 	Return 0 on success, < 0 on error.
 *
 * Hint: the only function you need to call is envid2env.
 */
int sys_ipc_can_send(int sysno, u_int envid, u_int value, u_int srcva,
					 u_int perm) // 中文注释：尝试向目标环境发送 IPC（可选页映射）
{

	int r; // 中文注释：返回码
	struct Env *e; // 中文注释：目标环境
	struct Page *p; // 中文注释：可选映射的物理页
//printf("debug0\n");
	if (srcva != NULL && (srcva >= UTOP || srcva < 0)) { // 中文注释：源页地址检查
		return -E_UNSPECIFIED; // 中文注释：地址越界
	}
	

//printf("debug1, envid = %x\n", envid);
	r = envid2env(envid, &e, 0); // 中文注释：查找目标环境
	if (r < 0) {
		return r;
	}
	
//printf("debug2\n");
	if (e->env_ipc_recving == 0) { // 中文注释：目标未处于接收状态
		return -E_IPC_NOT_RECV; // 中文注释：发送失败
	}

//printf("debug3\n");
	if (srcva != 0) { // 中文注释：需要传递页映射
		p = page_lookup(curenv->env_pgdir, srcva, 0); // 中文注释：查找源页
		r = page_insert(e->env_pgdir, p, e->env_ipc_dstva, perm | PTE_V); // 中文注释：建立共享映射
		if (r < 0) { // 中文注释：失败则返回
			return r;
		}
	}

//printf("debug4\n");
	e->env_ipc_perm = perm | PTE_V; // 中文注释：记录权限
	e->env_ipc_recving = 0; // 中文注释：清除接收标记
	e->env_ipc_from = curenv->env_id; // 中文注释：记录来源
	e->env_ipc_value = value; // 中文注释：记录发送值
	e->env_status = ENV_RUNNABLE; // 中文注释：目标可运行
	LIST_INSERT_HEAD(&env_sched_list[0], e, env_sched_link); // 中文注释：放入就绪队列

	return 0;
}

/* Overview:
 * 	This function is used to write data to device, which is
 * 	represented by its mapped physical address.
 *	Remember to check the validity of device address (see Hint below);
 * 
 * Pre-Condition:
 *      'va' is the startting address of source data, 'len' is the
 *      length of data (in bytes), 'dev' is the physical address of
 *      the device
 * 	
 * Post-Condition:
 *      copy data from 'va' to 'dev' with length 'len'
 *      Return 0 on success.
 *	Return -E_INVAL on address error.
 *      
 * Hint: Use ummapped segment in kernel address space to perform MMIO.
 *	 Physical device address:
 *	* ---------------------------------*
 *	|   device   | start addr | length |
 *	* -----------+------------+--------*
 *	|  console   | 0x10000000 | 0x20   |
 *	|    IDE     | 0x13000000 | 0x4200 |
 *	|    rtc     | 0x15000000 | 0x200  |
 *	* ---------------------------------*
 */
int sys_write_dev(int sysno, u_int va, u_int dev, u_int len) // 中文注释：写设备 MMIO 空间
{
	if (va < 0 || va + len >= UTOP) { // 中文注释：用户地址检查
		printf("wrong va in sys_write_dev!!\n");
		return -E_INVAL; // 中文注释：参数无效
	}
	if (dev < 0x10000020 && dev >= 0x10000000 || // 中文注释：控制台
		dev < 0x13004200 && dev >= 0x13000000 || // 中文注释：IDE
		dev < 0x15000200 && dev >= 0x15000000) { // 中文注释：RTC
		bcopy(va, dev + 0xa0000000, len); // 中文注释：KSEG1 非缓存映射写设备
		return 0; // 中文注释：成功
	} else {
		return -E_INVAL; // 中文注释：设备地址非法
	}
}

/* Overview:
 * 	This function is used to read data from device, which is
 * 	represented by its mapped physical address.
 *	Remember to check the validity of device address (same as sys_read_dev)
 * 
 * Pre-Condition:
 *      'va' is the startting address of data buffer, 'len' is the
 *      length of data (in bytes), 'dev' is the physical address of
 *      the device
 * 
 * Post-Condition:
 *      copy data from 'dev' to 'va' with length 'len'
 *      Return 0 on success, < 0 on error
 *      
 * Hint: Use ummapped segment in kernel address space to perform MMIO.
 */
int sys_read_dev(int sysno, u_int va, u_int dev, u_int len) // 中文注释：读设备 MMIO 空间
{
	if (va < 0 || va + len >= UTOP) { // 中文注释：用户地址检查
		printf("wrong va in sys_read_dev!!\n");
		return -E_INVAL; // 中文注释：参数无效
	}
	if (dev < 0x10000020 && dev >= 0x10000000 || // 中文注释：控制台
		dev < 0x13004200 && dev >= 0x13000000 || // 中文注释：IDE
		dev < 0x15000200 && dev >= 0x15000000) { // 中文注释：RTC
		bcopy(dev + 0xa0000000, va, len); // 中文注释：KSEG1 非缓存映射读设备
		return 0; // 中文注释：成功
	} else {
		return -E_INVAL; // 中文注释：设备地址非法
	}
}
