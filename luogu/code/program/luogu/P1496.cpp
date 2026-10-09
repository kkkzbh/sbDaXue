

#include<iostream>
#include<array>
#include<algorithm>
#include<utility>

constexpr int N{ 20000 + 2 };
constexpr int M_size{ 2 * N };

std::array<int,M_size> a;
std::array<int,M_size> dis;
int dis_top;
std::array<std::pair<int,int>,M_size> v;
std::array<int,M_size> diff;


int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    int n;
    std::cin >> n;
    for(int i{ 1 }; i <= n; ++i)
    {
        auto x = (i << 1) - 1;
        auto y = i << 1;
        std::cin >> a[x] >> a[y];
        dis[x] = a[x];
        dis[y] = a[y];
    }
    std::sort(dis.begin() + 1,dis.begin() + 1 + 2 * n);
    dis_top = std::unique(dis.begin() + 1,dis.begin() + 1 + (n << 1)) - dis.begin();
    for(int i{ 1 }; i <= n; ++i)
    {
        v[i].first = std::lower_bound(dis.begin() + 1,dis.begin() + dis_top,a[(i << 1) - 1]) - dis.begin();
        v[i].second = std::lower_bound(dis.begin() + 1,dis.begin() + dis_top,a[i << 1]) - dis.begin();
    }
    for(int i{ 1 }; i <= n; ++i)
    {
        diff[v[i].first] += 1;
        diff[v[i].second] -= 1;
    }
    int ans{};
    for(int i{ 1 },cei{ n << 1 }; i <= cei; ++i)
        diff[i] += diff[i - 1];
    int l{ 1 },r{ 1 };
    int cei{ n << 1 };
    while(r <= cei)
    {
        while(r <= cei && diff[r])
            ++r;
        ans += dis[r] - dis[l];
        while(r <= cei && !diff[r]) //离散化之后 仍然存在一个相对的一个关系  cnt = 末尾 - 初始.....
                                    //对于离散的数据来言 以前的一些恒等式子可能就不成立了 毕竟元素间隔不是1
                                    //区间范围 1 1 1 1 1 1 1 1 1 0  仍包含尾后0的这个数据 指向离散化结尾点
            ++r;
        l = r;
    }
    std::cout << ans;

    return 0;
}