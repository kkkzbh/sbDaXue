


#include<iostream>
#include<queue>
#include<array>
#include<algorithm>
#include<iterator>

using int64 = long long;
using uint64 = unsigned long long;

constexpr int N{ 100'000 + 2 };

int k;
std::array<uint64, N> a;
int n;

int main()
{
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
    std::cin >> n >> k;
    std::copy_n(std::istream_iterator<int>{ std::cin }, n, a.begin() + 1);


    return 0;
}