


#include<iostream>
#include<array>

using ll = long long;
constexpr int size = 1e5 + 10;

bool solve(ll len,int m,const std::array<int,size> &a,int n)
{
    int cnt{};
    ll sum{};
    for(int i = 1; i <= n;++i)
    {
        if(a[i] > len) i = n + 1,cnt = m + 1;
        else if(sum + a[i] > len) sum = a[i],++cnt;
        else sum += a[i];
    }
    return cnt < m;
}

int main()
{
    int n,m; std::cin >> n >> m;
    std::array<int,size> a;
    for(int i = 1; i <= n;++i) std::cin >> a[i];
    ll l = 0,r = 1e16 + 1;
    while(l != r)
    {
        ll mid = (l + r) >> 1;
        if(solve(mid,m,a,n)) r = mid;
        else l = mid + 1;
    }
    std::cout << l;

    return 0;
}