

#include"utility.h"
#include"print.h"
#include"fun.h"
#include"menu.h"
#include"rle.h"
#include"lz77.h"
#include"deflate.h"

/* ************ /*

 从main.cpp 开始
 关于程序的注释 ------> 中文的都是我后期加上去的  英文的为非后期加上去的 是当写当补的注释
 init语句用于更改终端的编码方式 防止中文乱码

/* ************ */

auto init{ []
{
    system("chcp 65001");
    return 0;
}()};

// 程序从类menu 的构造函数开始 类menu的定义 位于 menu.h 中

menu m;

int main()
{

    return 0;
}