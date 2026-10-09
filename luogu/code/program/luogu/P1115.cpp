

#include<iostream>
#include<array>
#include<algorithm>
#include<iterator>

constexpr int N{ 2 * 100000 + 1 };

std::array<int,N> a;
int n;

int main()
{
    std::cin >> n;
    std::copy_n(std::istream_iterator<int>{ std::cin },n,a.begin());
    int ans{ a[0] };
    for(int i{},sum{}; i != n; ++i)
    {
        sum = std::max(sum + a[i],a[i]);
        ans = std::max(sum,ans);
    }
    std::cout << ans;

    return 0;
}