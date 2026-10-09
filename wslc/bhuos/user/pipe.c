#include "lib.h"  // 运行库与系统调用封装
#include <mmu.h>  // 虚拟内存宏
#include <env.h>  // 环境结构
#define debug 0  // 调试开关

static int pipeclose(struct Fd*);
static int piperead(struct Fd *fd, void *buf, u_int n, u_int offset);
static int pipestat(struct Fd*, struct Stat*);
static int pipewrite(struct Fd *fd, const void *buf, u_int n, u_int offset);

struct Dev devpipe =
{
.dev_id=	'p',        // 设备 ID：管道
.dev_name=	"pipe",   // 设备名称
.dev_read=	piperead,  // 读实现
.dev_write=	pipewrite,// 写实现
.dev_close=	pipeclose,// 关闭实现
.dev_stat=	pipestat,  // 状态查询
};

#define BY2PIPE 32		// 管道缓冲区大小（较小以便暴露竞争条件）

struct Pipe {
	u_int p_rpos;		// 读位置
	u_int p_wpos;		// 写位置
	u_char p_buf[BY2PIPE];	// 数据缓冲区（环形）
};

int
pipe(int pfd[2])  // 创建匿名管道，返回读写两个 fd
{
	int r, va;
	struct Fd *fd0, *fd1;

	// 分配两个 fd 页并建立映射
	if ((r = fd_alloc(&fd0)) < 0
	||  (r = syscall_mem_alloc(0, (u_int)fd0, PTE_V|PTE_R|PTE_LIBRARY)) < 0)
		goto err;

	if ((r = fd_alloc(&fd1)) < 0
	||  (r = syscall_mem_alloc(0, (u_int)fd1, PTE_V|PTE_R|PTE_LIBRARY)) < 0)
		goto err1;

	// 将 Pipe 结构作为数据区第一页，并在两个 fd 上共享映射
	va = fd2data(fd0);
	if ((r = syscall_mem_alloc(0, va, PTE_V|PTE_R|PTE_LIBRARY)) < 0)
		goto err2;
	if ((r = syscall_mem_map(0, va, 0, fd2data(fd1), PTE_V|PTE_R|PTE_LIBRARY)) < 0)
		goto err3;

	// 初始化 fd 结构体（读/写端）
	fd0->fd_dev_id = devpipe.dev_id;
	fd0->fd_omode = O_RDONLY;

	fd1->fd_dev_id = devpipe.dev_id;
	fd1->fd_omode = O_WRONLY;

	writef("[%08x] pipecreate \n", env->env_id, (* vpt)[VPN(va)]);

	pfd[0] = fd2num(fd0);
	pfd[1] = fd2num(fd1);
	return 0;

err3:	syscall_mem_unmap(0, va);
err2:	syscall_mem_unmap(0, (u_int)fd1);
err1:	syscall_mem_unmap(0, (u_int)fd0);
err:	return r;
}

static int
_pipeisclosed(struct Fd *fd, struct Pipe *p)
{
	// 思路：比较 pageref(fd) 与 pageref(p)。若相等，说明仅剩本端类型，另一端已关闭。
	int pfd,pfp,runs;
	do {	
		runs = env->env_runs;
		pfd = pageref((void *) fd);
		pfp = pageref((void *) p);
//writef("in _pipeisclosed : pfd = %d, pfp = %d\n", pfd, pfp);
	} while (runs != env->env_runs);
	
	if (pfd == pfp) {
		return 1;
	}
	return 0;

	user_panic("_pipeisclosed not implemented");
//	return 0;
}

int
pipeisclosed(int fdnum)
{
	struct Fd *fd;
	struct Pipe *p;
	int r;

	if ((r = fd_lookup(fdnum, &fd)) < 0)
		return r;
	p = (struct Pipe*)fd2data(fd);
	return _pipeisclosed(fd, p);
}

