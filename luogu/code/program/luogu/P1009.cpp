

#ifdef P1009

#include<iostream>
#include<array>

constexpr int size = 66;

std::array<int,size> sum;
std::array<int,size> lv{0,1};
int sl = 1;
int ss = 1;
constexpr int sr = 2;

void add()
{
    int max = std::max(sl,ss);
    for(int i = 1; i <= max;++i)
    {
        sum[i] += lv[i];
        sum[i + 1] += sum[i] / 10;
        sum[i] %= 10;
    }
    ss = sum[max + 1] ? max + 1 : max;
}

void mul(int n)
{
    for(int i = 1; i <= sl;++i)
    {
        lv[i] *= n;
    }
    for(int i = 1; i <= sl + sr;++i)
    {
        lv[i + 1] += lv[i] / 10;
        lv[i] %= 10;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    for(int i = 1; i <= n;++i)
    {
        mul(i);
        for(sl += sr;lv[sl] == 0;--sl);
        add();
    }
    for(;ss >= 1;--ss) std::cout << sum[ss];

    return 0;
}

#endif
