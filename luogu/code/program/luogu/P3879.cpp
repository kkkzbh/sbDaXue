


#include<iostream>
#include<unordered_map>
#include<vector>

std::unordered_map<std::string,std::vector<int>> map;

void push(const std::string& s,int i)
{
    auto f = map.find(s);
    if(f == map.end())
        map.emplace(s,std::vector<int>{ i });
    else
    {
        for(auto&& it : f->second)
        {
            if(it == i)
                return;
        }
        f->second.push_back(i);
    }
}

int main()
{
    int n;
    std::cin >> n;
    for(int i{ 1 }; i <= n;++i)
    {
        int l;
        std::cin >> l;
        for(int j{ 1 }; j <= l;++j)
        {
            std::string s;
            std::cin >> s;
            push(s,i);
        }
    }
    int m;
    std::cin >> m;
    for(int i{ 1 }; i <= m;++i)
    {
        std::string s;
        std::cin >> s;
        auto it = map.find(s);
        if(it != map.end())
        {
            for (auto &&val: it->second)
            {
                std::cout << val << ' ';
            }
        }
        std::cout << '\n';
    }

    return 0;
}