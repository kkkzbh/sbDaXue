#include "lib.h"  // 基本字符串/内存操作的声明依赖

int
strlen(const char *s)  // 计算以'\0'结尾字符串的长度（不含终止符）
{
	int n;  // 计数器

	for (n=0; *s; s++)  // 遍历直到遇到终止符
		n++;  // 每遇到一个非零字符长度加一
	return n;  // 返回累计长度
}

char*
strcpy(char *dst, const char *src)  // 将 src 字符串复制到 dst（包含终止符）
{
	char *ret;  // 返回原始目标指针

	ret = dst;  // 保存起始地址
	while ((*dst++ = *src++) != 0)  // 逐字节复制，包含终止符
		;  // 空循环体，复制在赋值表达式中完成
	return ret;  // 返回目标起始地址
}

const char*
strchr(const char *s, char c)  // 在 s 中查找字符 c 的第一次出现
{
	for(; *s; s++)  // 遍历字符串
		if(*s == c)  // 命中则返回当前位置指针
			return s;
	return 0;  // 未找到返回空指针
}

void *
memcpy(void *destaddr,void const *srcaddr,u_int len)  // 按字节从 srcaddr 拷贝 len 个字节到 destaddr
{
	char *dest = destaddr;  // 目标指针按字节访问
	char const *src = srcaddr;  // 源指针按字节访问

	while(len-->0)  // 循环 len 次
		*dest++=*src++;  // 复制当前字节并自增指针
	return destaddr;  // 返回目标基址
}


int
strcmp(const char *p, const char *q)  // 比较两个以'\0'结尾的字符串的字典序
{
	while (*p && *p == *q)  // 跳过公共前缀
		p++, q++;
	if ((u_int)*p < (u_int)*q)  // p 首个差异字符较小
		return -1;
	if ((u_int)*p > (u_int)*q)  // p 首个差异字符较大
		return 1;
	return 0;  // 完全相等
}
