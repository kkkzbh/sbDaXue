



/* ************************ /*

    utility.h
    也是本次所有文件共享的一个通用处理头文件

    其包含了一些 基本的小函数
    包含了基本大部分文件都要用到的的 C++ 标准库
    定义了一些 所有文件都要用到的类型
    #define OPTIMISE 和  #define O2 优化的定义处
    定义了一些 常用多个文件都会用到的的常量

/* ************************ */


#ifndef UTILITY_H
#define UTILITY_H

#include<iostream>
#include<vector>
#include<array>
#include<algorithm>
#include<fstream>
#include<utility>
#include<string>
#include<bitset>
#include<format>

using int64 = long long;
using uint64 = unsigned long long;
using int8 = char;
using uint8 = unsigned char;
using uint = unsigned int;
using int16 = short;
using uint16 = unsigned short;
using wchar = short;
using uwchar = unsigned short;

using tuple = std::tuple<uint16,uint16,char>;

//#define O2
#define OPTIMISE

#ifndef OPTIMISE

constexpr int ch_size{ 256 + 2 };

#else

constexpr int ch_size{ 256 + 3 };
constexpr int sum_index{ 256 + 2 };

#endif

auto constexpr up(std::size_t i) -> std::size_t
{
    return (i - 1) >> 1;
}

auto constexpr left(std::size_t i) -> std::size_t
{
    return (i << 1) + 1;
}

auto constexpr right(std::size_t i) -> std::size_t
{
    return (i << 1) +  2;
}

auto to_int(uint64 i,const std::string& data) -> int;

auto to_int(uint64 i,const char* data) -> int;


#endif