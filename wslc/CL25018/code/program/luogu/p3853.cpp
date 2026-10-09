


#include<iostream>
#include<array>

constexpr int size = 1e5 + 10;

bool solve(int len,int k,const std::array<int,size>& a,int n)
{
    int cnt{};
    for(int i = 2; i <= n;++i) cnt += (a[i] - a[i - 1] - 1) / len;
    return cnt <= k;
}

int main()
{
    int len,n,k; std::cin >> len >> n >> k;
    std::array<int,size> a;
    for(int i = 1; i <= n;++i) std::cin >> a[i];
    int l = 1,r = 1e8 + 1;
    while(l != r)
    {
        int mid = (l + r) >> 1;
        if(solve(mid,k,a,n)) r = mid;
        else l = mid + 1;
    }
    std::cout << l;

    return 0;
}