

#include<iostream>
#include<array>

using ll = long long;

constexpr int size = 1e5 + 10;

std::array<int,size> a;

inline int MAX(int a,int b)
{
    return a > b ? a : b;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    for(int i = 1; i <= n;++i)
    {
        std::cin >> a[i];
    }
    ll max = 0;
    ll ans = 0;
    for(int i = 1; i <= n;++i)
    {
        max += a[i];
        ans = MAX(ans,max);
        max = MAX(0,max);
    }
    std::cout << ans;

    return 0;
}