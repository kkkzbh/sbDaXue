#ifndef _ERROR_H_ // 头文件防重包含开始
#define _ERROR_H_ // 定义本头文件的防重包含宏

#define E_UNSPECIFIED 1 // 未指定或未知错误
#define E_BAD_ENV     2 // 目标环境不存在或不可用于该操作

#define E_INVAL       3 // 参数无效
#define E_NO_MEM      4 // 内存不足（分配失败）
#define E_NO_FREE_ENV 5 // 超出可创建环境（进程）数量上限

#define E_IPC_NOT_RECV 6 // 目标环境当前未处于接收 IPC 的状态

#define E_NO_DISK     7 // 磁盘空间不足
#define E_MAX_OPEN    8 // 打开的文件数量已达上限
#define E_NOT_FOUND   9 // 未找到文件或数据块
#define E_BAD_PATH   10 // 路径无效
#define E_FILE_EXISTS 11 // 文件已存在
#define E_NOT_EXEC   12 // 不是合法的可执行文件

#define MAXERROR 12 // 错误码最大值（当前为 12）

#endif // 结束防重包含
