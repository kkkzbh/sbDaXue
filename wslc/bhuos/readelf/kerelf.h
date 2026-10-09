#ifndef _KER_ELF_H // 头文件保护宏开始
#define _KER_ELF_H // 定义头文件保护宏

// 本文件为精简版 ELF 定义，仅保留 ELF32 相关的必要类型、结构与常量

#include "types.h" // 引入基础整数类型定义

typedef u_int64_t               uint64_t; // 别名：无符号 64 位整数
typedef u_int32_t               uint32_t; // 别名：无符号 32 位整数
typedef u_int16_t               uint16_t; // 别名：无符号 16 位整数

typedef uint16_t Elf32_Half;   // ELF 16 位半字

typedef uint32_t Elf32_Word;   // ELF 32 位无符号字
typedef int32_t  Elf32_Sword;  // ELF 32 位有符号字

typedef uint64_t Elf32_Xword;  // ELF 64 位无符号扩展字（为兼容性保留）
typedef int64_t  Elf32_Sxword; // ELF 64 位有符号扩展字（为兼容性保留）

typedef uint32_t Elf32_Addr;   // 虚拟地址类型

typedef uint32_t Elf32_Off;    // 文件内偏移类型

typedef uint16_t Elf32_Section;// 节（Section）索引类型（16 位）

typedef uint32_t Elf32_Symndx; // 符号表索引类型


// ELF 文件头，位于每个 ELF 文件的开头

#define EI_NIDENT (16) // e_ident 标识数组长度（字节）

typedef struct { // ELF 文件头结构
        unsigned char   e_ident[EI_NIDENT];     // 魔数及其他标识信息
        Elf32_Half      e_type;                 // 对象文件类型
        Elf32_Half      e_machine;              // 目标体系结构
        Elf32_Word      e_version;              // 文件版本
        Elf32_Addr      e_entry;                // 入口虚拟地址
        Elf32_Off       e_phoff;                // 程序头表文件偏移
        Elf32_Off       e_shoff;                // 节头表文件偏移
        Elf32_Word      e_flags;                // 处理器相关标志
        Elf32_Half      e_ehsize;               // ELF 头大小（字节）
        Elf32_Half      e_phentsize;            // 程序头表项大小
        Elf32_Half      e_phnum;                // 程序头表项数量
        Elf32_Half      e_shentsize;            // 节头表项大小
        Elf32_Half      e_shnum;                // 节头表项数量
        Elf32_Half      e_shstrndx;             // 节名字符串表索引
} Elf32_Ehdr; // 结构体结束

// e_ident 字节字段的索引与其可能的取值

#define EI_MAG0         0               // 文件标识第 0 字节索引
#define ELFMAG0         0x7f            // 魔数第 0 字节（0x7F）

#define EI_MAG1         1               // 文件标识第 1 字节索引
#define ELFMAG1         'E'             // 魔数字符 'E'

#define EI_MAG2         2               // 文件标识第 2 字节索引
#define ELFMAG2         'L'             // 魔数字符 'L'

#define EI_MAG3         3               // 文件标识第 3 字节索引
#define ELFMAG3         'F'             // 魔数字符 'F'


typedef struct{ // 节（Section）头结构
        Elf32_Word sh_name;                 // 节名在字符串表中的偏移
        Elf32_Word sh_type;                 // 节类型
        Elf32_Word sh_flags;                // 节标志
        Elf32_Addr sh_addr;                 // 节的虚拟地址
        Elf32_Off  sh_offset;               // 节在文件内的偏移
        Elf32_Word sh_size;                 // 节大小（字节）
        Elf32_Word sh_link;                 // 关联信息（与类型相关）
        Elf32_Word sh_info;                 // 额外信息（与类型相关）
        Elf32_Word sh_addralign;            // 地址对齐要求
        Elf32_Word sh_entsize;              // 表项大小（对表格类节有效）
}Elf32_Shdr; // 结构体结束


// 程序段（Program Segment）头结构

typedef struct { // 程序段头
        Elf32_Word      p_type;                 // 段类型
        Elf32_Off       p_offset;               // 段在文件内的偏移
        Elf32_Addr      p_vaddr;                // 段的虚拟地址
        Elf32_Addr      p_paddr;                // 段的物理地址（部分平台使用）
        Elf32_Word      p_filesz;               // 文件中大小
        Elf32_Word      p_memsz;                // 装载到内存后的大小
        Elf32_Word      p_flags;                // 段权限标志
        Elf32_Word      p_align;                // 对齐要求
} Elf32_Phdr; // 结构体结束


// p_type（段类型）的合法取值

#define PT_NULL         0               // 表项未使用
#define PT_LOAD         1               // 可装入段
#define PT_DYNAMIC      2               // 动态链接信息
#define PT_INTERP       3               // 程序解释器
#define PT_NOTE         4               // 附加说明信息
#define PT_SHLIB        5               // 保留
#define PT_PHDR         6               // 程序头表自身所在段
#define PT_NUM          7               // 已定义类型数量
#define PT_LOOS         0x60000000      // OS 特定范围起始
#define PT_HIOS         0x6fffffff      // OS 特定范围结束
#define PT_LOPROC       0x70000000      // 处理器特定范围起始
#define PT_HIPROC       0x7fffffff      // 处理器特定范围结束

// p_flags（段权限）的合法取值

#define PF_X            (1 << 0)        // 可执行
#define PF_W            (1 << 1)        // 可写
#define PF_R            (1 << 2)        // 可读
#define PF_MASKPROC     0xf0000000      // 处理器特定掩码

int readelf(u_char *binary,int size); // 对外导出的 ELF 解析函数原型

#endif // kerelf.h 头文件保护宏结束
