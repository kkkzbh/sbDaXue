


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
    while(l !=  r)
    {
        ll sum = 0;
        int mid = l + (r - l) / 2 + 1;
        for(int i = 1; i <= n;++i) sum += std::max(0,a[i] - mid);
        if(sum < m) r = mid - 1;
        else l = mid;
    }
    std::cout << l;

    return 0;
}