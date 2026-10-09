

#ifdef P2550

#include<iostream>

constexpr int size = 40;
int lottery[size];

int reward[10];

int main()
{
    int n;
    std::cin >> n;
    int value;
    for(int i = 0;i<7;++i)
    {
        std::cin >> value;
        ++lottery[value];
    }
    for(int i = 1;i<=n;++i)
    {
        int count = 0;
        for(int j = 1;j<=7;++j)
        {
            std::cin >> value;
            if(lottery[value]) ++count;
        }
        ++reward[count];
    }
    for(int i = 7;i>=1;--i)
    {
        std::cout << reward[i] << ' ';
    }

    return 0;
}

#endif
