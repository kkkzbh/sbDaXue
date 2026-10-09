// 基本类型与常用宏定义（精简版）

#ifndef _INC_TYPES_H_ // 头文件保护宏开始
#define _INC_TYPES_H_ // 定义头文件保护宏

#ifndef NULL // 若未定义 NULL，则进行定义
#define NULL ((void *) 0) // 空指针常量
#endif // !NULL

typedef unsigned char            u_int8_t; // 无符号 8 位整数
typedef short                    int16_t;  // 有符号 16 位整数
typedef unsigned short           u_int16_t; // 无符号 16 位整数
typedef int                      int32_t;  // 有符号 32 位整数
typedef unsigned int             u_int32_t; // 无符号 32 位整数
typedef long long                int64_t;  // 有符号 64 位整数
typedef unsigned long long       u_int64_t; // 无符号 64 位整数

typedef int32_t                  register_t; // 寄存器宽度对应的整型（本实验为 32 位）

typedef unsigned char            u_char;  // 常用别名：无符号字节
typedef unsigned short           u_short; // 常用别名：无符号短整型
typedef unsigned int             u_int;   // 常用别名：无符号整型
typedef unsigned long            u_long;  // 常用别名：无符号长整型

typedef u_int64_t                u_quad_t; // 64 位无符号（历史称“quad”）
typedef int64_t                  quad_t;   // 64 位有符号类型
typedef quad_t*                  qaddr_t;  // 指向 64 位量的指针

// 取较小值的宏：使用 GNU C 语句表达式，确保每个参数仅求值一次
#define MIN(_a, _b) /* 返回较小者 */ \
    ({ /* 语句表达式开始 */ \
        typeof(_a) __a = (_a); /* 保存 a 的值与类型 */ \
        typeof(_b) __b = (_b); /* 保存 b 的值与类型 */ \
        __a <= __b ? __a : __b; /* 比较并返回较小值 */ \
    }) // 语句表达式结束

// 编译期断言：条件为假时制造语法错误
#define static_assert(c) switch (c) case 0: case(c): // 通过重复 case 实现检查

#define offsetof(type, member)  ((size_t)(&((type *)0)->member)) // 计算结构体成员偏移

// 对齐相关宏（n 必须为 2 的幂）
#define ROUND(a, n)      (((((u_long)(a))+(n)-1)) & ~((n)-1)) // 向上按 n 对齐
#define ROUNDDOWN(a, n)  (((u_long)(a)) & ~((n)-1))           // 向下按 n 对齐

#endif // !_INC_TYPES_H_ 头文件保护宏结束
