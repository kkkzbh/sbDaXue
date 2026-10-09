#pragma once

#include"utility.h"
#include<string_view>
#include"map.h"

/* ******************************* /*

    word_frequency: 服务于哈夫曼编码算法
    给定一个file的path路径 返回其一个词频表

    tuple_frequncry: 服务于lz77编码算法
    同上 返回一个tuole表 基于map实现 详见map.h

/* ****************************** */

auto word_frequency(const std::string_view path) -> std::array<uint64,ch_size>;

auto tuple_frequency(const std::string_view path) -> map<tuple,uint>;