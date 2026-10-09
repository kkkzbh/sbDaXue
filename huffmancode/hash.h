#pragma once

#include"utility.h"
#include<string_view>

constexpr static uint64 prime{ 521ull };

template<typename T>
struct hash;

template<>
struct hash<std::string>
{
    auto operator()(const std::string_view str) const -> uint64
    {
        uint64 ret{};
        for(const auto c : str)
        {
            ret *= prime;
            ret += c;
        }
        return ret;
    }
};

template<>
struct hash<tuple>
{
    auto operator()(const tuple tuple) const -> uint64
    {
        return std::get<0>(tuple) * prime * prime + std::get<1>(tuple) * prime + std::get<2>(tuple);
    }
};