#include <stdio.h> // 引入标准输入输出库
#include <stdlib.h> // 引入标准库（提供内存分配等函数）

extern int readelf(u_char* binary, int size); // 声明 ELF 解析函数，参数为内存首地址与大小

// 从命令行读取 ELF 文件并调用 readelf 解析
int main(int argc,char *argv[]) // 程序入口，argc/argv 为命令行参数
{ // 函数体开始
        FILE* fp; // 文件指针
        int fsize; // 文件大小（字节）
        unsigned char *p; // 缓冲区指针（保存文件内容）

        if(argc < 2) // 参数个数不足，未给出文件名
        {
                printf("Please input the filename.\n"); // 提示用户输入文件名
                return 0; // 结束程序
        }
        if((fp = fopen(argv[1],"rb"))==NULL) // 以二进制只读方式打开文件
        {
                printf("File not found\n"); // 打印“未找到文件”
                return 0; // 结束程序
        }
        fseek(fp,0L,SEEK_END); // 文件指针移动到末尾
        fsize = ftell(fp); // 取得文件大小
        p = (u_char *)malloc(fsize+1); // 申请缓冲区，多 1 字节用于结尾的 0
        if(p == NULL) // 内存分配失败
        {
                fclose(fp); // 关闭文件
                return 0; // 结束程序
        }
        fseek(fp,0L,SEEK_SET); // 回到文件开头
        fread(p,fsize,1,fp); // 读取整个文件到内存
        p[fsize] = 0; // 在末尾补 0，便于安全处理

	readelf(p,fsize); // 调用 ELF 解析函数
        return 0; // 正常结束
} // 函数体结束
