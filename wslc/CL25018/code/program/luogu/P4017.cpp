

#include<iostream>
#include<array>
#include<vector>
#include<utility>
#include<queue>

constexpr int M_size{ 5000 + 2 };
constexpr std::size_t mod{ 80112002 };

int n,m;
std::array<std::vector<int>,M_size> a;
std::array<std::size_t,M_size> cnt;
std::array<int,M_size> id;

void top_sort(int i)
{
    std::queue<int> que;
    que.push(i);
    cnt[i] = 1;
    while(!que.empty())
    {
        int v  = que.front();
        for(auto&& it : a[v])
        {
            cnt[it] += cnt[v];
            cnt[it] %= mod;
            if(!--id[it])
                que.push(it);
        }
        que.pop();
    }
}

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    std::cin >> n >> m;
    for(int i{ 1 }; i <= m; ++i)
    {
        int x,y;
        std::cin >> x >> y;
        a[x].push_back(y);
        ++id[y];
    }

    for(int i{ 1 }; i <= n; ++i)
    {
        if(!id[i])
        {
            a[0].push_back(i);
            ++id[i];
        }
    }
    top_sort(0);
    std::size_t ans{};
    for(int i{ 1 }; i <= n; ++i)
    {
        if(a[i].empty())
        {
            ans += cnt[i];
            ans %= mod;
        }
    }
    std::cout << ans;

    return 0;
}