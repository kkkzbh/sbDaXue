// 在两个进程间“乒乓”传递计数器；只需启动一个进程，它会通过 fork 分裂为两个。

#include "lib.h"  // 进程与 IPC 接口

void
umain(void)  // 主函数：父子进程通过 IPC 互相传递递增的整数
{
	u_int who, i;

	if ((who = fork()) != 0) {  // 父进程路径
		// 先把“球”发给子进程
		writef("\n@@@@@send 0 from %x to %x\n", syscall_getenvid(), who);
		ipc_send(who, 0, 0, 0);
		// user_panic("&&&&&&&&&&&&&&&&&&&&&&&&m");
	}

	for (;;) {
		writef("%x am waiting.....\n",syscall_getenvid());  // 等待接球
		i = ipc_recv(&who, 0, 0);
		
		writef("%x got %d from %x\n", syscall_getenvid(), i, who);  // 打印收到的值
	
		//user_panic("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&");
		if (i == 10)  // 传满 10 次结束
			return;
		i++;
		writef("\n@@@@@send 0 from %x to %x\n", syscall_getenvid(), who);
		ipc_send(who, i, 0, 0);
		if (i == 10)
			return;
	}
		
}
