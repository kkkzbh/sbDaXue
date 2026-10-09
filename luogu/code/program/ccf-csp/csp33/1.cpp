


#include<iostream>
#include<array>
#include<bitset>

constexpr static int N{ 500 + 2 };

int n,m;
std::array<int,N> ct,ct2;
std::bitset<N> vis;

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> n >> m;
    for(int i{ 1 }; i <= n; ++i)
    {
        int cnt;
        std::cin >> cnt;
        while(cnt--)
        {
            int val;
            std::cin >> val;
            ++ct[val];
            if(!vis[val])
            {
                vis.set(val);
                ++ct2[val];
            }
        }
        vis.reset();
    }
    for(int i{ 1 }; i <= m; ++i)
    {
        std::cout << ct2[i] << ' ' << ct[i] << '\n';
    }

    return 0;
}