static int
piperead(struct Fd *fd, void *vbuf, u_int n, u_int offset)
{
	// 逐字节读取；若缓冲区为空且尚未读取任何数据，则让出 CPU；
	// 若对端关闭且未读取到数据则返回 0；使用 _pipeisclosed 判断是否关闭。
	int i;
	struct Pipe *p;
	char *rbuf;

    /* 步骤 1：根据 fd 获取管道指针，vbuf 为读取缓冲区 */
        p = (struct Pipe *)fd2data(fd);
//writef("in piperead, n is %d, pfd = %d, pfp = %d, pipe va = %x, fd va = %x\n", n, pageref(fd), pageref(p), p, fd);
        rbuf = vbuf;

        if (_pipeisclosed(fd, p)) {
		//writef("end piperead, i is %d\n", 0);
                return 0;
        }           

    /* 步骤 2：当读指针追上写指针时，若尚未读取任何数据则让出 CPU */
        for (i = 0; i < n; i++) {
                while (p->p_rpos >= p->p_wpos) {
			//writef("piperead p->p_rpos = %d, p->p_wpos = %d\n", p->p_rpos, p->p_wpos);
                        if (_pipeisclosed(fd, p)) {
				//writef("end piperead, i is %d\n", i);
                                return i;
                        }           
                        syscall_yield();
                }          
		 
    /* 步骤 3：从环形缓冲区拷贝一个字节到 rbuf */
                rbuf[i] = p->p_buf[p->p_wpos % BY2PIPE];
//		writef("read from pipe : %c\n", rbuf[i]);
                p->p_rpos++;
        }           
	//writef("end piperead, i is %d\n", i);
        return i;
	
	user_panic("piperead not implemented");
//	return -E_INVAL;
}

static int
pipewrite(struct Fd *fd, const void *vbuf, u_int n, u_int offset)
{
	// 逐字节写入；必须写满 n 字节。若缓冲区满则等待清空后继续；
	// 若缓冲区满且对端关闭，返回 0；使用 _pipeisclosed 判断是否关闭。
	int i;
	struct Pipe *p;
	char *wbuf;
    /* 步骤 1：根据 fd 获取管道指针，vbuf 为写入缓冲区 */
        p = (struct Pipe *)fd2data(fd);
//writef("in pipewrite, n is %d, pfd = %d, pfp = %d, pipe va = %x, fd va = %x\n", n, pageref(fd), pageref(p), p, fd);
        wbuf = vbuf;

        if (_pipeisclosed(fd, p)) {
                return 0;
        }
    /* 步骤 2：当写入与读取的差值达到 BY2PIPE（满）时，让出 CPU 等待 */
        for (i = 0; i < n; i++) {
              	while (p->p_wpos - p->p_rpos >= BY2PIPE ) {
			//writef("pipewrite p->p_rpos = %d, p->p_wpos = %d\n", p->p_rpos, p->p_wpos);
                        if (_pipeisclosed(fd, p)) {
				//writef("end pipewrite, i is %d\n", i);
                                return i;
                        }
                        syscall_yield();
                }
    /* 步骤 3：写入一个字节到环形缓冲区 */
//		writef("write in pipe : %c\n", wbuf[i]);
                p->p_buf[p->p_wpos % BY2PIPE] = wbuf[i];
                p->p_wpos++;
	//	writef("%c", wbuf[i]);
        }

	//writef("end piperead, i is %d\n", i);
        return n;
//	return -E_INVAL;
	user_panic("pipewrite not implemented");
}

static int
pipestat(struct Fd *fd, struct Stat *stat)
{
	struct Pipe *p;

	p = (struct Pipe *)fd2data(fd);
        strcpy(stat->st_name, "<pipe>");   // 名称占位
        stat->st_size = p->p_wpos - p->p_rpos;  // 当前可读字节数
        stat->st_isdir = 0;  // 非目录
        stat->st_dev = &devpipe;  // 关联设备
        return 0;	
}

static int
pipeclose(struct Fd *fd)
{
	syscall_mem_unmap(0, fd);          // 解绑 fd 页
	syscall_mem_unmap(0, fd2data(fd)); // 解绑共享数据页
	return 0;
}
