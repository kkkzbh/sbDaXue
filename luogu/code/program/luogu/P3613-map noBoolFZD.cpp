



#include<iostream>
#include<unordered_map>
#include<functional>
#include<utility>

namespace std
{
    template<>
    struct hash<std::pair<int,int>>
    {
        size_t operator() (const std::pair<int,int>& p) const noexcept
        {return hash<int>()(p.first) ^ ((hash<int>()(p.second) << 1));}
    };
}

std::unordered_map<std::pair<int,int>,int> map;

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr),std::cout.tie(nullptr);
    int n,q; std::cin >> n >> q;
    int c,i,j,v;
    while(q--)
    {
        if(std::cin >> c >> i >> j;c == 1)
        {
            std::cin >> v;
            if(v) map.emplace(std::make_pair(i,j),v);
            else map.erase(map.find({i,j}));
        }
        else
        {
            std::cout << map[{i,j}] << '\n';
        }
    }
    return 0;
}