


#include<iostream>
#include<array>
#include<algorithm>

using ll = long long;
constexpr int size = 1e5 + 10;

int main()
{
    int m,n; std::cin >> m >> n;
    std::array<int,size> school{};
    std::array<int,size> stu{};
    for(int i = 1; i <= m;++i) std::cin >> school[i];
    school[m + 1] = 1e9;
    school[0] = -school[m + 1];
    for(int i = 1; i <= n;++i) std::cin >> stu[i];
    std::sort(school.begin() + 1,school.begin() + 1 + m);
    std::sort(stu.begin() + 1,stu.begin() + 1 + n);
    ll sum{};
    for(int i = 1,top = 1; i <= n;++i)
    {
        while(school[top] < stu[i]) ++top;
        sum += std::min(school[top] - stu[i],stu[i] - school[top - 1]);
    }
    std::cout << sum;

    return 0;
}