

#include<iostream>
#include<array>     //偶数-F  奇数-B        //要留所有的奇数
#include<algorithm>
#include<iterator>
#include<bitset>

constexpr int N{ 5000 + 2 };

std::array<int,N> a;
std::array<int,N> cpy;
std::bitset<N> diff;
int n;

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    std::cin >> n;
    std::for_each_n(a.begin() + 1,n,[](int& val) -> void
    {
        char c;
        std::cin >> c;
        if(c == 'B')
            val = 1;
    });
    std::copy_n(a.begin() + 1,n,cpy.begin() + 1);
    int ans{ 2147483647 },ansk;
    for(int k{ 1 }; k <= n; ++k) //枚举k
    {
        int cnt{};
        bool find{ true };
        for(int i{ 1 }; i <= n; ++i)    //遍历
        {
            if(diff[i])
                find = !find;
            if(int cei{ n - k + 1 }; a[i] == find && i <= cei)
            {
                find = !find;
                diff.set(i + k);
                ++cnt;
            }
            else if(a[i] == find)
            {
                cnt = 2147483647;
                break;
            }
        }
        if(cnt < ans)
        {
            ans = cnt;
            ansk = k;
        }
        std::copy_n(cpy.begin() + 1,n,a.begin() + 1);
        diff.reset();
    }
    std::copy_n(std::begin({ ansk,ans }),2,
                std::ostream_iterator<int>(std::cout," "));

    return 0;
}