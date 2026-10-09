

#include<iostream>
#include<queue>
#include<array>
#include<iterator>
#include<algorithm>
#include<utility>

using int64 = long long;
using uint64 = unsigned long long;

constexpr int N{ 100000 + 2 };
constexpr int IMIN{ -2147483648 };

int n,m,q;
int u,v;
int t;
std::array<int,N> a;
std::array<std::queue<int>,3> que;

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> n >> m >> q >> u >> v >> t;
    std::copy_n(std::istream_iterator<int>{ std::cin },n,a.begin());
    std::sort(a.begin(),a.begin() + n,std::greater<>());
    std::for_each_n(a.begin(),n,[](int i){ que[0].push(i); });
    for(int i{ 1 }; i <= m; ++i)
    {
        auto len{ std::max({ std::make_pair( que[0].empty() ? IMIN : que[0].front(),0 ),
                             { que[1].empty() ? IMIN : que[1].front(),1 },
                             { que[2].empty() ? IMIN : que[2].front(),2 } })};
        que[len.second].pop();
        int64 val{ len.first + (i - 1ll) * q };
        int64 l{ val * u / v };
        if(!(i % t))
            std::cout << val << ' ';    //实长与虚长的转换 因为都是虚长 每次拿出来默认转成实长...
        que[1].emplace(l - i * q);
        que[2].emplace(val - l - i * q);
    }
    std::cout << '\n';
    for(int i{ 1 }; !que[0].empty() or !que[1].empty() or !que[2].empty(); ++i)
    {
        auto len{ std::max({ std::make_pair( que[0].empty() ? IMIN : que[0].front(),0 ),
                             { que[1].empty() ? IMIN : que[1].front(),1 },
                             { que[2].empty() ? IMIN : que[2].front(),2 } })};
        que[len.second].pop();
        if(!(i % t))
            std::cout << len.first + m * q << ' ';
    }


    return 0;
}