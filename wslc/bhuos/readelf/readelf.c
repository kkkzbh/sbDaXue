// 简化版 ELF 读取器
#include "kerelf.h" // 引入 ELF 相关类型与常量定义
#include <stdio.h>   // 引入标准 I/O 接口

// 功能：判断给定内存是否为 ELF 文件
// 约束：binary 至少应包含 4 个字节以便检查魔数
int is_elf_format(u_char *binary) // 返回 1 表示是 ELF，返回 0 表示不是
{
        Elf32_Ehdr *ehdr = (Elf32_Ehdr *)binary; // 将起始地址解释为 ELF 文件头
        if (ehdr->e_ident[EI_MAG0] == ELFMAG0 && // 检查魔数第 0 字节
                ehdr->e_ident[EI_MAG1] == ELFMAG1 && // 检查魔数第 1 字节
                ehdr->e_ident[EI_MAG2] == ELFMAG2 && // 检查魔数第 2 字节
                ehdr->e_ident[EI_MAG3] == ELFMAG3) { // 检查魔数第 3 字节
                return 1; // 符合 ELF 魔数
        }

        return 0; // 不符合 ELF 魔数
}

// 功能：读取 ELF 基本信息并输出每个节（Section）的虚拟地址
// 约束：binary 非空，size 为其字节数；只做最小化校验
int readelf(u_char *binary, int size) // 成功返回 0
{
        Elf32_Ehdr *ehdr = (Elf32_Ehdr *)binary; // ELF 头指针

        int Nr; // 循环变量：节编号

        Elf32_Shdr *shdr = NULL; // 节头指针（循环体内复用）

        u_char *ptr_sh_table = NULL; // 节头表当前条目地址
        Elf32_Half sh_entry_count; // 节头表项数量
        Elf32_Half sh_entry_size;  // 节头表项大小

        // 校验是否为 ELF 文件（并确保长度满足最小检查要求）
        if (size < 4 || !is_elf_format(binary)) {
                printf("not a standard elf format\n"); // 打印提示：非标准 ELF
                return 0; // 直接返回
        }

        // 计算节头表起始地址与计数、单项大小
	ptr_sh_table = binary + ehdr->e_shoff; // e_shoff：节头表在文件中的偏移
	sh_entry_count = ehdr->e_shnum;        // e_shnum：节头表项数量
	sh_entry_size = ehdr->e_shentsize;     // e_shentsize：单个节头项大小

        // 遍历每个节头项并输出其编号与虚拟地址 sh_addr
	for (Nr = 0; Nr < sh_entry_count; Nr++, ptr_sh_table += sh_entry_size) { // 逐项移动
		shdr = (Elf32_Shdr *)ptr_sh_table; // 将当前位置解释为节头
		printf("%d:0x%x\n", Nr, shdr->sh_addr); // 打印节编号与虚拟地址
	}

        return 0; // 成功结束
}
