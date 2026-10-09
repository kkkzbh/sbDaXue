

#include<iostream>
#include<array>
#include<utility>

constexpr int N{ 200000 + 2 };

//标准个数和 * 标准价值和

std::array<std::pair<int,int>,N> a;
std::array<std::pair<int,int>,N> sec;
std::array<std::pair<std::size_t,std::size_t>,N> prefix;
int n,m;
std::size_t s;

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    std::cin >> n >> m >> s;
    for(int i{ 1 }; i <= n ;++i)
        std::cin >> a[i].first >> a[i].second;
    for(int i{ 1 }; i <= m; ++i)
        std::cin >> sec[i].first >> sec[i].second;
    int l{},r{ 1000000 + 1 };
    std::size_t lv{ static_cast<std::size_t>(-1) },rv{ static_cast<std::size_t>(-1) };
        //更新迭代vis 只是此二分并非最后一个vis一定是答案 可以加条件记录
    while(l != r)
    {
        int mid{ (l + r) >> 1 };
        for(int i{ 1 }; i <= n; ++i)
        {
            prefix[i].first = prefix[i - 1].first + (a[i].first >= mid);
            prefix[i].second = prefix[i - 1].second + (a[i].second * (a[i].first >= mid));
        }
        std::size_t val{};
        for(int i{ 1 }; i <= m; ++i)
        {
            val += (prefix[sec[i].second].first - prefix[sec[i].first - 1].first) *
             (prefix[sec[i].second].second - prefix[sec[i].first - 1].second);
        }
        if(val > s)
        {
            rv = val;
            l = mid + 1;
        }
        else
        {
            lv = val;
            r = mid;
        }
    }
    std::cout << std::min(s - lv,rv - s);

    return 0;
}