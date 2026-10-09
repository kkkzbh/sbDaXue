

#ifdef P1223

#include<iostream>
#include<array>
#include<algorithm>
#include<iomanip>
constexpr int size = 1000 + 10;

int main()
{
    int n;
    std::cin >> n;
    std::array<int,size> arr{};
    for(int i = 1; i <= n;++i)
    {
        std::cin >> arr[i];
    }
    std::array<int,size> point{};
    for(int i = 1; i <=n ;++i)
    {
        point[i] = i;
    }
    std::sort(point.begin() + 1,point.begin() + 1 + n,[&arr](const int& i1,const int& i2) -> bool
    {
        return arr[i1] < arr[i2];
    });
    double sum = 0;
    for(int i = 1; i <= n;++i)
    {
        std::cout << point[i] << ' ';
    }
    std::cout << '\n';
    int a = 0;
    for(int i = 1; i< n;++i)
    {
        a += arr[point[i]];
        sum += a;
    }
    std::cout << std::fixed << std::setprecision(2) << sum/n;


    return 0;
}

#endif
