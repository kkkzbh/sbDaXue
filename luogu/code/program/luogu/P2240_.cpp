


#include<iostream>
#include<array>

constexpr int size = 1e5 + 10;

bool solve(const std::array<int,size>& a,int len,int k,int n)
{
    int cnt{};
    for(int i = 1; i <= n;++i) cnt += a[i] / len;
    return cnt >= k;
}

int main()
{
    int n,k; std::cin >> n >> k;
    std::array<int,size> a{};
    for(int i = 1; i <= n;++i) std::cin >> a[i];
    int l = 1,r = 1e8 + 1;
    while(l != r)
    {
        int mid = (l + r) >> 1;
        if(solve(a,mid,k,n)) l = mid + 1;
        else r = mid;
    }
    std::cout << l - 1;

    return 0;
}