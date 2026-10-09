


#include<iostream>
#include<string>
#include<string_view>
#include<array>
#include<cctype>
#include<algorithm>

constexpr int M_size{ 10000 + 2 };


std::array<size_t,M_size> a;
size_t t;

size_t ctoi(const char c)
{
    if(isdigit(c))
        return (c ^ 48) + 1;
    else if(islower(c))
        return 10 + (c ^ 96);
    else
        return 36 + (c ^ 64);
}

size_t hash(const std::string_view s)
{
    constexpr static size_t M_prime{ 521 };
    size_t val{};
    for(auto&& c : s)
    {
        val *= M_prime;
        val += ctoi(c);
    }
    return val;
}

int main()
{
    freopen("../in.in","r",stdin);
    freopen("../out.out","w",stdout);
    std::ios::sync_with_stdio(0),std::cin.tie(0),std::cout.tie(0);
    int n;
    std::cin >> n;
    for(int i{}; i != n;++i)
    {
        std::string s;
        std::cin >> s;
        a[t++] = hash(s);
    }
    std::sort(a.begin(),a.begin() + t);
    int ans{ 1 };
    for(int i{ 1 }; i != t;++i)
    {
        if(a[i] != a[i - 1])
            ++ans;
    }
    std::cout << ans;

    return 0;
}