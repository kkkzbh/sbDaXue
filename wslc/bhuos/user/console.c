#include "lib.h"  // 基础库与 fd 接口
#include <mmu.h>   // 常量/宏

static int cons_read(struct Fd*, void*, u_int, u_int);        // 控制台读取
static int cons_write(struct Fd*, const void*, u_int, u_int); // 控制台写入
static int cons_close(struct Fd*);                             // 空操作关闭
static int cons_stat(struct Fd*, struct Stat*);                // 状态查询

struct Dev devcons =
{
.dev_id=	'c',        // 设备 ID：控制台
.dev_name=	"cons",   // 名称
.dev_read=	cons_read, // 读函数
.dev_write=	cons_write,// 写函数
.dev_close=	cons_close,// 关闭函数
.dev_stat=	cons_stat,  // 状态函数
};

int
iscons(int fdnum)  // 判断给定 fd 是否为控制台
{
	int r;
	struct Fd *fd;

	if ((r = fd_lookup(fdnum, &fd)) < 0)
		return r;
	return fd->fd_dev_id == devcons.dev_id;
}

int
opencons(void)  // 打开新的控制台 fd
{
	int r;
	struct Fd *fd;

	if ((r = fd_alloc(&fd)) < 0)
		return r;
	if ((r = syscall_mem_alloc(0, (u_int)fd, PTE_V|PTE_R|PTE_LIBRARY)) < 0)
		return r;
	fd->fd_dev_id = devcons.dev_id;
	fd->fd_omode = O_RDWR;
	return fd2num(fd);
}

int
cons_read(struct Fd *fd, void *vbuf, u_int n, u_int offset)  // 从控制台读取一个字符
{
	int c;

	USED(offset);
	// writef("got into cons_read");  // 调试
	if (n == 0)
		return 0;

	while ((c = syscall_cgetc()) == 0)  // 忙等时主动让出 CPU
		syscall_yield();

	if (c == 8 || c == 127)
		writef("\b \b");
	else if (c!='\r') 
		writef("%c",c);
	else
		writef("\n");

	if (c < 0)
		return c;
	if (c == 0x04)	// Ctrl-D 视作 EOF
		return 0;
	*(char*)vbuf = c;
	return 1;
}

int
cons_write(struct Fd *fd, const void *vbuf, u_int n, u_int offset)  // 将缓冲区写到控制台
{
	int tot, m;
	char buf[128];

	USED(offset);

	// 需要以 NUL 结尾传给底层输出：分块复制到临时 buf，并补 NUL
	for(tot=0; tot<n; tot+=m) {
		m = n - tot;
		if (m > sizeof buf-1)
			m = sizeof buf-1;
		user_bcopy((char*)vbuf+tot, buf, m);
		buf[m] = 0;
		writef("%s",buf);
	}
	return tot;
}

int
cons_close(struct Fd *fd)  // 控制台关闭：无资源可释放
{
	USED(fd);

	return 0;
}

int
cons_stat(struct Fd *fd, struct Stat *stat)  // 控制台状态：仅设置名称
{
	strcpy(stat->st_name, "<cons>");
	return 0;
}
