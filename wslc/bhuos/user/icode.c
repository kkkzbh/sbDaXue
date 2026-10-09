#include "lib.h"  // 基础库与文件/进程接口

void
umain(void)  // 初始用户进程：打印 motd 并拉起 init
{
	int fd, n, r;
	char buf[512+1];

	writef("icode: open /motd\n");  // 打开消息文件
	if ((fd = open("/motd", O_RDONLY)) < 0)
		user_panic("icode: open /motd: %e", fd);

	writef("icode: read /motd\n");  // 读取并打印
	while ((n = read(fd, buf, sizeof buf-1)) > 0){
		buf[n] = 0;
		writef("%s\n",buf);
	}

	writef("icode: close /motd\n");  // 关闭（示例保留注释掉的 close）
//	close(fd);

	writef("icode: spawn /init\n");  // 启动 init 进程
	if ((r = spawnl("init.b", "init", "initarg1", "initarg2", (char*)0)) < 0)
		user_panic("icode: spawn /init: %e", r);

	writef("icode: exiting\n");  // 退出
}
