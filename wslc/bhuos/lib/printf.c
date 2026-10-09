/* 中文说明：内核格式化输出接口的封装。统一采用中文注释风格。*/

#include <printf.h> // 中文注释：对外提供 printf/_panic 等声明
#include <print.h> // 中文注释：底层格式化与输出适配（lp_Print）
#include <drivers/gxconsole/dev_cons.h> // 中文注释：控制台设备输出

void printcharc(char ch); // 中文注释：单字符输出到控制台

void halt(void); // 中文注释：停止系统（预留）

static void myoutput(void *arg, char *s, int l) // 中文注释：lp_Print 回调，将缓冲区输出到控制台
{
    int i; // 中文注释：循环变量

    if ((l==1) && (s[0] == '\0')) return; // 中文注释：特殊终止调用（仅 0 字符）
    
    for (i=0; i< l; i++) { // 中文注释：逐字符输出
	printcharc(s[i]); // 中文注释：输出当前字符
	if (s[i] == '\n') printcharc('\n'); // 中文注释：换行时按照控制台需求再追加换行
    }
}

void printf(char *fmt, ...) // 中文注释：内核 printf，转发到 lp_Print
{
    va_list ap; // 中文注释：变参列表
    va_start(ap, fmt); // 中文注释：初始化变参
    lp_Print(myoutput, 0, fmt, ap); // 中文注释：格式化并通过回调输出
    va_end(ap); // 中文注释：结束变参
}

void
_panic(const char *file, int line, const char *fmt,...) // 中文注释：触发内核恐慌并打印定位信息
{
	va_list ap; // 中文注释：变参列表

	va_start(ap, fmt); // 中文注释：初始化变参
	printf("panic at %s:%d: ", file, line); // 中文注释：打印文件名与行号
	lp_Print(myoutput, 0, (char *)fmt, ap); // 中文注释：打印自定义信息
	printf("\n"); // 中文注释：换行
	va_end(ap); // 中文注释：结束变参

	for(;;); // 中文注释：进入死循环，防止继续执行
}
