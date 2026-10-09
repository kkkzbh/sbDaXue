

                //性价比的除法计算 应使用double存储计算比较
#ifdef P2240

#include<iostream>
#include<algorithm>
#include<array>
#include<iomanip>

constexpr int size = 100 + 10;

struct coin
{
    double weigh = 0;
    double price = 0;
};


int main()
{
    std::array<coin,size> a{};
    int N;
    double T;
    std::cin >> N >> T;
    for(double i = 1;i<=N;++i)
    {
        std::cin >> a[i].weigh >> a[i].price;
    }
    std::sort(a.begin() + 1,a.begin() + 1 + N,[](const coin& c1,const coin& c2) -> bool
    {
        return c1.price/c1.weigh > c2.price/c2.weigh;
    });
    double sum = 0;
    for(double i = 1; i <= N;++i)
    {
        if(T > a[i].weigh)
        {
            T -= a[i].weigh;
            sum += a[i].price;
        }
        else
        {
            sum += a[i].price / a[i].weigh * T;
            break;
        }
    }
    std::cout  << std::fixed << std::setprecision(2) << static_cast<double>(sum);

    return 0;
}

#endif
