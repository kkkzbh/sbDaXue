#ifndef _print_h_ // 头文件防重包含开始
#define _print_h_ // 定义本头文件的防重包含宏

#include <stdarg.h> // 可变参数支持

#define LP_MAX_BUF 1000 // 输出缓冲区最大长度

void lp_Print(void (*output)(void*, char*, int), // 输出回调：写入一段字符串
              void* arg,                         // 传递给回调的用户参数
              char* fmt,                         // 格式化字符串
              va_list ap);                       // 可变参数列表

#endif // 结束防重包含
