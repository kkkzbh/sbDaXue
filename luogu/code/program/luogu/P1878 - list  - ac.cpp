


#include<iostream>
#include<vector>
#include<algorithm>
#include<ranges>
#include<array>
#include<queue>
#include<utility>
#include<cmath>

#define val(p) \
    std::abs(l.a[p.first].a - l.a[p.second].a)

constexpr int N{ 200000 + 2 };

struct list
{

    constexpr static int null{ -1 };

    struct node
    {
        int id;
        char c; //复用
        int a;
        int next{ null };
        int last{ null };
    };

    std::array<node,N> a;
    int root{ null };
    int n;

    void del(int l,int r)
    {
        a[a[l].last].next = a[r].next;
        a[a[r].next].last = a[l].last;
        a[l].c = a[r].c = 0;
    }

    void make()
    {
        std::cin >> n;
        std::ranges::for_each(a | std::views::take(n),[](node& val){ std::cin >> val.c; });
        std::ranges::for_each(a | std::views::take(n),[](node& val){ std::cin >> val.a; });
        root = 0;
        for(int i{}; i != n; ++i)
        {
            a[i].id = i + 1;
            a[i].next = i + 1;
            a[i].last = i - 1;
        }
        a[n - 1].next = null;
    }
};

list l;

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    l.make();
    std::vector<std::pair<int,int>> vec;
    for(int i{},cei{ l.n - 1 }; i != cei; ++i)
    {
        if(l.a[i].c != l.a[i + 1].c)
            vec.emplace_back(i, i + 1);
    }
    auto cmp{ [](const auto p1,const auto p2)
              {
                  int val{ val(p1) - val(p2) };
                  if(!val)
                      return p1.first > p2.first;
                  return val > 0;
              }};
    std::priority_queue<std::pair<int,int>,
            std::vector<std::pair<int,int>>,decltype(cmp)> que{ cmp,std::move(vec) };
    int k{};
    std::vector<std::pair<int,int>> ans;
    while(!que.empty())
    {
        auto p{ que.top() };
        que.pop();
        if(l.a[p.first].c and l.a[p.second].c)
        {
            ++k;
            ans.emplace_back(l.a[p.first].id,l.a[p.second].id);
            if(l.a[l.a[p.first].last].c != l.a[l.a[p.second].next].c)
                que.emplace(l.a[p.first].last,l.a[p.second].next);
            l.del(p.first,p.second);
        }
    }
    std::cout << k << '\n';
    for(const auto p : ans)
        std::cout << p.first << ' ' << p.second << '\n';


    return 0;
}