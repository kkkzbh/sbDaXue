#include "lib.h"   // 运行库与 IPC/系统调用
#include <mmu.h>    // 内存管理常量
#include <env.h>    // 环境（进程）结构
#include <kerelf.h> // ELF 解析所需结构体

#define debug 0
#define TMPPAGE		(BY2PG)          // 临时栈页的基址（用户空间中的保留位置）
#define TMPPAGETOP	(TMPPAGE+BY2PG)   // 临时栈页的顶部地址

int
init_stack(u_int child, char **argv, u_int *init_esp)  // 构造子进程的初始用户栈
{
	int argc, i, r, tot;
	char *strings;
	u_int *args;

	// 统计参数个数（argc）与字符串总长度（tot）
	tot = 0;
	for (argc=0; argv[argc]; argc++)
		tot += strlen(argv[argc])+1;

	// 确保所有内容能放入一页栈内
	if (ROUND(tot, 4)+4*(argc+3) > BY2PG)
		return -E_NO_MEM;

	// 计算字符串区与参数指针数组在栈页中的放置位置
	strings = (char*)TMPPAGETOP - tot;
	args = (u_int*)(TMPPAGETOP - ROUND(tot, 4) - 4*(argc+1));

	if ((r = syscall_mem_alloc(0, TMPPAGE, PTE_V|PTE_R)) < 0)
		return r;
	// 将参数字符串复制到临时栈页的 strings 区域
	char *ctemp,*argv_temp;
	u_int j;
	ctemp = strings;
	for(i = 0;i < argc; i++)
	{
		argv_temp = argv[i];
		for(j=0;j < strlen(argv[i]);j++)
		{
			*ctemp = *argv_temp;
			ctemp++;
			argv_temp++;
		}
		*ctemp = 0;
		ctemp++;
	}
	// 初始化 args[0..argc-1] 指向上述字符串（注意对子进程而言该页位于 USTACKTOP-BY2PG）
	ctemp = (char *)(USTACKTOP - TMPPAGETOP + (u_int)strings);
	for(i = 0;i < argc;i++)
	{
		args[i] = (u_int)ctemp;
		ctemp += strlen(argv[i])+1;
	}
	// 将 args[argc] 置 0 作为参数数组的结束标记
	ctemp--;
	args[argc] = ctemp;
	// 在 args 下方再压入两个字：argc 与 argv（传递给子进程的 umain）
	u_int *pargv_ptr;
	pargv_ptr = args - 1;
	*pargv_ptr = USTACKTOP - TMPPAGETOP + (u_int)args;
	pargv_ptr--;
	*pargv_ptr = argc;
	// 设置 *init_esp 为子进程的初始栈指针
	*init_esp = USTACKTOP - TMPPAGETOP + (u_int)pargv_ptr;
//	*init_esp = USTACKTOP;	// Change this!

	if ((r = syscall_mem_map(0, TMPPAGE, child, USTACKTOP-BY2PG, PTE_V|PTE_R)) < 0)
		goto error;
	if ((r = syscall_mem_unmap(0, TMPPAGE)) < 0)
		goto error;

	return 0;

error:
	syscall_mem_unmap(0, TMPPAGE);
	return r;
}

int usr_is_elf_format(u_char *binary){
	Elf32_Ehdr *ehdr = (Elf32_Ehdr *)binary;
	if (ehdr->e_ident[0] == ELFMAG0 &&
        ehdr->e_ident[1] == ELFMAG1 &&
        ehdr->e_ident[2] == ELFMAG2 &&
        ehdr->e_ident[3] == ELFMAG3) {
        return 1;
    }   

    return 0;
}

int 
usr_load_elf(int fd , Elf32_Phdr *ph, int child_envid){
		// 提示：此辅助函数可用于将单个 PT_LOAD 段映射到子环境
	u_long va = ph->p_vaddr;
	u_int sgsize = ph->p_memsz;
	u_int bin_size = ph->p_filesz;
	u_int off = ph->p_offset;
	u_int perm = PTE_V | PTE_R;
	int r;
	int i = 0;
	void * blk;
	u_long offset = va - ROUNDDOWN(va, BY2PG);
writef("debug 0, bin_size = %x va = %x offset = %x\n", bin_size, va, offset);
	for (i = 0; i < bin_size; i += BY2PG) {// - BY2PG && bin_size > BY2PG; i += BY2PG) {
writef("debug 1, i = %d\n", i);
		r = read_map(fd2num(fd), off + i, &blk);
writef("debug 2, r = %d\n", r);
		if (r < 0) {
			return r;
		}
		syscall_mem_map(0, blk, child_envid, va + i, perm);
	}
	

/*		syscall_mem_alloc(child_envid, va + i, perm);  // 备选实现：分配页并手动拷贝

writef("debug 3\n");
		const int addr = 0x400000 - BY2PG;
		syscall_mem_map(0, addr, child_envid, va + i, perm);
		if (i == 0) {
writef("debug 3\n");
			user_bcopy(blk, addr + offset, MIN(BY2PG -offset, bin_size));
		} else {
			user_bcopy(blk, addr, MIN(BY2PG, bin_size + offset - i));
		}
		syscall_mem_unmap(0, addr);
writef("debug 3\n");
	}

	if (i < bin_size) {
		r = read_map(fd2num(fd), off + i, &blk);
		if (r < 0) {
			return r;
		}
		if (bin_size - i > 0) {
			user_bzero((u_char *)blk + bin_size - i, BY2PG +i - bin_size);
		}
		syscall_mem_map(0, blk, child_envid, va + i, perm);
		i += BY2PG;
	}
	
	while(i < sgsize) {
		syscall_mem_alloc(child_envid, va + i, perm);
		i += BY2PG;
	}
*/
	return 0;
}

