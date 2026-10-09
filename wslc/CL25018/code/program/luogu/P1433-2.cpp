

#include<iostream>
#include<array>
#include<utility>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<format>

constexpr int dp_size()
{
    return (1 << 15) + 10;
}

constexpr int size = 15 + 10;

std::array<std::array<double,dp_size()>,size> dp{};

inline double distance(const std::pair<double,double> &p1,const std::pair<double,double> &p2)
{
#define dx (p1.first - p2.first)
#define dy (p1.second - p2.second)
    return std::sqrt(dx * dx + dy * dy);
}

int main()
{
    int n; std::cin >> n;
    std::array<std::pair<double,double>,size> point;
    std::array<std::array<double,size>,size> dis{};
    for(int i = 1; i <= n;++i) std::cin >> point[i].first >> point[i].second;
    for(int i = 0; i <= n;++i) for(int j = i + 1; j <= n;++j) dis[i][j] = distance(point[i],point[j]),dis[j][i] = dis[i][j];
    memset(dp.begin(),127,sizeof(dp));
    for(int i = 1; i <= n;++i) dp[i][1 << (i - 1)] = dis[0][i];
    for(int i = 1,end = 1 << n;i != end;++i)  //枚举状态 从低状态 -> 高状态
        for(int j = 1; j <= n;++j)       //for every destination.
            if(1 << (j - 1) & i)
                for(int k = 1; k <= n;++k)  //start
                    if(k != j && 1 << (k - 1) & i)
                        dp[j][i] = std::min(dp[k][i - (1 << (j - 1))] + dis[k][j],dp[j][i]);
    int ed = (1 << n) - 1;
    double min{dp[0][0]};
    for(int i = 1; i <= n;++i) min = std::min(min,dp[i][ed]);
    std::cout << std::format("{:.2f}",min);

    return 0;
}