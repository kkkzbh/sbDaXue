# Main makefile                               # 启动阶段（boot/）的主 Makefile
#                                             # 只添加中文注释，不改动任何规则语义
# Copyright (C) 2007 Beihang University       # 版权信息
# Written by Zhu Like ( zlike@cse.buaa.edu.cn ) # 作者信息
#

# ========= Configuration =========           # 配置区域：定义编译所需变量

INCLUDES	  := -I../include/               # 头文件包含路径，供预处理器查找

# ======== End of configuration ===           # 配置区域结束

%.o: %.S                                      # 规则：将同名 .S 汇编为 .o
	$(CC) $(CFLAGS) $(INCLUDES) -c $<           # 调用编译器预处理+汇编，生成目标文件

.PHONY: clean                                 # 声明伪目标：不与文件同名关联

all: start.o                                  # 默认目标：构建启动对象文件 start.o

clean:                                        # 清理临时与产物文件
	rm -rf *~ *.o                               # 删除编辑器备份和编译生成的 .o

include ../include.mk                         # 包含上层公共编译选项与工具链设置
