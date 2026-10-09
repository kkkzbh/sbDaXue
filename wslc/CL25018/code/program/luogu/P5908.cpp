

#include<iostream>
#include<vector>
#include<array>
#include<queue>
#include<bitset>

constexpr static int N{ 100000 + 2 };

std::array<std::vector<int>,N> a;
int n,d;
std::bitset<N> vis;

int bfs(int start)
{
    std::queue<int> que;
    que.emplace(start);
    vis.set(start);
    int ret{};
    int cnt{ d };
    while(!que.empty() and cnt--)
    {
        for(std::size_t i{},cei{ que.size() }; i != cei; ++i)
        {
            auto val{ que.front() };
            que.pop();
            for(const auto it : a[val])
            {
                if(!vis[it])
                {
                    que.emplace(it);
                    vis.set(it);
                    ++ret;
                }
            }
        }
    }
    return ret;
}

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> n >> d;
    for(int i{}; i != n; ++i)
    {
        int x,y;
        std::cin >> x >> y;
        a[x].emplace_back(y);
        a[y].emplace_back(x);
    }
    std::cout << bfs(1);


    return 0;
}