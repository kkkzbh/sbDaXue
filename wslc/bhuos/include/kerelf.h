
#ifndef _KER_ELF_H // 头文件防重包含开始
#define _KER_ELF_H // 定义本头文件的防重包含宏

#include <types.h> // 基础类型

typedef u_int64_t uint64_t; // 64 位无符号整数
typedef u_int32_t uint32_t; // 32 位无符号整数
typedef u_int16_t uint16_t; // 16 位无符号整数

typedef uint16_t Elf32_Half;   // 半字（16 位）
typedef uint32_t Elf32_Word;   // 字（32 位）
typedef int32_t  Elf32_Sword;  // 有符号字（32 位）
typedef uint64_t Elf32_Xword;  // 扩展字（64 位）
typedef int64_t  Elf32_Sxword; // 有符号扩展字（64 位）
typedef uint32_t Elf32_Addr;   // 地址
typedef uint32_t Elf32_Off;    // 偏移
typedef uint16_t Elf32_Section;// 段表索引
typedef uint32_t Elf32_Symndx; // 符号表索引

#define EI_NIDENT 16 // ELF 识别字段长度

typedef struct {                      // ELF 文件头（32 位）
    unsigned char e_ident[EI_NIDENT]; // 魔数与识别信息
    Elf32_Half e_type;                // 文件类型
    Elf32_Half e_machine;             // 目标机器
    Elf32_Word e_version;             // 版本
    Elf32_Addr e_entry;               // 入口地址
    Elf32_Off  e_phoff;               // 程序头表偏移
    Elf32_Off  e_shoff;               // 段头表偏移
    Elf32_Word e_flags;               // 标志
    Elf32_Half e_ehsize;              // 本文件头大小
    Elf32_Half e_phentsize;           // 程序头项大小
    Elf32_Half e_phnum;               // 程序头项个数
    Elf32_Half e_shentsize;           // 段头项大小
    Elf32_Half e_shnum;               // 段头项个数
    Elf32_Half e_shstrndx;            // 段名字符串表索引
} Elf32_Ehdr; // 结构体结束

#define EI_MAG0   0  // e_ident[0] 应为 0x7F
#define ELFMAG0 0x7f // 魔数字节 0
#define EI_MAG1   1  // e_ident[1] 应为 'E'
#define ELFMAG1 'E'  // 魔数字节 1
#define EI_MAG2   2  // e_ident[2] 应为 'L'
#define ELFMAG2 'L'  // 魔数字节 2
#define EI_MAG3   3  // e_ident[3] 应为 'F'
#define ELFMAG3 'F'  // 魔数字节 3

typedef struct {            // 程序头（段）
    Elf32_Word p_type;      // 段类型
    Elf32_Off  p_offset;    // 文件内偏移
    Elf32_Addr p_vaddr;     // 目标虚拟地址
    Elf32_Addr p_paddr;     // 目标物理地址
    Elf32_Word p_filesz;    // 文件中大小
    Elf32_Word p_memsz;     // 内存中大小
    Elf32_Word p_flags;     // 访问权限
    Elf32_Word p_align;     // 对齐
} Elf32_Phdr; // 结构体结束

#define PT_NULL    0         // 忽略
#define PT_LOAD    1         // 需要加载到内存
#define PT_DYNAMIC 2         // 动态链接信息
#define PT_INTERP  3         // 解释器路径
#define PT_NOTE    4         // 附注
#define PT_SHLIB   5         // 预留
#define PT_PHDR    6         // 程序头自身
#define PT_NUM     7         // 保留数量边界
#define PT_LOOS    0x60000000 // OS 专用范围起
#define PT_HIOS    0x6fffffff // OS 专用范围止
#define PT_LOPROC  0x70000000 // 处理器专用范围起
#define PT_HIPROC  0x7fffffff // 处理器专用范围止

#define PF_X       (1 << 0)  // 可执行
#define PF_W       (1 << 1)  // 可写
#define PF_R       (1 << 2)  // 可读
#define PF_MASKPROC 0xf0000000 // 处理器专用位掩码

int load_elf(u_char* binary, int size,           // 载入内存中的 ELF 映像
             u_long* entry_point, void* user_data, // 输出入口地址，透传用户数据
             int (*map)(u_long, u_int32_t, u_char*, u_int32_t, void*)); // 回调：建立段映射

#endif // 结束防重包含
