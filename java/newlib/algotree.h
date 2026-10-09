#pragma once

#include"basic_binary_tree.h"

template<typename C,typename M_node>
constexpr C*& cast(M_node*& ptr) noexcept
{
    return reinterpret_cast<C*&>(ptr);
}

template<typename C,typename M_node>
constexpr const C*& cast(const M_node*& ptr) noexcept
{
    return reinterpret_cast<const C*&>(ptr);
}

template<typename T>
void swap(T& a,T& b)
{
    T c = std::move(a);
    a = b;
    b = c;
}
