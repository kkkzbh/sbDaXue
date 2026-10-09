


#include<iostream>
#include<algorithm>
#include<string>
#include<array>
#include<iterator>
#include<cctype>

constexpr static int N{ 10000 + 2 };

int n,m;
std::array<std::string,N> s1,s2;

int j_cnt()
{
    int l{},r{},ret{};
    while(l != n and r != m)
    {
        if(s1[l] < s2[r])
        {
            ++l;
        }
        else if(s1[l] > s2[r])
        {
            ++r;
        }
        else
        {
            ++ret;
            ++l;
            ++r;
        }
    }
    return ret;
}

int m_cnt()
{
    int l{},r{},ret{};
    while(l != n and r != m)
    {
        if(s1[l] < s2[r])
        {
            ++l;
            ++ret;
        }
        else if(s1[l] > s2[r])
        {
            ++r;
            ++ret;
        }
        else
        {
            ++ret;
            ++l;
            ++r;
        }
    }
    return ret + (n - l) + (m - r);
}

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> n >> m;
    std::copy_n(std::istream_iterator<std::string>{ std::cin },n,s1.begin());
    std::copy_n(std::istream_iterator<std::string>{ std::cin },m,s2.begin());
    for(int i{}; i != n; ++i)
    {
        for(auto& it : s1[i])
        {
            it = std::toupper(it);
        }
    }
    for(int i{}; i != m; ++i)
    {
        for(auto& it : s2[i])
        {
            it = std::toupper(it);
        }
    }
    std::sort(s1.begin(),s1.begin() + n);
    std::sort(s2.begin(),s2.begin() + m);
    n = std::unique(s1.begin(),s1.begin() + n) - s1.begin();
    m = std::unique(s2.begin(),s2.begin() + m) - s2.begin();
    std::cout << j_cnt() << '\n' << m_cnt();

    return 0;
}