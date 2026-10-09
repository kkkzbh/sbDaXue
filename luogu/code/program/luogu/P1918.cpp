

#include<iostream>
#include<unordered_map>

std::unordered_map<size_t,int> map;

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0),std::cout.tie(0);
    int n;
    std::cin >> n;
    for(int i{ 1 }; i <= n;++i)
    {
        size_t v;
        std::cin >> v;
        map.emplace(v,i);
    }
    int q;
    std::cin >> q;
    while(q--)
    {
        size_t cnt;
        std::cin >> cnt;
        auto i = map.find(cnt);
        if(i != map.end())
        {
            std::cout << i->second << '\n';
        }
        else
        {
            std::cout << "0\n";
        }
    }


    return 0;
}