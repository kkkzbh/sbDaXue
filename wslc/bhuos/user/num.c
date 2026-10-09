#include "lib.h"  // 基础库与 IO 接口

int bol = 1;   // 是否行首（begin of line）
int line = 0;  // 当前行号

void
num(int f, const char *s)  // 给每行添加行号并输出
{
	long n;
	int r;
	char c;

	while ((n = read(f, &c, 1)) > 0) {  // 逐字节读取
		if (bol) {  // 行首输出行号
			writef("%5d ", ++line);
			bol = 0;
		}
		if ((r = write(1, &c, 1)) != 1)
			user_panic("write error copying %s: %e", s, r);
		if (c == '\n')  // 换行后回到行首状态
			bol = 1;
	}
	if (n < 0)
		user_panic("error reading %s: %e", s, n);
}

void
umain(int argc, char **argv)  // 命令入口
{
	int f, i;

	// binaryname = "num.b";  // 保留注释，标记可执行名
	if (argc == 1)
		num(0, "<stdin>");
	else
		for (i = 1; i < argc; i++) {
			f = open(argv[i], O_RDONLY);
			if (f < 0)
				user_panic("can't open %s: %e", argv[i], f);
			else {
				num(f, argv[i]);
				close(f);
			}
		}
	exit();
}
