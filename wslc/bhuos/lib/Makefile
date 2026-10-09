INCLUDES := -I./ -I../ -I../include/ # 中文注释：头文件搜索路径
%.o: %.c # 中文注释：C 源文件到目标文件的规则
	$(CC) $(CFLAGS) $(INCLUDES) -c $< # 中文注释：编译为 .o，不链接

%.o: %.S # 中文注释：汇编源码到目标文件的规则
	$(CC) $(CFLAGS) $(INCLUDES) -c $< # 中文注释：预处理+编译汇编

.PHONY: clean # 中文注释：声明伪目标

all: kernel_elfloader.o env.o print.o printf.o sched.o env_asm.o kclock.o traps.o genex.o kclock_asm.o syscall.o syscall_all.o getc.o # 中文注释：本目录默认构建的目标集合

clean: # 中文注释：清理编译产物
	rm -rf *~ *.o # 中文注释：移除临时与目标文件


include ../include.mk # 中文注释：包含上级通用编译配置
