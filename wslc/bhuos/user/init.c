#include "lib.h"  // 基础库与文件/进程接口

struct {                // 测试已初始化数据段（.data）
	char msg1[5000];      // 填充字符串 1
	char msg2[1000];      // 填充字符串 2
} data = {
	"this is initialized data",
	"so is this"
};

char bss[6000];  // 测试未初始化数据段（.bss），应全为 0

inline int MY_MUL(int a,int b)  // 简单乘法：通过累加实现
{
	int i;
	int sum;
	for(i=0,sum=0;i<b;sum+=a,i++);  // 循环 b 次，每次累加 a
	return sum;
}

int
sum(char *s, int n)  // 计算加权校验和（用于验证数据段/ bss）
{
	int i, tot;

	tot = 0;
	for(i=0; i<n; i++)
		tot ^= MY_MUL(i,s[i]);  // 累加 XOR 形式
	return tot;
}
		
void
umain(int argc, char **argv)  // init 进程：自检并启动 shell
{
	int i, r, x, want;

	writef("init: running\n");

	want = 0xf989e;  // 期望的 .data 校验值（与编译结果绑定）
	if ((x=sum((char*)&data, sizeof data)) != want)
		writef("init: data is not initialized: got sum %08x wanted %08x\n",
			x, want);
	else
		writef("init: data seems okay\n");
	if ((x=sum(bss, sizeof bss)) != 0)
		writef("bss is not initialized: wanted sum 0 got %08x\n", x);
	else
		writef("init: bss seems okay\n");

	writef("init: args:");
	for (i=0; i<argc; i++)
		writef(" '%s'", argv[i]);
	writef("\n");

	writef("init: running sh\n");

	// 直接由内核启动，初始无打开的文件描述符
	close(0);
	if ((r = opencons()) < 0)
		user_panic("opencons: %e", r);
	if (r != 0)
		user_panic("first opencons used fd %d", r);
	if ((r = dup(0, 1)) < 0)
		user_panic("dup: %d", r);

write(1,"LALA",4);  // 直接向控制台写入

	for (;;) {  // 循环拉起 shell
		writef("init: starting sh\n");  // 启动 shell
		r = spawnl("sh.b", "sh", (char*)0);
		if (r < 0) {
			writef("init: spawn sh: %e\n", r);
			continue;
		}
		wait(r);  // 等待子进程退出
	
	}
}
