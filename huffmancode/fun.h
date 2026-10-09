#pragma once

#include"huftree.h"
#include<string_view>
#include"statistics.h"
#include"hufio.h"

/* ***************************************   /*

    fun.h 基于哈夫曼编码 实现压缩与解压
    fun.cpp 中 也就只有这两个函数  这个默认实参 其实是无用的
    不过由于是最基础的解压函数 所以内部实现 可能已经有些复杂了(被改动较多)

    为什么用std::string_view 作参数 而不是std::string？ 当然 const char* 只适用于C语言 故这里不予考虑
    string_view 对于 const char* 而言 具有更高效的传递效率,因为其不需要拷贝一份std::string,而是只有两个指针拷贝的代价
    string_view 也能高效接受 std::string 的传参
    也就是说 在这个场景下 string_view 是最优解

 /* **************************************   */

auto compress(const std::string_view file,const std::string_view output = "out") -> bool;

auto depress(const std::string_view file,const std::string_view output = "de.txt") -> bool;