

#ifdef P3817

#include<iostream>
#include<array>

constexpr int size = 1e5 + 10;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    int x;
    std::cin >> n >> x;
    std::array<long long,size> a{};
    for(int i = 1; i <= n;++i)
    {
        std::cin >> a[i];
    }
    long long count = 0;
    for(int i = 2; i <= n;++i)
    {
        if(a[i] + a[i - 1] > x)
        {
            if(a[i - 1] > x)
            {
                count += a[i] + a[i - 1] - x;
                a[i] = 0;
                a[i - 1] = x;
            }
            else
            {
                count += a[i] - x + a[i - 1];
                a[i] = x - a[i - 1];
            }
        }
    }
    std::cout << count;

    return 0;
}

#endif
