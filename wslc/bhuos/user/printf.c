#include "lib.h"  // 引入运行库与 writef/user_lp_Print 等声明

void halt(void);  // 可选的停止原语声明（如需使用）

// 底层输出适配：将格式化后的字符串逐字符写到控制台
static void user_myoutput(void *arg, char *s, int l)
{
    int i;  // 循环计数器

    // 约定：长度为 1 且内容为'\0' 代表“结束调用”，无需输出
    if ((l==1) && (s[0] == '\0')) return;  // 特殊终止信号，直接返回
    
    for (i=0; i< l; i++) {  // 逐字符输出缓冲区内容
		syscall_putchar(s[i]);  // 写出一个字符
		if (s[i] == '\n') syscall_putchar('\n');  // 行尾再补一个换行（控制台行为需要）
    }
}

// 用户态的简易 printf，输出到控制台
void writef(char *fmt, ...)
{
    va_list ap;  // 变参句柄
    va_start(ap, fmt);  // 初始化变参访问
    user_lp_Print(user_myoutput, 0, fmt, ap);  // 调用通用格式化引擎
    va_end(ap);  // 结束变参访问
}

// 终止前打印 panic 信息（包含源文件与行号）
void
_user_panic(const char *file, int line, const char *fmt,...)
{
	va_list ap;  // 变参句柄

	va_start(ap, fmt);  // 开始读取可变参数
	writef("panic at %s:%d: ", file, line);  // 打印触发位置
	user_lp_Print(user_myoutput, 0, (char *)fmt, ap);  // 打印具体信息
	writef("\n");  // 末尾换行
	va_end(ap);  // 收尾

	for(;;);  // 停滞于此，等待内核回收
}
