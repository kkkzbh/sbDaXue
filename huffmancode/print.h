#pragma once

/* ******************** /*

    非核心 主要用于模拟实现 C++23的std::print
    不再给出过多注释

/* ******************** */


#include<iostream>
#include<format>
#include<string_view>

template<typename... Args>
auto print(const std::string_view fmt_str,Args&&... args) -> void
{
    fputs(std::vformat(fmt_str,std::make_format_args(args...)).data(),stdout);
}

template<typename Value>
auto print(Value&& i) -> void
{
    print("{}",i);
}

template<typename... Args>
auto println(const std::string_view fmt_str,Args&&... args) -> void
{
    fputs(std::vformat(fmt_str,std::make_format_args(args...)).data(),stdout);
    std::cout << '\n';
}