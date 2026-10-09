

#include<iostream>
#include<format>
#include<array>
#include<algorithm>
#include<ranges>
#include<iterator>

#define fun auto
#define print(...) std::cout << std::format(__VA_ARGS__)

constexpr static int N1{ 1000 + 2 };

std::array<std::array<int,N1>,N1> a;
int n;

fun fdp() -> void
{
    for(int i{ n }; i; --i)
    {
        for(int j{ 1 }; j <= i; ++j)
        {
            a[i][j] += std::max(a[i + 1][j],a[i + 1][j + 1]);
        }
    }
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> n;
    for(int i{ 1 }; i <= n; ++i)
    {
        std::copy_n(std::istream_iterator<int>{ std::cin },i,a[i].begin() + 1);
    }
    fdp();
    print("{:d}",a[1][1]);

    return 0;
}