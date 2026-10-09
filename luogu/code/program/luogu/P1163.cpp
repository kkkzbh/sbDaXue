

#include<iostream>
#include<format>
#include<array>
constexpr int size = 4000 + 10;

constexpr double eps = 1e-4;

bool solve(int w,int m,double k,std::array<double,size>& a)
{
    for(int i = 1; i <= m;++i) a[i] = (1 + k) * a[i - 1] - w;
    return a[m] > eps;
}

int main()
{
    int w0,w,m; std::cin >> w0 >> w >> m;
    std::array<double,size> a;
    a[0] = w0;
    double l = 0.0,r = 3.0;
    while(r - l >= eps)
    {
        double mid = (l + r) / 2;
        if(solve(w,m,mid,a)) r = mid;
        else l = mid;
    }
    std::cout << std::format("{:.1f}",l * 100.0);

    return 0;
}