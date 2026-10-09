

#include<iostream>
#include<array>
#include<utility>
#include<algorithm>
#include<cmath>
#include<format>
#include<cstring>

constexpr int _pow(int i,int power)
{
    int mod = i;
    for(int _{1}; _ != power;++_) i *= mod;
    return i;
}

constexpr int size = 15 + 10;
constexpr int dp_size = _pow(2,16) + 10;
double null;

int n;
std::array<std::pair<double,double>,size> a;
std::array<std::pair<double,double>*,size> ptr;
double dis;
int dp_;
std::array<std::array<double,dp_size>,size> dp;
double ans = 1e100;

inline double distance(const std::pair<double,double>& p1,const std::pair<double,double>& p2)
{
#define dx (p1.first - p2.first)
#define dy (p1.second - p2.second)
    return std::sqrt(dx * dx + dy * dy);
}

double dfs(const std::pair<double,double>& pos,int i)
{
    if(i == n + 1)
    {
        ans = std::min(ans,dis);
        return ans;
    }
    for(int _ = i; _ <= n;++_)
    {
        if(dp[ptr[_] - &a[1]][dp_] != null) continue;
        double s = distance(pos,*ptr[_]);
        dis += s;
        std::swap(ptr[i],ptr[_]);
        dp_ += 1 << ptr[i] - &a[1];
        if(dis < ans) dp[ptr[i] - &a[1]][dp_] = dfs(*ptr[i],i + 1);
        dis -= s;
        dp_ -= 1 << ptr[i] - &a[1];
        std::swap(ptr[i],ptr[_]);
    }
    return ans;
}

int main()
{
    std::cin >> n;
    for(int i = 1; i <= n;++i) std::cin >> a[i].first >> a[i].second;
    for(int i = 1; i <= n;++i) ptr[i] = &a[i];
    memset(dp.begin(),127,sizeof(dp));
    null = dp[0][0];
    std::cout << std::format("{:.2f}",dfs(a[0],1));

    return 0;
}
