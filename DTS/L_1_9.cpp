

#ifdef L_1_9

#include<iostream>

constexpr int size = 1e5 + 10;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    int a[size];
    for(int i = 1; i <=n;++i)
    {
        std::cin >> a[i];
    }
    int beg = 0;
    int end = 0;
    int it = 1;
    for(int i = 2; i <= n;++i)
    {
        if(a[i] > a[i - 1]);
        else
        {
            if(i - it > end - beg)
            {
                beg = it;
                end = i;
            }
            it = i;
        }
    }
    if(n + 1 - it > end - beg)
    {
        beg = it;
        end = n + 1;
    }
    it = n + 1;
    int flag = 1;
    while(beg != end)
    {
        if(flag) flag = 0;else std::cout << ' ';
        std::cout << a[beg++];
    }
    return 0;
}

#endif