int spawn(char *prog, char **argv)  // 装载并启动用户程序 prog
{
	u_char * elfbuf;
	int r;
	int fd;
	u_int child_envid;
	int size, text_start;
	u_int i, *blk;
	u_int esp;
	Elf32_Ehdr* elf;
	Elf32_Phdr* ph;
	// 注意：部分局部变量未必使用，可按需精简
	// 步骤 1：打开程序文件 prog（路径）
	if((r=open(prog, O_RDONLY))<0){
		//user_panic("spawn ::open line 102 RDONLY wrong !\n");
		writef("spawn ::open line 102 RDONLY wrong !\n");
		return r;
	}
	// 代码从此处填充
	fd = num2fd(r);
	// 步骤 2：分配新环境（可使用 syscall_env_alloc）之前，最好确认目标为可执行文件
	r = syscall_env_alloc();
	if (r < 0) {
		writef("some thing error in spawn.c, syscall_env_alloc\n");
		return r;
	}
	// 步骤 3：使用 init_stack(...) 初始化子环境的用户栈
	child_envid = r;
	r = init_stack(child_envid, argv, &esp);
	if (r < 0) {
		writef("some thing error in spawn.c, init_stack\n");
		return r;
	}
	// 步骤 4：将文件内容映射到新环境的文本段
	//   提示 1：文本段在文件中的偏移可用 objdump 分析；
	//   提示 2：可使用 read_map(...);
	//   提示 3：注意 read_map 在某些情况下并不安全，理解后可采用任意正确方式加载程序；
	// 备注：步骤 1/2 需要健全性检查（打开成功、分配环境成功）。
	elfbuf = (char *)fd2data(fd);
	size = ((struct Filefd *)fd)->f_file.f_size;
	elf = (Elf32_Ehdr *)elfbuf;
	ph = NULL;
	
	u_char *ptr_ph_table = NULL;
	Elf32_Half ph_entry_count;
	Elf32_Half ph_entry_size;

	// 检查是否为有效的 ELF 文件
	if (size < 4 || !usr_is_elf_format(elfbuf)) {
		return -1;
	}
	
	ptr_ph_table = elfbuf + elf->e_phoff;
	ph_entry_count = elf->e_phnum;
	ph_entry_size = elf->e_phentsize;

	while (ph_entry_count--) {
		ph = (Elf32_Phdr *)ptr_ph_table;
		if (ph->p_type == PT_LOAD) {
// writef("before usr_load_elf\n");	
			r = usr_load_elf(fd, ph, child_envid);
			if (r < 0) {
				return r;
			}
// writef("after usr_load_elf\n");	
		}
		ptr_ph_table += ph_entry_size;
	}
	// 代码到此结束（加载阶段）

	struct Trapframe *tf;
	writef("\n::::::::::spawn size : %x  sp : %x::::::::\n",size,esp);
	tf = &(envs[ENVX(child_envid)].env_tf);
	tf->pc = UTEXT;
	tf->regs[29]=esp;


	// 共享库/共享页映射（共享 PTE_LIBRARY 的页）
	u_int pdeno = 0;
	u_int pteno = 0;
	u_int pn = 0;
	u_int va = 0;
	for(pdeno = 0;pdeno<PDX(UTOP);pdeno++)
	{
		if(!((* vpd)[pdeno]&PTE_V))
			continue;
		for(pteno = 0;pteno<=PTX(~0);pteno++)
		{
			pn = (pdeno<<10)+pteno;
			if(((* vpt)[pn]&PTE_V)&&((* vpt)[pn]&PTE_LIBRARY))
			{
				va = pn*BY2PG;

				if((r = syscall_mem_map(0,va,child_envid,va,(PTE_V|PTE_R|PTE_LIBRARY)))<0)
				{

					writef("va: %x   child_envid: %x   \n",va,child_envid);
					user_panic("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");  // 显式失败钩子
					return r;
				}
			}
		}
	}


	if((r = syscall_set_env_status(child_envid, ENV_RUNNABLE)) < 0)
	{
		writef("set child runnable is wrong\n");
		return r;
	}
	return child_envid;		

}

int
spawnl(char *prog, char *args, ...)
{
	return spawn(prog, &args);
}
