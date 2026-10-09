

#include<iostream>
#include<array>
#include<algorithm>
#include<iterator>

constexpr int N{ 100'000 + 2 };

std::array<int,N> a;
int n;

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    std::cin >> n;
    std::copy_n(std::istream_iterator<int>(std::cin),n,a.begin() + 1);
    std::array<int,N> tmp;
    std::copy_n(a.begin() + 1,n,tmp.begin() + 1);
    std::sort(tmp.begin() + 1,tmp.begin() + 1 + n);
    tmp[0] = tmp[n + 1] = -1;
    int cnt{ n };
    for(int i{ 1 }; i <= n; ++i)
    {
        cnt -= tmp[i] == a[i];
    }
    std::cout << (cnt + 2) / 3;

    return 0;
}