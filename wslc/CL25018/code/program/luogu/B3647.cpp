
#include<iostream>
#include<format>
#include<array>
#include<iterator>
#include<ranges>
#include<algorithm>
constexpr static int N{ 100 + 2 };

std::array<std::array<int,N>,N> a;
int n,m;

void floyd()
{
    for(int k{ 1 }; k <= n; ++k)
    {
        for(int i{ 1 }; i <= n; ++i)
        {
            if(a[i][k] == std::numeric_limits<int>::max() >> 2) continue;
            for(int j{ 1 }; j <= n; ++j)
            {
                a[i][j] = std::min(a[i][j],a[i][k] + a[k][j]);
                if(i == j) a[i][j] = 0;
            }
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::ranges::for_each(a,[](auto& v){ std::ranges::fill(v,std::numeric_limits<int>::max() >> 2); });
    std::cin >> n >> m;
    for(int i{ 1 },u,v,w; i <= m; ++i)
    {
        std::cin >> u >> v >> w;
        a[u][v] = a[v][u] = std::min(a[u][v],w);
    }
    floyd();
    for(int i{ 1 }; i <= n; ++i)
    {
        std::ranges::copy_n(a[i].begin() + 1,n,std::ostream_iterator<int>{ std::cout," " });
        std::cout << '\n';
    }

    return 0;
}