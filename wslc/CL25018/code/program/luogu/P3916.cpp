

#include<iostream>
#include<array>
#include<vector>
#include<algorithm>

constexpr int M_size{ 100000 + 2 };

std::array<std::vector<int>,M_size> a;
std::array<int,M_size> ans;

void dfs(int i,const int max)
{
    ans[i] = max;
    for(auto&& it : a[i])
    {
        if(!ans[it])
        {
            dfs(it,max);
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    int n,m;
    std::cin >> n >> m;
    for(int i{ 1 }; i <= m; ++i)
    {
        int x,y;
        std::cin >> x >> y;
        a[y].push_back(x);
    }
    for(int i{ n }; i >= 1; --i)
    {
        if(!ans[i])
            dfs(i,i);
    }
    for(int i{ 1 }; i <= n; ++i)
        std::cout << ans[i] << ' ';

    return 0;
}