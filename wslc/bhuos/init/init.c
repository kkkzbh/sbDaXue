#include <asm/asm.h>          // 引入与 MIPS 相关的汇编辅助宏与内联汇编支持
#include <pmap.h>              // 引入物理/虚拟内存管理与页表接口
#include <env.h>               // 引入进程/环境（env）管理接口
#include <printf.h>            // 引入内核态格式化输出函数 printf
#include <kclock.h>            // 引入内核时钟初始化与时基设置接口
#include <trap.h>              // 引入异常/中断（trap）处理初始化接口

extern char aoutcode[];        // 外部符号：A 程序的二进制镜像起始地址（由 code*.c 提供）
extern char boutcode[];        // 外部符号：B 程序的二进制镜像起始地址（由 code*.c 提供）

void mips_init()                           // 系统初始化主入口：完成内存/中断/进程等内核子系统初始化
{	// 函数体开始
	printf("init.c:\tmips_init() is called\n"); // 调试输出：标记已进入 mips_init()
	mips_detect_memory();                    // 探测物理内存布局与大小，为后续内存管理做准备
	
	mips_vm_init();                          // 初始化与 MIPS 相关的虚拟内存机制（段/页/TLB 等常量与表项）
	page_init();                             // 初始化物理页分配器（空闲链表、引用计数等）
	//page_check();                          // 可选：运行物理内存管理自检（实验阶段可按需开启）
	
	env_init();                              // 初始化进程/环境表，准备创建第一个用户态环境
	
	//ENV_CREATE(user_fktest);               // 备选：创建特定用户态测试程序（按实验需要启用）
	//ENV_CREATE(user_pt1);
	//ENV_CREATE(user_idle);
	//ENV_CREATE(user_testpipe);
	//ENV_CREATE(user_testpiperace);
	//ENV_CREATE(user_testptelibrary);
	//ENV_CREATE(user_shelltest);
	ENV_CREATE(user_icode);                  // 创建内置的引导用户程序（icode），用于加载/拉起其他程序
	ENV_CREATE(fs_serv);                     // 创建文件系统服务进程（若采用微内核式服务划分）
	//ENV_CREATE(user_fktest);
	//ENV_CREATE(user_pingpong);
	//ENV_CREATE(user_testfdsharing);	      // 备选：文件描述符共享测试
	//ENV_CREATE(user_testspawn);             // 备选：进程派生/加载测试
	trap_init();                             // 设置异常向量与中断处理入口
	kclock_init();                           // 初始化内核时钟，用于时基与定时中断
	//env_run(&envs[0]);                     // 可直接切换到第 0 个环境运行（通常由调度器决定）

	//env_run(&envs[1]);                     // 也可切换到第 1 个环境（实验调试时使用）
	
	panic("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"); // 若执行至此，说明未进入任何环境，直接触发内核恐慌
	while(1);                                 // 保底：死循环，防止继续往下执行
	panic("init.c:\tend of mips_init() reached!"); // 理论不可达：用于标记异常路径
}	// 函数体结束

void bcopy(const void *src, void *dst, size_t len) // 内存拷贝：从 src 拷贝 len 字节到 dst（可能比 memcpy 更宽松的约束）
{	// 函数体开始
	void *max;                               // 目标区域末地址（开区间）

	max = dst + len;                         // 计算拷贝终点：dst 起始地址加上字节长度
	// 尽可能按机器字（4 字节）对齐拷贝，提高效率
	while (dst + 3 < max)
	{
		*(int *)dst = *(int *)src;           // 按 4 字节整型宽度拷贝一字
		dst+=4;                               // 目标指针前移 4 字节
		src+=4;                               // 源指针前移 4 字节
	}
	// 处理剩余的 0~3 个零散字节，逐字节拷贝补齐
	while (dst < max)
	{
		*(char *)dst = *(char *)src;         // 拷贝 1 字节
		dst+=1;                               // 目标指针前移 1 字节
		src+=1;                               // 源指针前移 1 字节
	}
}	// 函数体结束

void bzero(void *b, size_t len)             // 内存清零：将起始地址 b 开始的 len 字节全部置 0
{	// 函数体开始
	void *max;                               // 清零范围末地址（开区间）

	max = b + len;                           // 计算末尾地址，便于边界判断

	//printf("init.c:\tzero from %x to %x\n",(int)b,(int)max); // 调试输出：观察清零范围（可按需启用）
	
	// 尽可能按机器字（4 字节）对齐清零，提高效率

	while (b + 3 < max)
	{
		*(int *)b = 0;                       // 写入 4 字节 0
		b+=4;                                 // 指针前移 4 字节
	}
	
	// 处理剩余的 0~3 个零散字节，逐字节清零补齐
	while (b < max)
	{
		*(char *)b++ = 0;                    // 写入 1 字节 0 并前移
	}		
	
}	// 函数体结束
