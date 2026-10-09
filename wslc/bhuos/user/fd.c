#include "lib.h"  // 运行库与系统调用封装
#include "fd.h"   // 文件描述符与设备抽象
#include <mmu.h>   // 虚拟内存常量/宏
#include <env.h>   // 环境（进程）结构

#define debug 0  // 调试开关：非零时输出调试信息

#define MAXFD 32  // 允许的最大打开文件数
#define FILEBASE 0x60000000  // 数据页起始虚拟地址（映射文件内容）
#define FDTABLE (FILEBASE-PDMAP)  // fd 表区域基址（每个 fd 占一页）

#define INDEX2FD(i)	(FDTABLE+(i)*BY2PG)  // 由下标计算 fd 页虚拟地址
#define INDEX2DATA(i)	(FILEBASE+(i)*PDMAP)  // 由下标计算数据区（映射文件）起始地址

static struct Dev *devtab[] = {
	&devfile,  // 文件设备
	&devcons,  // 控制台设备
	&devpipe,  // 管道设备
	0          // 表尾标记
};

int
dev_lookup(int dev_id, struct Dev **dev)  // 按设备 ID 查找设备表项
{
	int i;  // 遍历下标

	for (i = 0; devtab[i]; i++)  // 遍历已注册设备
		if (devtab[i]->dev_id == dev_id) {  // 匹配即返回
			*dev = devtab[i];
			return 0;
		}

	writef("[%08x] unknown device type %d\n", env->env_id, dev_id);  // 未知设备类型
	return -E_INVAL;  // 参数非法
}

int
fd_alloc(struct Fd **fd)  // 分配一个空闲的 fd 页地址（不分配物理页）
{
	u_int va;   // 备选 fd 页虚拟地址
	u_int fdno; // fd 下标

	for (fdno = 0; fdno < MAXFD - 1; fdno++) {  // 从小到大寻找空位
		va = INDEX2FD(fdno);  // 计算对应页地址

		// 若对应的二级页目录项无效，则该范围尚未使用
		if (((* vpd)[va / PDMAP] & PTE_V) == 0) {
			*fd = (struct Fd *)va;  // 返回页地址即可
			return 0;
		}

		// 页表项无效，说明该页未映射——可用
		if (((* vpt)[va / BY2PG] & PTE_V) == 0) {  // 该 fd 目前未占用
			*fd = (struct Fd *)va;  // 返回页地址
			return 0;
		}
	}

	return -E_MAX_OPEN;  // 已无空闲 fd
}

void
fd_close(struct Fd *fd)  // 取消映射该 fd 页
{
	syscall_mem_unmap(0, (u_int)fd);  // 传 0 表示当前环境
}

int
fd_lookup(int fdnum, struct Fd **fd)  // 校验 fd 号并返回对应页地址
{
	u_int va;  // 目标 fd 页地址

	if (fdnum >= MAXFD) {  // 越界检查
		return -E_INVAL;
	}

	va = INDEX2FD(fdnum);  // 计算页地址

	if (((* vpt)[va / BY2PG] & PTE_V) != 0) {  // 页已映射，fd 在用
		*fd = (struct Fd *)va;
		return 0;
	}

	return -E_INVAL;  // 未映射/非法 fd
}

u_int
fd2data(struct Fd *fd)  // 将 fd 页地址转换为其数据区首地址
{
	return INDEX2DATA(fd2num(fd));
}

int
fd2num(struct Fd *fd)  // 将 fd 页地址转换为 fd 下标
{
	return ((u_int)fd - FDTABLE) / BY2PG;
}
int
num2fd(int fd)  // 将 fd 下标转换为 fd 页虚拟地址
{
	return fd * BY2PG + FDTABLE;
}

int
close(int fdnum)  // 关闭给定 fd：调用设备关闭并解除映射
{
	int r;  // 返回码
	struct Dev *dev;  // 设备表项
	struct Fd *fd;    // fd 页

	if ((r = fd_lookup(fdnum, &fd)) < 0  // 解析 fd
		||  (r = dev_lookup(fd->fd_dev_id, &dev)) < 0) {  // 查找设备
		return r;  // 出错直接返回
	}
	// writef("in user/fd.c : fd->fd_dev_id is %d\n", fd->fd_dev_id);
	r = (*dev->dev_close)(fd);  // 调用设备特定的关闭操作
	fd_close(fd);  // 解除映射 fd 页
	// writef("close va is %x\n", (void *)fd);
	return r;  // 返回设备关闭的结果
}

void
close_all(void)  // 关闭所有可能打开的 fd
{
	int i;  // 下标

	for (i = 0; i < MAXFD; i++) {
		close(i);  // 忽略错误，尽力关闭
	}
}

