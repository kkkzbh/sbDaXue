#pragma once

#include<iostream>
#include<random>
#include<string>
#include<ctime>

std::default_random_engine M_e(time(0));

std::string make_string()
{
    constexpr size_t default_len{ 15 };
    static std::uniform_int_distribution M_int(32,126);
    std::string tmp;
    for(size_t i{}; i != default_len;++i)
    {
        tmp.push_back(static_cast<char>(M_int(M_e)));
    }
    return tmp;
}

std::string make_string(size_t len)
{
    static std::uniform_int_distribution M_int(32,126);
    std::string tmp;
    for(size_t i{}; i != len;++i)
    {
        tmp.push_back(static_cast<char>(M_int(M_e)));
    }
    return tmp;
}
