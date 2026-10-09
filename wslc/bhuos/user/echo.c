#include "lib.h"  // 基础库与字符串/IO 接口

void
umain(int argc, char **argv)  // echo 命令：打印参数，支持 -n 禁止换行
{
    int i, nflag;  // 索引与是否换行标志

    nflag = 0;  // 默认打印换行
    if (argc > 1 && strcmp(argv[1], "-n") == 0) {  // 处理 -n 选项
        nflag = 1;  // 末尾不换行
        argc--;     // 参数左移
        argv++;
    }
    for (i = 1; i < argc; i++) {  // 逐个输出参数
        if (i > 1)
            write(1, " ", 1);  // 参数间输出空格
        write(1, argv[i], strlen(argv[i]));  // 输出参数字符串
    }
    if (!nflag)
        write(1, "\n", 1);  // 末尾按需换行
}
