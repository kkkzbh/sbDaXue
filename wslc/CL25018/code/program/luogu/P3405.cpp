

#include<iostream>
#include<array>
#include<string>
#include<vector>
#include<string_view>

constexpr size_t M_isprime(size_t i)
{
    for(int j{2}; j * j <= i; ++j)
        if(!(i % j))
            return false;
    return true;
}

constexpr size_t M_prime(size_t i)
{
    for(;!M_isprime(i);++i);
    return i;
}

constexpr size_t M_size{ M_prime(8 * 100000 + 2) };
constexpr size_t prime{ M_prime(666) };

size_t hash(const std::string_view str)
{
    size_t val{};
    for(auto&& i : str)
    {
        val = (val * prime + (i ^ 64)) % M_size;
    }
    return val;
}

std::array<std::vector<std::pair<std::string,std::string>>,M_size> a;

void insert(const std::string& s1,const std::string& s2,size_t h)
{
//    for(auto&& it : a[h])
//    {
//        if(it.first == s1 && it.second == s2)
//            return;
//    }
    a[h].emplace_back(s1,s2);
}


int main()
{
    freopen("../in","r",stdin);
    freopen("../out","w",stdout);
    std::string s1;
    std::string s2;
    int n;
    std::cin >> n;
    size_t ans{};
    for(int i{}; i != n;++i)
    {
        std::cin >> s1 >> s2;
        auto sub = s1.substr(0,2);
        if(sub != s2)
        {
            std::string s = sub + s2;
            auto h = hash(s);
            insert(s1, s2, h);
            for (auto &&it: a[hash(s2 + sub)])
            {
                if (it.first.substr(0,2) == s2 && it.second == sub)
                    ++ans;
            }
        }
    }
    std::cout << ans;

    return 0;
}