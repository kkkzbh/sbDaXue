

#include<iostream>
#include<array>
#include<algorithm>

constexpr int M_size{ 10000 + 2 };

std::array<int,M_size> dist;

int main()
{
    int n;
    std::cin >> n;
    int ans{};
    for(int i{ 1 }; i <= n; ++i)
    {
        int x,y;
        std::cin >> x >> y;
        int d{},c;
        while(std::cin >> c && c)
            d = std::max(d,dist[c]);
        dist[x] = d + y;
        ans = std::max(ans,dist[x]);
    }
    std::cout << ans;

    return 0;
}