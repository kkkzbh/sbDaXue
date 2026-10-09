

#include<iostream>
#include<array>
#include<algorithm>
#include<iterator>

constexpr int N{ 600 + 1 };

std::array<int,N> buc;
int w;

int main()
{
    int n;
    std::cin >> n >> w;
    for(int i{ 1 },val; i <= n; ++i)
    {
        std::cin >> val;
        ++buc[val];
        int cnt{ std::max(1,i * w / 100) },j{ 601 };
        while(cnt > 0 && --j >= 0)
            cnt -= buc[j];
        std::cout << j << ' ';
    }

    return 0;
}