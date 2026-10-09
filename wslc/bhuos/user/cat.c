#include "lib.h"  // 基础库与文件操作接口

char buf[8192];  // 读写缓冲区（8KB）

void
cat(int f, char *s)  // 将文件描述符 f 的内容拷贝到标准输出
{
	long n;  // 实际读取字节数
	int r;   // 写入返回值
writef("in cat, n = %d\n", n);  // 调试：进入 cat
	while((n=read(f, buf, (long)sizeof buf))>0) {  // 循环读取直到 EOF
		if((r=write(1, buf, n))!=n)  // 写到标准输出（fd=1）
			user_panic("write error copying %s: %e", s, r);  // 写失败则报错
	}
writef("after cat, n = %d\n", n);  // 调试：读取结束
	if(n < 0)
		user_panic("error reading %s: %e", s, n);  // 读取出错
}

void
umain(int argc, char **argv)  // 程序入口：依次输出参数指定的文件内容
{
	int f, i;  // 文件描述符与循环变量
writef("argc in cat.c = %d\n", argc);  // 调试：参数个数
	if(argc == 1)
		cat(0, "<stdin>");  // 无参数则从标准输入读
	else for(i=1; i<argc; i++){
		f = open(argv[i], O_RDONLY);  // 以只读打开文件
		if(f < 0)
			// user_panic("can't open %s: %e", argv[i], f);
			writef("can't open %s: %e in user/cat.c", argv[i], f);  // 打开失败打印错误
		else{
			cat(f, argv[i]);  // 复制到标准输出
			close(f);         // 关闭文件
		}
	}
}
