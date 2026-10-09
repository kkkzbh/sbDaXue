#pragma once

#include<iostream>
#include<array>

template<typename Val>
struct Tarray
{
    using int64 = long long;
    constexpr static int M_size{ 500000 + 2 };

    std::array<Val,M_size> a{};
    int M_n;

    Tarray() = default;
    explicit Tarray(int sz) : M_n(sz){}
    void set(int sz)
    {
        M_n = sz;
    }

    void add(int i,Val val)
    {
        while(i <= M_n)
        {
            a[i] += val;
            i += i & -i;
        }
    }

    int64 query(int l,int r)
    {
        return query(r) - query(l - 1);
    }

private:

    int64 query(int i)
    {
        int64 ret{};
        while(i)
        {
            ret += a[i];
            i -= i & -i;
        }
        return ret;
    }

};