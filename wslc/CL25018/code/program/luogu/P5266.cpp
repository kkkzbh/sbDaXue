


#include<iostream>
#include<string>
#include<unordered_map>
#include<utility>

[[maybe_unused]]
auto M_re = []() -> auto
{
    freopen("../in","r",stdin);
    freopen("../out","w",stdout);
    return 0;
}();

std::unordered_map<std::string,size_t> map;

int main()
{
    int n;
    std::cin >> n;
    while(n--)
    {
        int op;
        std::string s;
        size_t score;
        if(std::cin >> op; op == 1)
        {
            std::cin >> s >> score;
            auto i = map.emplace(s,score);
            if(!i.second)
            {
                i.first->second = score;
            }
            std::cout << "OK\n";
        }
        else if(op == 2)
        {
            std::cin >> s;
            auto i = map.find(s);
            if(i == map.end())
            {
                std::cout << "Not found\n";
            }
            else
            {
                std::cout << i->second << '\n';
            }
        }
        else if(op == 3)
        {
            std::cin >> s;
            auto i = map.find(s);
            if(i == map.end())
            {
                std::cout << "Not found\n";
            }
            else
            {
                map.erase(i);
                std::cout << "Deleted successfully\n";
            }
        }
        else
        {
            std::cout << map.size() << '\n';
        }
    }

    return 0;
}