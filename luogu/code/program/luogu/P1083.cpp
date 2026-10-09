

#include<iostream>
#include<array>
#include<algorithm>

constexpr int N{ 1000000 + 2 };

struct node
{
    int d,s,t;
};

std::array<std::size_t,N> diff;
std::array<int,N> cnt;
std::array<node,N> mes;
int n;

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    int m;
    std::cin >> n >> m;
    for(int i{ 1 }; i <= n; ++i)
        std::cin >> cnt[i];
    for(int i{ 1 },d,s,t; i <= m; ++i)
        std::cin >> mes[i].d >> mes[i].s >> mes[i].t;

    int l{},r{ n + 1 };

    while(l != r)
    {
        int mid = (l + r) >> 1;
        for(int i{ 1 }; i <= mid; ++i)
        {
            diff[mes[i].s] += mes[i].d;
            diff[mes[i].t + 1] -= mes[i].d;
        }
        for(int i{ 1 }; i <= n; ++i)
            diff[i] += diff[i - 1];
        int i{ 1 };
        for(; i <= n; ++i)
        {
            if (diff[i] > cnt[i])
                break;
        }
        std::for_each_n(diff.begin() + 1,n,[](std::size_t& val) -> void
        {
            val = 0;
        });
        if(i <= n)
            r = mid;
        else
            l = mid + 1;
    }
    if(r == n + 1)
        std::cout << '0';
    else
    {
        std::cout << "-1\n" << r;
    }

    return 0;
}