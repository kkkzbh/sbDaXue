#pragma once


/* ***************** /*

    概念 主要用于约束map 和 priority_queue 的模板形参
    同 不在给出过多注释

/* ***************** */


#include"hash.h"

template<typename T>
concept comparable = requires(T a,T b)
{
    { a < b } -> std::convertible_to<bool>;
};

template<typename T>
concept hashable = requires(T a)
{
    { hash<T>{}(a) } -> std::convertible_to<uint64>;
};

template<typename T>
concept contain_a = requires(T tree)
{
    tree.a;
};
