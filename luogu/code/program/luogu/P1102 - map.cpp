

#include<iostream>
#include<unordered_map>

auto F_re = []() -> auto
{
    freopen("../in.in","r",stdin);
    freopen("../out.out","w",stdout);
    return 0;
}();

int n,c;
std::unordered_map<int,size_t> map;

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0),std::cout.tie(0);
    std::cin >> n >> c;
    while(n--)
    {
        int v;
        std::cin >> v;
        auto i = map.emplace(v,1ull);
        if(!i.second)
        {
            ++i.first->second;
        }
    }
    size_t ans{};   //枚举 A 求 B = A - C  枚举B 求 A = B + C
    for(auto&& i : map)
    {
        auto it = map.find(i.first + c);
        if(it != map.end())
        {
            ans += i.second * it->second;
        }
    }
    std::cout << ans;

    return 0;
}