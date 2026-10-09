

#include<iostream>
#include<string>
#include<unordered_map>
#include<utility>

std::unordered_map<std::string,std::string> map;

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    std::string fa;
    std::string tmp;
    char c;
    while(std::cin >> c)
    {
        if(c == '$')
            break;
        std::cin >> tmp;
        if(c == '#')
            fa = std::move(tmp);
        else if(c != '?')
        {
            map.emplace(tmp,fa);
        }
        else
        {
            std::cout << tmp << ' ';
            decltype(map.begin()) it;
            const std::string* sit = &tmp;
            while((it = map.find(*sit)) != map.end())
                sit = &it->second;
            std::cout << *sit << '\n';
        }
    }

    return 0;
}