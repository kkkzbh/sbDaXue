

#ifndef LZ77_H
#define LZ77_H


/* ************************* /*

    lz77 无需我在过多介绍
    就是硬模拟 建议直接读源码
    不过lz77是基于利用一个已有的滑动窗口 来实现对一个缓冲区进行编码
    我在此次 寻找字串所用的算法是 字符串哈希匹配算法

/* ************************* */

#include<string_view>
#include"utility.h"

constexpr static uint64 window_length{ 128 };
constexpr static uint64 buffer_length{ 512 };


auto lz_compress(const std::string_view file,const std::string_view output = "../out.nt") -> bool;

auto lz_depress(const std::string_view file,const std::string_view output = "../de.znt") -> bool;

#endif //LZ77_H
