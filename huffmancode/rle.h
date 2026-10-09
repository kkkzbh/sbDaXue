



#ifndef RLE_H
#define RLE_H

#include<string_view>
#include"utility.h"

/* ********************* /*

    rle太过于简单 不再给出过多注释
    简要说明一下实现:
    找重复值 若找到 n个重复值x 则存入 n x
    如果没有重复值 找连续的不重复值 直到n个后 出现重复的 则写入 n x1 x2 x3 ..... xn
    这里对于非重复值 避免了大量的 1字节 -> 2字节 的操作 算是一个小优化
    但怎么说呢 感觉这个按单值找重复的rle很弱鸡, 或许我只是没接触他的适用领域

/* ********************* */


constexpr static uint8 tag{ 1 << 7 };

auto rle_compress(const std::string_view file,const std::string_view output = "../out.nt") -> bool;

auto rle_depress(const std::string_view file,const std::string_view output = "../de.znt") -> bool;

#endif //RLE_H
