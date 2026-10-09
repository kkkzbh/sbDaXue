

#include<iostream>
#include<array>
#include<algorithm>
#include<numeric>

constexpr int N{ 10000 + 2 };   //本题的暴力 事先计算复杂度 可以判断 然后就是左闭右开的思想 我也是诈一想
                //但细想发现 确实啊 确实是啊 因为结尾要掉0 也就是最尾的高度是不参与计算的 如果有谁最高穿出了结尾 就会原坐标掉出他
                //然后就是一个3结尾 一个4开头  因为结尾高度计算不算 数组上的连续 使得3的时候会掉下去0 4的时候升起
                //所以左闭右开

std::array<int,N> a;

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    int x,h,y;
    int beg{ 2147483647 },end{};
    while(std::cin >> x)
    {
        std::cin >> h >> y;
        std::for_each(a.begin() + x,a.begin() + y,[h](int& v)
        {
            v = std::max(v,h);
        });
        beg = std::min(beg,x);
        end = std::max(end,y);
    }
    int sentry{ a[beg] };
    ++end;
    while(beg <= end)
    {
        std::cout << beg << ' ' << a[beg] << ' ';
        while(beg <= end && a[++beg] == sentry);
        sentry = a[beg];
    }

    return 0;
}