

#include<iostream>
#include<array>
#include<algorithm>
#include<map>
#include<unordered_map>

constexpr int N{ 100000 + 2 };

struct node
{
    int a;
    int b;
    int c;
};

std::array<int,N> a;
int n,m;
std::array<long long,N> diff;
std::array<node,N> dis;


int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    std::cin >> n >> m;
    for(int i{ 1 }; i <= m; ++i)
        std::cin >> a[i];
    for(int i{ 1 }; i != n; ++i)
        std::cin >> dis[i].a >> dis[i].b >> dis[i].c;
    for(int i{ 1 }; i != m; ++i)
    {
        int st{ std::min(a[i],a[i + 1]) };
        int ed{ std::max(a[i],a[i + 1]) };
        diff[st] += 1;
        diff[ed] -= 1;
    }
    for(int i{ 1 }; i <= n; ++i)
        diff[i] += diff[i - 1];
    std::size_t ans{};
    for(int i{ 1 }; i != n; ++i)
        ans += std::min(diff[i] * dis[i].a,diff[i] * dis[i].b + dis[i].c);
    std::cout << ans;

    return 0;
}