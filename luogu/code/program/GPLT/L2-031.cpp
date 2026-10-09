



#include<iostream>
#include<vector>
#include<array>
#include<algorithm>
#include<queue>
#include<bitset>

constexpr static int N{ 100000 + 2  };

std::array<std::vector<int>,N> a;
std::bitset<N> bit;
int n;
std::array<int,N> tab;

int ans,level;
void bfs(int start)
{
    std::queue<int> que;
    que.push(start);
    bit.set(start);
    int l{ 1 };
    while(!que.empty())
    {
        for(int cei{ static_cast<int>(que.size())}; cei; --cei)
        {
            int i{que.front()};
            que.pop();
            for (const auto it: a[i])
            {
                if (!bit[it])
                {
                    bit.set(it);
                    if(l > tab[it])
                    {
                        que.push(it);
                        tab[it] = l;
                    }
                }
            }
        }
        ++l;
    }
    if(l > level)
    {
        level = l;
        ans = start;
    }
}

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> n;
    std::vector<int> end;
    for(int i{ 1 },k; i <= n; ++i)
    {
        std::cin >> k;
        if(!k)
            end.push_back(i);
        while(k--)
        {
            int val;
            std::cin >> val;
            a[val].push_back(i);
        }
    }
    for(const auto it : end)
    {
        bfs(it);
        bit.reset();
    }
    std::cout << ans;

    return 0;
}