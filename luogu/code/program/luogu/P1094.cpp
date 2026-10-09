

#ifdef P1094

#include<iostream>
#include<array>
#include<algorithm>

constexpr int size = 3 * 1e4 + 10;

int main()
{
    int w;
    int n;
    std::array<int,size> G = {0};
    std::cin >> w >> n;
    for(int i = 1 ; i <= n;++i)
    {
        std::cin >> G[i];
    }
    std::sort(G.begin() + 1,G.begin() + 1 + n);
    int left = 1;
    int right = n;
    int cnt = n;
    while(true)
    {
        while(G[left] + G[right] > w) --right;
        if(left < right)
        {
            --cnt;
            ++left;
            --right;
        }
        else break;
    }
    std::cout << cnt;

    return 0;
}

#endif
