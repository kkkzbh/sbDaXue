
#ifdef P1028

#include<iostream>
#include<array>

constexpr int size = 1e3 + 10;

int main()
{
    int n;
    std::cin >> n;
    std::array<int,size> a{};
    for(int i = 1; i <= n;++i)
    {
        a[i] += 1;
        for(int j = i / 2;j >= 1;--j)
        {
            a[i] += a[j];
        }
    }
    std::cout << a[n];

    return 0;
}

#endif
