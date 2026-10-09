


#include<iostream>
#include<string>
#include<array>
#include<unordered_set>

constexpr int M_size{ 10000 + 2 };

std::string str;
std::string delete_str;
std::array<char,M_size> a;
size_t t;
std::unordered_set<char> set;

inline bool isdelete(char c)
{
    return (set.find(c) != set.end());
}

int main()
{
    freopen("../in.in","r",stdin);
    freopen("../out.out","w",stdout);
    std::getline(std::cin,str);
    std::getline(std::cin,delete_str);
    for(auto&& i : delete_str)
    {
        set.insert(i);
    }
    for(auto&& i : str)
    {
        if(!isdelete(i))
            a[t++] = i;
    }
    for(int i{}; i != t;++i)
        std::cout << a[i];

    return 0;
}