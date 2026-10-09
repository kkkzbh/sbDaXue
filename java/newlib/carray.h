//
// Created by k on 24-8-4.
//

#ifndef JAVA_CARRAY_H

#include<ranges>

template<typename T,int MOD_>
struct carray
{
    auto begin() noexcept
    {
        return std::ranges::begin(a);
    }

    auto end() noexcept
    {
        return std::ranges::end(a);
    }

    auto operator[](int i) noexcept
    {
        return a[i % MOD_];
    }

    T a[MOD_]{};
};



#define JAVA_CARRAY_H

#endif //JAVA_CARRAY_H
