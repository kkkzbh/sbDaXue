#ifndef _printf_h_ // 头文件防重包含开始
#define _printf_h_ // 定义本头文件的防重包含宏

#include <stdarg.h> // 可变参数支持
void printf(char* fmt, ...); // 简化版 printf，输出到控制台

void _panic(const char*, int, const char*, ...) // 内核致命错误输出并停机
    __attribute__((noreturn));                  // 函数不返回

#define panic(...) _panic(__FILE__, __LINE__, __VA_ARGS__) // 带文件与行号的 panic 宏

#endif // 结束防重包含
