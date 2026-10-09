#pragma once

#include<iostream>
#include<format>
#include<string_view>

template<typename... Args>
void print(const std::string_view fmt_str,Args&&... args)
{
    fputs(std::vformat(fmt_str,std::make_format_args(args...)).data(),stdout);
}

void print(char c)
{
    fputc(c,stdout);
}

void print(const std::string_view s)
{
    fputs(s.data(),stdout);
}

template<typename Count>
void print(Count i)
{
    std::cout << i;
}