


#include<iostream>
#include<map>

int cnt;
int c,m,n;
std::map<int,int> map;

template<typename T>
void dfs(T& it)
{
    bool l{},r{};
    T last,back;
    if(it != map.begin())
    {
        last = --it;
        ++it;
        ++last->second;
        l = true;
    }
    if(++it != map.end())
    {
        back = it;
        --it;
        ++back->second;
        r = true;
    }
    else
    {
        --it;
    }
    map.erase(it);
    --cnt;
    if(l and last->second >= 5)
    {
        dfs(last);
    }
    else if(r and back->second >= 5)
    {
        dfs(back);
    }
}

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> c >> m >> n;
    for(int i{ 1 }; i <= m; ++i)
    {
        int x,w;
        std::cin >> x >> w;
        map.emplace(x,w);
    }
    cnt = m;
    for(int i{ 1 }; i <= n; ++i)
    {
        int p;
        std::cin >> p;
        auto it{ map.find(p) };
        if(++it->second == 5)
        {
            dfs(it);
        }
        std::cout << cnt << '\n';
    }

    return 0;
}