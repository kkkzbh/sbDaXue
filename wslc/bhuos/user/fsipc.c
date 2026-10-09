#include "lib.h"  // 运行库与 IPC 封装
#include <fs.h>    // 文件系统请求/响应结构
#include <env.h>   // 环境结构与数组 envs

#define debug 0  // 调试开关

extern u_char fsipcbuf[BY2PG];		// 页对齐缓冲区（在 entry.S 中定义）

// 功能概述：
// 向文件服务器发送一次 IPC 请求并等待应答。
// 参数：
//   type  —— 请求类型，作为 IPC 的整数值发送；
//   fsreq —— 携带请求数据的页，通常为 fsipcbuf（服务器也可能在上面写回响应信息）；
//   dstva —— 若期望接收一页映射，则为接收地址；否则为 0；
//   perm  —— 返回接收页的权限（可为 NULL）。
// 返回：成功 0；失败为负错误码。
static int
fsipc(u_int type, void *fsreq, u_int dstva, u_int *perm)
{
	u_int whom;  // 实际服务者的 envid（由回复提供）
	// 约定：文件系统服务进程为 envs[1]
	ipc_send(envs[1].env_id, type, (u_int)fsreq, PTE_V | PTE_R);  // 发送请求页
	return ipc_recv(&whom, dstva, perm);  // 等待回复与可选映射页
}

// 功能：向文件服务器发送“打开文件”请求（包含路径与打开模式），
// 成功时服务器在 fd 页中写入必要的元信息。
int
fsipc_open(const char *path, u_int omode, struct Fd *fd)
{
	u_int perm;
	struct Fsreq_open *req;

	req = (struct Fsreq_open *)fsipcbuf;

	// 路径过长则报错
	if (strlen(path) >= MAXPATHLEN) {
		return -E_BAD_PATH;
	}

	strcpy((char *)req->req_path, path);
	req->req_omode = omode;
	return fsipc(FSREQ_OPEN, req, (u_int)fd, &perm);
}

// 功能：向文件服务器申请将文件中从 offset 开始的块映射为一页，
// 服务器将返回包含该块的页映射到 dstva。
int
fsipc_map(u_int fileid, u_int offset, u_int dstva)
{
	int r;
	u_int perm;
	struct Fsreq_map *req;

	req = (struct Fsreq_map *)fsipcbuf;
	req->req_fileid = fileid;
	req->req_offset = offset;

	if ((r = fsipc(FSREQ_MAP, req, dstva, &perm)) < 0) {
		return r;
	}

	if ((perm & ~(PTE_R | PTE_LIBRARY)) != (PTE_V)) {  // 校验页权限
		user_panic("fsipc_map: unexpected permissions %08x for dstva %08x", perm,
				   dstva);
	}

	return 0;
}

// 功能：请求设置文件大小为 size 字节
int
fsipc_set_size(u_int fileid, u_int size)
{
	struct Fsreq_set_size *req;

	req = (struct Fsreq_set_size *)fsipcbuf;
	req->req_fileid = fileid;
	req->req_size = size;
	return fsipc(FSREQ_SET_SIZE, req, 0, 0);
}

// 功能：请求关闭文件（fileid 随后失效）
int
fsipc_close(u_int fileid)
{
	struct Fsreq_close *req;

	req = (struct Fsreq_close *)fsipcbuf;
	req->req_fileid = fileid;
	return fsipc(FSREQ_CLOSE, req, 0, 0);
}

// 功能：请求将文件中指定偏移的块标记为脏（便于回写）
int
fsipc_dirty(u_int fileid, u_int offset)
{
	struct Fsreq_dirty *req;

	req = (struct Fsreq_dirty *)fsipcbuf;
	req->req_fileid = fileid;
	req->req_offset = offset;
	return fsipc(FSREQ_DIRTY, req, 0, 0);
}

// 功能：请求删除给定路径的文件/目录
int
fsipc_remove(const char *path)
{
	struct Fsreq_remove *req;
	// 步骤 1：校验路径长度
	if (strlen(path) >= MAXPATHLEN) {
		return -E_BAD_PATH;
	}
	req = (struct Fsreq_remove *)fsipcbuf;
	strcpy((char *)req->req_path, path);

	// 步骤 2：通过 IPC 发送删除请求
	return fsipc(FSREQ_REMOVE, req, 0, 0);
}

// 功能：请求文件服务器将缓存中的脏块同步到磁盘
int
fsipc_sync(void)
{
	return fsipc(FSREQ_SYNC, fsipcbuf, 0, 0);
}
