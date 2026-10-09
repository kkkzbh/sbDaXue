#include "lib.h"  // 基础库与写接口



static void user_out2string(void *arg, char *s, int l)  // 将输出累积到字符串缓冲区
{
    int i;
	char * b = (char *)arg;  // 目标缓冲区
    // 特殊终止调用：长度 1 且内容为'\0' 表示结束
    if ((l==1) && (s[0] == '\0')) return;
    
    for (i=0; i< l; i++) {
	b[i]=s[i];  // 逐字符拷贝到目标缓冲区
    }
}


int fwritef(int fd, const char *fmt, ...)  // 将格式化字符串输出到指定 fd
{
	char buf[512];
	va_list ap;
	va_start(ap, fmt);
	user_bzero((void *) buf, 512);
	user_lp_Print(user_out2string, buf, fmt, ap);
	va_end(ap);
	return write(fd, buf, strlen(buf));
}
