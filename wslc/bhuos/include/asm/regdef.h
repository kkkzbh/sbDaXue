#ifndef __ASM_MIPS_REGDEF_H // 头文件防重包含开始
#define __ASM_MIPS_REGDEF_H // 定义本头文件的防重包含宏

#define zero    $0  // 常量 0 寄存器
#define AT      $1  // 汇编器保留寄存器
#define v0      $2  // 返回值/表达式值
#define v1      $3  // 返回值/表达式值
#define a0      $4  // 参数 0
#define a1      $5  // 参数 1
#define a2      $6  // 参数 2
#define a3      $7  // 参数 3
#define t0      $8  // 临时寄存器
#define t1      $9  // 临时寄存器
#define t2      $10 // 临时寄存器
#define t3      $11 // 临时寄存器
#define t4      $12 // 临时寄存器
#define t5      $13 // 临时寄存器
#define t6      $14 // 临时寄存器
#define t7      $15 // 临时寄存器
#define s0      $16 // 被保存寄存器
#define s1      $17 // 被保存寄存器
#define s2      $18 // 被保存寄存器
#define s3      $19 // 被保存寄存器
#define s4      $20 // 被保存寄存器
#define s5      $21 // 被保存寄存器
#define s6      $22 // 被保存寄存器
#define s7      $23 // 被保存寄存器
#define t8      $24 // 临时寄存器
#define t9      $25 // 临时/过程寄存器
#define jp      $25 // 跳转寄存器同名（别名）
#define k0      $26 // 内核保留寄存器
#define k1      $27 // 内核保留寄存器
#define gp      $28 // 全局指针
#define sp      $29 // 栈指针
#define fp      $30 // 帧指针
#define s8      $30 // 帧指针别名
#define ra      $31 // 返回地址

#endif // 结束防重包含
