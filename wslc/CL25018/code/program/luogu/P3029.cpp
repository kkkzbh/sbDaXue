

#include<iostream>
#include<array>
#include<iterator>
#include<algorithm>
#include<bitset>

constexpr int N{ 50000 + 2 };

struct node
{
    friend std::istream& operator>>(std::istream& is,node& n)
    {
        is >> n.x >> n.id;
        return is;
    }
    int x;
    int id;
};

std::array<node,N> a;
std::array<int,N> dis;
int dt{ 1 };
int n;
std::array<int,N> vis;
int cnt;

int hash(int id)
{
    return static_cast<int>(std::lower_bound(dis.begin() + 1,dis.begin() + dt,id) - dis.begin());
}

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    std::cin >> n;
    std::for_each_n(a.begin() + 1,n,[](node& n) -> void
    {
        std::cin >> n;
        dis[dt++] = n.id;
    });
    std::sort(dis.begin() + 1,dis.begin() + dt);
    dt = std::unique(dis.begin() + 1,dis.begin() + dt) - dis.begin();
    std::sort(a.begin() + 1,a.begin() + 1 + n,[](const node& n1,const node& n2)
    {
        return n1.x < n2.x;
    });
    std::size_t ans{ -1ull };
    for(int l{ 1 },r{ 1 },cei{ dt - 1 }; r <= n; ++r)
    {
        if(!vis[hash(a[r].id)]++)
            ++cnt;
        if(cnt == cei)
        {
            for(int val{ hash(a[l].id) }; vis[val] > 1; val = hash(a[++l].id))
                --vis[val];
            ans = std::min(ans,static_cast<std::size_t>(a[r].x - a[l].x));
        }
    }
    std::cout << ans;

    return 0;
}