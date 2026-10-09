

#include<iostream>
#include<array>
#include<algorithm>

constexpr int N{ 10000000 + 2 };

std::array<std::size_t,N> diff;
int n;

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    int m;
    std::cin >> n >> m;
    for(int i{ 1 },l,r,s,e; i <= m; ++i)
    {
        std::cin >> l >> r >> s >> e;
        int d{ (e - s) / (r - l) };
        diff[l] += s;
        diff[l + 1] -= s;
        diff[l + 1] += d;
        diff[r + 1] -= d;
        diff[r + 1] -= e;
        diff[r + 2] += e;
    }
    std::size_t ans{};
    std::size_t max{};
    for(int i{ 1 }; i <= m; ++i)
    {
        diff[i] += diff[i - 1];
        diff[i] += diff[i - 1];
        ans ^= diff[i];
        max = std::max(max,diff[i]);
    }
    std::cout << ans << ' ' << max;

    return 0;
}