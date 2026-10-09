


#include<iostream>
#include<array>
#include<bitset>

constexpr int C_size{ 100 + 2 };
constexpr int M_size{ 1000 + 2 };
constexpr int V_size{ 10000 + 2};
constexpr int null{ -1 };

std::array<int,M_size> a;
std::array<int,V_size> next;
std::array<int,V_size> to;
int top;
std::array<int,M_size> cnt;
std::bitset<M_size> vis;
int k,n,m;
std::array<int,C_size> pos;

auto Pre = []() -> auto
{
    a.fill(null);
    return 0;
}();

void push(int x,int y)
{
    to[top] = y;
    next[top] = a[x];
    a[x] = top++;
}

void dfs(int i)
{
    vis.set(i);
    ++cnt[i];
    for(int it{ a[i] }; it != null; it = next[it])
    {
        if(!vis[to[it]])
            dfs(to[it]);
    }
}

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    std::cin >> k >> n >> m;
    for(int i{ 1 }; i <= k; ++i)
        std::cin >> pos[i];
    for(int i{ 1 }; i <= m; ++i)
    {
        int x,y;
        std::cin >> x >> y;
        push(x,y);
    }
    for(int i{ 1 }; i <= k; ++i)
    {
        vis.reset();
        dfs(pos[i]);
    }
    int ans{};
    for(int i{ 1 }; i <= n; ++i)
    {
        if(cnt[i] == k)
            ++ans;
    }
    std::cout << ans;

    return 0;
}