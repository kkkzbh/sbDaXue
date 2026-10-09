

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
    int l = 1;
    int it = 1;
    int r = n;
    ll ans = 0;
    ll max = 0;
    for(int i = 1; i <= n;++i)
    {
        max += a[i];
        if(ans < max || (ans == 0 && max == 0))
        {
            l = it;
            r = i;
            ans = max;
        }
        if(max < 0)
        {
            max = 0;
            it = i + 1;
        }
    }
    std::cout << ans << ' ' << a[l] << ' ' << a[r];

    return 0;
}