int
dup(int oldfdnum, int newfdnum)  // 将 oldfd 的映射复制到 newfd（含数据区）
{
	int i, r;  // 计数与返回码
	u_int ova, nva, pte;  // 原/新数据区基址与临时页表项
	struct Fd *oldfd, *newfd;  // 原/新 fd 页

	if ((r = fd_lookup(oldfdnum, &oldfd)) < 0) {  // 解析旧 fd
		return r;
	}

	close(newfdnum);  // 先关闭可能存在的目标 fd
	newfd = (struct Fd *)INDEX2FD(newfdnum);  // 计算新 fd 页地址
	ova = fd2data(oldfd);  // 原数据区基址
	nva = fd2data(newfd);  // 新数据区基址

	// 若原数据区所在的页目录项有效，则尝试映射整个 PDMAP 范围
	if ((* vpd)[PDX(ova)]) {
		for (i = 0; i < PDMAP; i += BY2PG) {  // 按页遍历
			pte = (* vpt)[VPN(ova + i)];  // 读取页表项

			if (pte & PTE_V) {  // 仅复制有效页
				// pd 已分配，不应出错；映射到新数据区对应位置
				if ((r = syscall_mem_map(0, ova + i, 0, nva + i,
										 pte & (PTE_V | PTE_R | PTE_LIBRARY))) < 0) {
					goto err;  // 失败则回滚
				}
			}
		}
	}

	// 最后映射 fd 页本身
	if ((r = syscall_mem_map(0, (u_int)oldfd, 0, (u_int)newfd,
							 ((*vpt)[VPN(oldfd)]) & (PTE_V | PTE_R | PTE_LIBRARY))) < 0) {
		goto err;
	}

	return newfdnum;  // 返回新 fd 号

err:
	syscall_mem_unmap(0, (u_int)newfd);  // 解除新 fd 映射

	for (i = 0; i < PDMAP; i += BY2PG) {  // 解除已映射的数据页
		syscall_mem_unmap(0, nva + i);
	}

	return r;  // 传播错误码
}

int
read(int fdnum, void *buf, u_int n)
{
	int r;
	struct Dev *dev;
	struct Fd *fd;
	char * temp;

	// 步骤 1：解析 fd 并找到对应设备
	r = fd_lookup(fdnum, &fd);
	if (r < 0) {
		return r;
	}
	r = dev_lookup(fd->fd_dev_id, &dev);
	if (r < 0) {
		return r;
	}
	// 步骤 2：检查打开模式是否允许读
	if ((fd->fd_omode & O_ACCMODE) == O_WRONLY) {
		writef("[%08x] read %d -- bad mode\n", env->env_id, fdnum);
		return -E_INVAL;
	}
	// 步骤 3：从当前偏移处读取数据
	r = (*dev->dev_read)(fd, buf, n, fd->fd_offset);
	// 步骤 4：更新偏移，并在缓冲区末尾添加字符串终止符
	if (r > 0) {
		fd->fd_offset += r;
		temp = (char *)buf;
		*(temp + r) = '\0';
	}
	// writef("finish read\n");  // 调试输出
	return r;
}

int
readn(int fdnum, void *buf, u_int n)
{
	int m, tot;

	for (tot = 0; tot < n; tot += m) {
		m = read(fdnum, (char *)buf + tot, n - tot);

		if (m < 0) {
			return m;
		}

		if (m == 0) {
			break;  // 遇到 EOF，提前退出循环
		}
	}

	return tot;
}

int
write(int fdnum, const void *buf, u_int n)
{
	int r;
	struct Dev *dev;
	struct Fd *fd;

	if ((r = fd_lookup(fdnum, &fd)) < 0
		||  (r = dev_lookup(fd->fd_dev_id, &dev)) < 0) {
		return r;
	}

	if ((fd->fd_omode & O_ACCMODE) == O_RDONLY) {  // 只读则拒绝写
		writef("[%08x] write %d -- bad mode\n", env->env_id, fdnum);
		return -E_INVAL;
	}

	if (debug) writef("write %d %p %d via dev %s\n",
						  fdnum, buf, n, dev->dev_name);

	r = (*dev->dev_write)(fd, buf, n, fd->fd_offset);

	if (r > 0) {  // 写入成功则推进偏移
		fd->fd_offset += r;
	}

	return r;
}

int
seek(int fdnum, u_int offset)
{
	int r;
	struct Fd *fd;

	if ((r = fd_lookup(fdnum, &fd)) < 0) {
		return r;
	}

	fd->fd_offset = offset;  // 直接设置新偏移
	return 0;
}


int fstat(int fdnum, struct Stat *stat)  // 获取 fd 对应对象的状态信息
{
	int r;
	struct Dev *dev;
	struct Fd *fd;

	if ((r = fd_lookup(fdnum, &fd)) < 0
		||  (r = dev_lookup(fd->fd_dev_id, &dev)) < 0) {
		return r;
	}

	stat->st_name[0] = 0;  // 默认清空名称
	stat->st_size = 0;     // 默认大小为 0
	stat->st_isdir = 0;    // 默认非目录
	stat->st_dev = dev;    // 记录设备指针
	return (*dev->dev_stat)(fd, stat);
}

int
stat(const char *path, struct Stat *stat)  // 通过打开临时 fd 获取路径状态
{
	int fd, r;

	if ((fd = open(path, O_RDONLY)) < 0) {
		return fd;
	}

	r = fstat(fd, stat);
	close(fd);
	return r;
}
