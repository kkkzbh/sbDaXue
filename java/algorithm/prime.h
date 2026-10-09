#pragma once

#include<vector>
#include<bitset>

//constexpr bool isprime(size_t p) = delete;
//{
//    if(p <= 1)
//        return false;
//    for(size_t i = 2; i * i <= p; ++i)
//    {
//        if(!(p % i))
//            return false;
//    }
//    return true;
//}

// the v storage mode can quickly travel the sequence of prime
// the a storage mode can quickly judge if a number is a prime

constexpr bool isprime(size_t p)
{
    if(p < 2)
        return false;
    for(size_t i = 2; i <= p / i ; ++i)
    {
        if(!(p % i))
            return false;
    }
    return true;
}

constexpr int nextprime(int p)
{
    int prime = p & 1 ? p + 2 : p + 1;
    while(!isprime(prime))
        prime += 2;
    return prime;
}

constexpr std::vector<int> v_linear_sieve(int left,int right)
{
    std::vector<int> v;
    for(int i{ left }; i <= right;++i)
    {
        if(isprime(i))
            v.push_back(i);
    }
    return v;
}

constexpr int M_size{ 10000 + 2 };
constexpr std::bitset<M_size> a_linear_sieve(int left,int right)
{
    std::bitset<M_size> v;
    for(int i{ left }; i <= right;++i)
        if(isprime(i))
            v.set(i);
    return v;
}

constexpr std::bitset<M_size> a_erlich_sieve(int N)
{
    std::bitset<M_size> v(3);  //利用所有数都可质分解 利用质数筛除素数
    for(int i{ 2 }; i <= N / i ;++i)
    {
        if(!v[i])
            for(int k{ i * i }; k <= N; k += i)
                v.set(k);
    }
    return v;
}

constexpr std::vector<int> v_erlich_sieve(int left,int right)
{
    std::vector<int> v;
    auto table = a_erlich_sieve(right);
    for(int i{ left }; i <= right;++i)
    {
        if(!table[i])
            v.push_back(i);
    }
    return v;
}

constexpr std::pair<std::bitset<M_size>,std::vector<int>> ola_sieve(int N)
{
    std::pair<std::bitset<M_size>,std::vector<int>> v;
    auto& bit = v.first;
    auto& vec = v.second;
    for(int i{ 2 }; i <= N; ++i)
    {
        if(!bit[i])
            vec.push_back(i);
        for(int j{}; i * vec[j] <= N; ++j)
        {
            bit.set(i * vec[j]);
            if(i % vec[j] == 0)
                break;
        }
    }
    return v;
}