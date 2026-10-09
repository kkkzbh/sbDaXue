

#include<iostream>
#include<array>
#include<algorithm>

using ll = long long;

constexpr int size = 1e6 + 10;

std::array<int,size> a;

int main()
{
    int n,m; std::cin >> n >> m;
    for(int i = 1; i <= n;++i) std::cin >> a[i];
    int l = 0;
    int r = 4e5;
    ll sum = 0;
    while(l != r)
    {
        int mid = (l + r) >> 1;
        sum = 0;
        for (int i = 1; i <= n; ++i) sum += std::max(0, a[i] - mid);
        if (sum <= m) r = mid;
        else l = mid + 1;
    }
    sum = 0;
    for(int i = 1; i <= n;++i) sum += std::max(0,a[i] - l);
    if(sum == m) std::cout << l;
    else std::cout << l - 1;

    return 0;
}