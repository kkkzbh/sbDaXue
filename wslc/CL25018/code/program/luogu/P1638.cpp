

#include<iostream>
#include<array>
#include<iterator>
#include<algorithm>

constexpr int N{ 1000000 + 2 };

std::array<int,N> a;
std::array<int,N> vis;
int n,m;

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    std::cin >> n >> m;
    std::copy_n(std::istream_iterator<int>{ std::cin },n,a.begin() + 1);
    int ia{},ib{ 2147483647 };
    for(int l{ 1 },r{ 1 },cnt{}; r <= n; ++r)
    {
        if(!vis[a[r]]++)
        {
            ++cnt;
        }
        while(vis[a[l]] > 1)
            --vis[a[l++]];
        if(cnt == m && r - l < ib - ia)
        {
            ia = l;
            ib = r;
        }
    }
    std::cout << ia << ' ' << ib;

    return 0;
}