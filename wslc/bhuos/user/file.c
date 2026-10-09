#include "lib.h"  // 运行库与系统调用封装
#include <fs.h>    // 文件系统协议与结构体

#define debug 0  // 调试开关

static int file_close(struct Fd *fd);  // 关闭文件并解除映射
static int file_read(struct Fd *fd, void *buf, u_int n, u_int offset);  // 从偏移读
static int file_write(struct Fd *fd, const void *buf, u_int n, u_int offset);  // 写入数据
static int file_stat(struct Fd *fd, struct Stat *stat);  // 填充状态信息

struct Dev devfile = {
	.dev_id =	'f',            // 文件设备 ID
	.dev_name =	"file",       // 设备名称
	.dev_read =	file_read,     // 读函数
	.dev_write =	file_write,   // 写函数
	.dev_close =	file_close,   // 关闭函数
	.dev_stat =	file_stat,     // 状态查询
};


int
open(const char *path, int mode)
{
	struct Fd *fd;
	struct Filefd *ffd;
	u_int size, fileid;
	int r;
	u_int va;
	u_int i;

	// 步骤 1：分配一个新的 Fd（仅返回地址，不分配物理页）
	r = fd_alloc(&fd);
	if (r < 0) {
		return r;
	}

	// 步骤 2：向文件服务器请求打开路径，填充 fd 页头部
	r = fsipc_open(path, mode, fd);
	if (r < 0) {
		writef("in open : fsipc_open fail!\n");
		return r;
	}
	ffd = (struct Filefd *)fd;

	// 步骤 3：确定文件内容映射的起始地址、大小与 fileid
	va = fd2data(fd);
	size = ffd->f_file.f_size;
	fileid = ffd->f_fileid;

	// 步骤 4：通过 IPC 请求将文件内容按页映射到本进程地址空间
	for (i = 0; i < size; i+=BY2PG) {
		r = fsipc_map(fileid, i, va + i);
		if (r < 0) {
			writef("in open : fsipc_map fail!\n");
			return r;
		}
	}
	// 步骤 5：返回 fd 数值（而非页地址）

	return fd2num(fd);	
}

int
file_close(struct Fd *fd)
{
	int r;
	struct Filefd *ffd;
	u_int va, size, fileid;
	u_int i;

	ffd = (struct Filefd *)fd;
	fileid = ffd->f_fileid;
	size = ffd->f_file.f_size;

	// 计算文件内容映射的基址
	va = fd2data(fd);

	// 通知文件服务器哪些页已变脏（供回写）
	for (i = 0; i < size; i += BY2PG) {
		fsipc_dirty(fileid, i);
	}

	// 请求服务器关闭文件句柄
	if ((r = fsipc_close(fileid)) < 0) {
		writef("cannot close the file\n");
		return r;
	}

	// 解除映射文件内容，释放内存
	if (size == 0) {
		return 0;
	}
	for (i = 0; i < size; i += BY2PG) {
		if ((r = syscall_mem_unmap(0, va + i)) < 0) {
			writef("cannont unmap the file.\n");
			return r;
		}
	}
	return 0;
}

static int
file_read(struct Fd *fd, void *buf, u_int n, u_int offset)
{
	u_int size;
	struct Filefd *f;
	f = (struct Filefd *)fd;

	// 避免越过文件末尾读取
	size = f->f_file.f_size;

	if (offset > size) {
		return 0;
	}

	if (offset + n > size) {
		n = size - offset;
	}

	user_bcopy((char *)fd2data(fd) + offset, buf, n);  // 内存映射文件，直接拷贝
	return n;
}

int
read_map(int fdnum, u_int offset, void **blk)
{
	int r;
	u_int va;
	struct Fd *fd;

	if ((r = fd_lookup(fdnum, &fd)) < 0) {
		return r;
	}

	if (fd->fd_dev_id != devfile.dev_id) {
		return -E_INVAL;
	}

	va = fd2data(fd) + offset;  // 目标虚拟地址

	if (offset >= MAXFILESIZE) {
		return -E_NO_DISK;
	}

	if (!((* vpd)[PDX(va)]&PTE_V) || !((* vpt)[VPN(va)]&PTE_V)) {  // 未映射
		return -E_NO_DISK;
	}

	*blk = (void *)va;  // 返回该页的用户虚拟地址
	return 0;
}

static int
file_write(struct Fd *fd, const void *buf, u_int n, u_int offset)
{
	int r;
	u_int tot;
	struct Filefd *f;

	f = (struct Filefd *)fd;

	// 不要超过最大文件尺寸
	tot = offset + n;

	if (tot > MAXFILESIZE) {
		return -E_NO_DISK;
	}

	// 如有需要，先扩展文件大小（触发映射）
	if (tot > f->f_file.f_size) {
		if ((r = ftruncate(fd2num(fd), tot)) < 0) {
			return r;
		}
	}

	// 写入数据到映射内存（随后由服务器落盘）
	user_bcopy(buf, (char *)fd2data(fd) + offset, n);
	return n;
}

static int
file_stat(struct Fd *fd, struct Stat *st)
{
	struct Filefd *f;

	f = (struct Filefd *)fd;

	strcpy(st->st_name, (char *)f->f_file.f_name);
	st->st_size = f->f_file.f_size;
	st->st_isdir = f->f_file.f_type == FTYPE_DIR;
	return 0;
}

int
ftruncate(int fdnum, u_int size)
{
	int i, r;
	struct Fd *fd;
	struct Filefd *f;
	u_int oldsize, va, fileid;

	if (size > MAXFILESIZE) {
		return -E_NO_DISK;
	}

	if ((r = fd_lookup(fdnum, &fd)) < 0) {
		return r;
	}

	if (fd->fd_dev_id != devfile.dev_id) {
		return -E_INVAL;
	}

	f = (struct Filefd *)fd;
	fileid = f->f_fileid;
	oldsize = f->f_file.f_size;
	f->f_file.f_size = size;

	if ((r = fsipc_set_size(fileid, size)) < 0) {
		return r;
	}

	va = fd2data(fd);

	// 若扩展文件：映射新增页
	for (i = ROUND(oldsize, BY2PG); i < ROUND(size, BY2PG); i += BY2PG) {
		if ((r = fsipc_map(fileid, i, va + i)) < 0) {
			fsipc_set_size(fileid, oldsize);
			return r;
		}
	}

	// 若截断文件：解除多余页映射
	for (i = ROUND(size, BY2PG); i < ROUND(oldsize, BY2PG); i += BY2PG)
		if ((r = syscall_mem_unmap(0, va + i)) < 0) {
			user_panic("ftruncate: syscall_mem_unmap %08x: %e", va + i, r);
		}

	return 0;
}

// 功能：删除文件或目录
int
remove(const char *path)
{
	// 直接将请求转发给文件服务器
	return fsipc_remove(path);
}

// 功能：将缓存中的脏块同步到磁盘
int
sync(void)
{
	return fsipc_sync();
}
