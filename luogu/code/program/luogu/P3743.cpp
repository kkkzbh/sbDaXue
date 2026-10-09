


#include<iostream>
#include<array>
#include<algorithm>

constexpr int size = 1e5 + 10;
constexpr double eps = 1e-4;
constexpr double floor = 1e10;

#if 0

本题需要探讨floor的范围 由于题目的特殊性 连续充电 + 切换不费时间
理论上来讲 就可以看成是 可以同时给所有机子充电并处理所有机子耗电(以微分的角度去理解)
如果是这样的话 如果 p 大于等于所有机子的耗电 那么就是-1
也就是说 只要有解  每秒至少消耗1的能量(由充电和总充电决定) 而初始状态可以有1e5台机子 1e5台能量 总能量1e10
则可以得到上界应该就为floor = 1e10; 这里定义的还是比较极限的
还是需要一个个的处理每台机子以取得最大的持续时间 只是不需要考虑充电冲突

#endif

bool solve(double m,int p,const std::array<double,size>& a,const std::array<double,size> &b,int n)
{
    double cnt{};
    for(int i = 1; i <= n;++i) cnt += std::max((a[i] * m - b[i]) / p,0.0);
    return cnt <= m;
}

int main()
{
    int n,p; std::cin >> n >> p;
    std::array<double,size> a,b;
    for(int i = 1; i <= n;++i) std::cin >> a[i] >> b[i];
    double l = 0,r = floor;
    while(r - l >= eps)
    {
        double mid = (l + r) / 2;
        if(solve(mid,p,a,b,n)) l = mid;
        else r = mid;
    }
    std::cout << (l >= floor - 1 ? -1 : l);

    return 0;
}