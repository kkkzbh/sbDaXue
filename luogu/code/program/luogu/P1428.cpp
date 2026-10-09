

#ifdef P1428

#include<iostream>

constexpr int size = 100 + 10;
int cuty[size];

int main()
{
    int n;
    std::cin >> n;
    for(int i = 1;i<=n;++i)
        std::cin >> cuty[i];
    int count = 0;
    for(int i = 1;i<=n;++i)
    {
        for (int j = 1; j < i; ++j)
        {
            if (cuty[j] < cuty[i]) ++count;
        }
        std::cout << count << ' ';
        count = 0;
    }

    return 0;
}

#endif
