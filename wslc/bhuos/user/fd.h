#ifndef _USER_FD_H_  // 头文件保护宏开始
#define _USER_FD_H_ 1  // 定义头文件保护宏值

#include <types.h>  // 基本类型定义
#include <fs.h>     // 文件系统相关结构体

// 前置声明：用于相互引用的结构体名
struct Fd;   // 文件描述符页结构
struct Stat; // 文件状态信息
struct Dev;  // 设备抽象表项

// 设备抽象：将不同设备统一成读/写/关闭/状态/定位等操作集
struct Dev
{
	int dev_id;  // 设备类型标识（如 'f' 文件、'p' 管道 等）
	char *dev_name;  // 设备名称字符串
	int (*dev_read)(struct Fd*, void*, u_int, u_int);   // 读函数指针
	int (*dev_write)(struct Fd*, const void*, u_int, u_int);  // 写函数指针
	int (*dev_close)(struct Fd*);  // 关闭函数指针
	int (*dev_stat)(struct Fd*, struct Stat*);  // 获取状态
	int (*dev_seek)(struct Fd*, u_int);  // 调整偏移
};

// 用户态文件描述符页（每个 fd 占一页，含状态）
struct Fd
{
	u_int fd_dev_id;  // 绑定的设备类型 ID（决定操作分派）
	u_int fd_offset;  // 当前读写偏移（字节）
	u_int fd_omode;   // 打开模式（O_RDONLY 等）
};

// 通用状态结构（stat）
struct Stat
{
	char st_name[MAXNAMELEN];  // 名称（不一定以'\0'填满）
	u_int st_size;             // 大小（字节）
	u_int st_isdir;            // 是否目录（非零为目录）
	struct Dev *st_dev;        // 所属设备表项
};

// 文件设备专用 fd 扩展（包含服务器返回的 fileid 与文件元信息）
struct Filefd 
{
	struct Fd f_fd;     // 公共 fd 页头部
	u_int f_fileid;     // 文件服务器侧的标识符
	struct File f_file; // 文件元信息（名字、大小、类型）
};

// 文件描述符表工具函数声明
int fd_alloc(struct Fd **fd);  // 分配一个空闲 fd 页（仅返回地址，不分配物理页）
int fd_lookup(int fdnum, struct Fd **fd);  // 校验 fd 号并返回映射页地址
u_int fd2data(struct Fd*);  // 由 fd 计算其首个数据页虚拟地址
int fd2num(struct Fd*);  // 由 fd 页地址反推 fd 号
int dev_lookup(int dev_id, struct Dev **dev);  // 根据 dev_id 查找设备表项
int num2fd(int fd);  // 将 fd 号映射为 fd 页的虚拟地址

// 全局设备表项（由各实现文件定义）
extern struct Dev devcons;  // 控制台设备
extern struct Dev devfile;  // 文件设备
extern struct Dev devpipe;  // 管道设备


#endif  // 头文件保护宏结束
