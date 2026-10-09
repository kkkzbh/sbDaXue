#ifndef _INC_TYPES_H_ // 头文件防重包含开始
#define _INC_TYPES_H_ // 定义本头文件的防重包含宏

#ifndef NULL // 若未定义 NULL，则在此给出定义
#define NULL ((void *) 0) // 空指针常量
#endif // 结束对 NULL 的条件判断

typedef unsigned char      u_int8_t;  // 8 位无符号整数
typedef short               int16_t;  // 16 位有符号整数
typedef unsigned short    u_int16_t;  // 16 位无符号整数
typedef int                 int32_t;  // 32 位有符号整数
typedef unsigned int      u_int32_t;  // 32 位无符号整数
typedef long long           int64_t;  // 64 位有符号整数
typedef unsigned long long u_int64_t; // 64 位无符号整数

typedef int32_t register_t; // 通用寄存器宽度对应的整数类型（32 位）

typedef unsigned char  u_char;  // 传统别名：无符号字符
typedef unsigned short u_short; // 传统别名：无符号短整型
typedef unsigned int   u_int;   // 传统别名：无符号整型
typedef unsigned long  u_long;  // 传统别名：无符号长整型

typedef u_int64_t u_quad_t; // 64 位无符号整型别名
typedef int64_t   quad_t;   // 64 位有符号整型别名
typedef quad_t*   qaddr_t;  // 指向 64 位有符号数的指针

typedef u_int32_t size_t; // 大小/长度类型（32 位）

#define MIN(_a, _b) \
    ({ typeof(_a) __a = (_a); typeof(_b) __b = (_b); __a <= __b ? __a : __b; }) // 返回较小值（GNU 语法扩展）

#define static_assert(c) switch (c) case 0: case(c): // 编译期断言：表达式为假将导致编译报错

#define offsetof(type, member) ((size_t)(&((type *)0)->member)) // 结构体成员相对结构起始的偏移

#define ROUND(a, n)     (((((u_long)(a)) + (n) - 1)) & ~((n) - 1)) // 向上按 n 对齐（n 为 2 的幂）
#define ROUNDDOWN(a, n) (((u_long)(a)) & ~((n) - 1))              // 向下按 n 对齐（n 为 2 的幂）

#endif // 结束防重包含
