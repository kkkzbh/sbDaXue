


#include<iostream>
#include<array>
#include<algorithm>

constexpr int size = 1e5 + 10;

bool isok(const std::array<int,size>& a,int k,int n,int N) //k 要求距离 // n 奶牛个数 //N 棚子个数
{
    int count = 1;
    int dis = 0;
    for(int i = 2; i <= N && count != n;++i)
    {
        dis += a[i] - a[i - 1];
        if(dis >= k) ++count,dis = 0;
    }
    return count == n;
}

int main()
{
    int n,c; std::cin >> n >> c;
    std::array<int,size> a{};
    for(int i = 1; i <= n;++i) std::cin >> a[i];
    std::sort(a.begin() + 1,a.begin() + 1 + n);
    int l = 0;
    int r = 1e9;
    while(l != r)
    {
        int mid = (l + r) >> 1;
        if(isok(a,mid,c,n)) l = mid + 1;
        else r = mid;
    }
    std::cout << l - 1;

    return 0;
}