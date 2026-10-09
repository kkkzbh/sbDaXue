#ifndef _FS_H_ // 头文件防重包含开始
#define _FS_H_ 1 // 定义本头文件的防重包含宏

#include <types.h> // 基础类型

#define BY2BLK    BY2PG          // 磁盘块大小（与页大小相同）
#define BIT2BLK   (BY2BLK * 8)   // 位图中 1 个块可表示的位数

#define MAXNAMELEN  128  // 文件名最大长度
#define MAXPATHLEN  1024 // 路径最大长度

#define NDIRECT   10           // 直接块数量
#define NINDIRECT (BY2BLK/4)   // 一级间接块可索引的块数
#define MAXFILESIZE (NINDIRECT * BY2BLK) // 最大文件大小（仅用一级间接）

#define BY2FILE 256 // 目录项大小（按 256B 对齐）

struct File {                      // 简化的文件元数据
    u_char f_name[MAXNAMELEN];     // 文件名（不含路径）
    u_int  f_size;                 // 文件长度（字节）
    u_int  f_type;                 // 类型：文件/目录
    u_int  f_direct[NDIRECT];      // 直接块索引
    u_int  f_indirect;             // 一级间接块索引

    struct File* f_dir;            // 所在目录（父结点）
    u_char f_pad[256 - MAXNAMELEN - 4 - 4 - NDIRECT*4 - 4 - 4]; // 填充到 BY2FILE
}; // 结构体结束

#define FILE2BLK (BY2BLK/sizeof(struct File)) // 一块中能存放的目录项数量

#define FTYPE_REG 0 // 普通文件
#define FTYPE_DIR 1 // 目录

#define FS_MAGIC 0x68286097 // 文件系统魔数

struct Super {           // 超级块（文件系统元信息）
    u_int s_magic;       // 魔数（用于识别）
    u_int s_nblocks;     // 数据区总块数
    struct File s_root;  // 根目录描述
}; // 结构体结束

// 文件系统请求类型（IPC）
#define FSREQ_OPEN     1 // 打开文件
#define FSREQ_MAP      2 // 将文件页映射到进程
#define FSREQ_SET_SIZE 3 // 调整文件大小
#define FSREQ_CLOSE    4 // 关闭文件
#define FSREQ_DIRTY    5 // 标记脏页
#define FSREQ_REMOVE   6 // 删除文件
#define FSREQ_SYNC     7 // 刷回磁盘

struct Fsreq_open {               // 打开请求
    char req_path[MAXPATHLEN];    // 路径
    u_int req_omode;              // 打开模式
};

struct Fsreq_map {                // 映射请求
    int  req_fileid;              // 文件句柄
    u_int req_offset;             // 文件内偏移
};

struct Fsreq_set_size {           // 改大小请求
    int  req_fileid;              // 文件句柄
    u_int req_size;               // 新尺寸
};

struct Fsreq_close {              // 关闭请求
    int req_fileid;               // 文件句柄
};

struct Fsreq_dirty {              // 脏页请求
    int  req_fileid;              // 文件句柄
    u_int req_offset;             // 页内偏移
};

struct Fsreq_remove {             // 删除请求
    u_char req_path[MAXPATHLEN];  // 路径
};

#endif // 结束防重包含
