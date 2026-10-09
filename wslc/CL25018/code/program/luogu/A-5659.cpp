
#include<iostream>
#include<vector>
#include<ranges>
#include<algorithm>
#include<functional>

using namespace std::views;

struct graph
{

    explicit graph(int n) : a(n,std::vector<int>{}) {}

    auto operator[](int i) -> auto&
    { return a[i]; }

    auto del(int x,int y)
    {
        a[x].erase(std::find(a[x].begin(),a[x].end(),y));
        a[y].erase(std::find(a[y].begin(),a[y].end(),x));
    }

    auto emplace(int x,int y)
    {
        a[x].push_back(y);
        a[y].push_back(x);
    }

    std::vector<std::vector<int>> a;
};

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while(t--) {
        std::invoke([] {
            int n;
            std::cin >> n;
            auto v = std::vector(n,0);
            std::ranges::for_each(v,[](auto& i) { std::cin >> i,--i; });
            auto id = std::vector(n,0);
            for(auto i : iota(0,n)) {
                id[v[i]] = i;
            }
            auto a = graph{ n };
            for(auto i : iota(0,n - 1)) {
                int x,y;
                std::cin >> x >> y;
                a.emplace(x - 1,y - 1);
            }

        });
    }
}