

#include<iostream>
#include<string>
#include<array>
#include<algorithm>
#include<vector>
#include<bitset>

constexpr int M_size{ 1000 + 2 };

std::array<std::string,M_size> a;
std::array<std::string*,M_size> M_a;

std::array<std::vector<int>,M_size> ver;
std::bitset<M_size> vis;

std::string ans;


int main()  //存完图后 根本没法有一个确定的路径和起点终点 肯定是不能暴力dfs的
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    int n;
    std::cin >> n;
    for(int i{ 1 }; i <= n; ++i)
        std::cin >> a[i];
    std::sort(a.begin() + 1,a.begin() + 1 + n);
    for(int i{ 1 }; i <= n; ++i)
        M_a[i] = &a[i];
    std::sort(M_a.begin() + 1,M_a.begin() + 1 + n,
              [](const std::string*const s1,const std::string*const s2) -> auto
              {
                  if(s1->back() == s2->back())
                      return s1 < s2;
                  return s1->back() < s2->back();
              });
    for(int i{ 1 },M_it{ 1 },M_last{ 1 }; i <= n && M_last <= n ; ++i)
    {
        if(M_a[i]->back() == a[M_last].front())
            M_it = M_last;

        //Just two situation. One is the new word has not changed.Another is change.
        while(M_it <= n && M_a[i]->back() != a[M_it].front())
            ++M_it;
        M_last = M_it;
        while(M_it <= n && M_a[i]->back() == a[M_it].front())
            ver[M_a[i] - &a[0]].push_back(M_it++);
    }

    for(int i{ 1 }; i <= n; ++i)
    {
        int it{ i };
        int cnt{};
        std::array<int,M_size> dis;
        vis.reset();
        while(true)
        {
            vis.set(it);
            dis[cnt++] = it;
            for(auto&& val : ver[it])
            {
                if(!vis[val])
                {
                    it = val;
                    break;
                }
            }
            if(cnt != n)
                break;
            for(int j{}; j != n; ++j)
                ans += a[dis[j]];
        }
    }

    return 0;
}