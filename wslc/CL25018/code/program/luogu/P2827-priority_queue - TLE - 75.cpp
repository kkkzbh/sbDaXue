


#include<iostream>
#include<array>
#include<vector>
#include<queue>
#include<algorithm>
#include<iterator>
#include<utility>

using int64 = long long;
using uint64 = unsigned long long;

constexpr int N{ 100'000 + 2 };

struct node
{
    friend bool operator<(node a,node b)
    {
        return a.len - a.del < b.len - b.del;
    }
    friend bool operator>(node a,node b)
    {
        return b < a;
    }
    friend std::istream& operator>>(std::istream& is,node& a)
    {
        return is >> a.len;
    }
    int64 len;  //会增的虚拟长度
    int del{};
};          //观察容易发现 本题的del 可以合并到len中去。。。

int n,m,q;
int u,v;
int t;

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> n >> m >> q >> u >> v >> t;
    std::vector<node> a(n);
    std::copy_n(std::istream_iterator<node>{ std::cin },n,a.begin());
    std::priority_queue<node> que{ std::less<node>{},std::move(a) };
    for(int i{ 1 }; i <= m; ++i)
    {
        node tp = que.top();
        que.pop();
        uint64 len{ tp.len - tp.del + (i - 1ull) * q };
        if(!(i % t))
            std::cout << len << ' ';    //实长 del抵消增量
        uint64 val{ len * u / v };
        que.emplace( val,i * q );
        que.emplace( len - val,i * q );
    }
    std::cout << '\n';
    for(int i{ 1 },cei{ static_cast<int>(que.size()) }; i <= cei; ++i)
    {
        node tp = que.top();
        if(!(i % t))
            std::cout << tp.len - tp.del + m * q << ' ';
        que.pop();
    }

    return 0;
}