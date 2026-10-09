

#include<iostream>
#include<array>
#include<algorithm>
#include<iterator>

constexpr int N{ 100000 + 2 };

std::array<int, N> a;
int n;
int w;

int main()
{
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
    std::cin >> n >> w;
    std::copy_n(std::istream_iterator<int>{ std::cin }, n, a.begin() + 1);
    for(int i{ 1 }; i <= n; ++i)
    {
        const int tmp{ a[i] };
        int j{ i };
        for (; j > 1 && tmp > a[j - 1]; --j)
            a[j] = a[j - 1];
        a[j] = tmp;
        std::cout << a[std::max(1, i * w / 100)] << ' ';
    }


    return 0;
}