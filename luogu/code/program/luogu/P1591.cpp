

#ifdef P1591

#include<iostream>
#include<array>
#include<algorithm>

constexpr int size = 10 * 1 + 100 * 2 + 1000 * 3 + 10 + 1;
int sz = 1;

auto& operator*(std::array<int,size>& a,const int& x)
{
    for(int i = 1; i <= sz + 4;++i)
    {
        a[i] *= x;
    }
    for(int i = 1; i <= sz + 3;++i)
    {
        a[i+1] += a[i] / 10;
        a[i] %= 10;
    }
    int i;
    for(i = sz + 4;a[i] == 0;--i);
    sz = i;
    return a;
}

inline auto& operator*=(std::array<int,size>& a,const int& x)
{
    return a = a * x;
}

int print(std::array<int,size>& a,int ma)
{
    int p = sz;
    int cnt = 0;
    while(p > 1 && a[p] == 0) --p;
    for(;p >=1 ; --p)
    {
        if(a[p] == ma) ++cnt;
    }
    return cnt;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    std::array<int,size> a{};
    int t = 0;
    std::cin >> t;
    int n;
    int ma;
    a[1] = 1;
    for(int i = 1; i <= t; ++i)
    {
        std::cin >> n >> ma;
        for(int j = 2; j <= n;++j)
        {
            a *= j;
        }
        std::cout << print(a,ma) << '\n';
        std::fill(a.begin() + 2,a.begin() + sz + 1,0);
        a[1] = 1;
        sz = 1;
    }

    return 0;
}

#endif
