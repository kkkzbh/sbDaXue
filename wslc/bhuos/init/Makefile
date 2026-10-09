INCLUDES := -I../include              # 头文件搜索路径：指向上级目录的 include 目录

%.o: %.c                               # 规则：将同名 .c 编译为 .o 目标文件
	$(CC) $(CFLAGS) $(INCLUDES) -c $<   # 使用编译器与通用选项进行编译，$< 表示第一个依赖文件

.PHONY: clean                          # 声明伪目标，避免与同名文件冲突

all: init.o main.o code.o              # 默认目标：构建本目录核心目标文件

clean:                                 # 清理构建产物
	rm -rf *~ *.o                        # 移除编辑器临时文件与目标文件


include ../include.mk                  # 引入上级目录的通用编译参数与规则
