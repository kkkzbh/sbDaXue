

#include<iostream>
#include<array>
#include<algorithm>

constexpr int N{ 5000 + 1 };
constexpr int F{ 2 * N };

struct disjoint_set
{
    std::array<int,4 * N> a;

    disjoint_set()
    {
        a.fill(-1);
    }

    int find(int v) noexcept
    {
        if(a[v] > -1)
            return a[v] = find(a[v]);
        return v;
    }

    void merge(int x,int y) noexcept
    {
        int fx = find(x);
        int fy = find(y);
        if(fx != fy)
        {
            if(a[fx] < a[fy])
            {
                a[fy] += a[fx];
                a[fx] = fy;
            }
            else
            {
                a[fx] += a[fy];
                a[fy] = fx;
            }
        }
    }

    bool same(int x,int y) noexcept
    {
        return find(x) == find(y);
    }
};

struct node
{
    int l,r;
    bool tag{};   // false 奇数 true 偶数
};

std::array<node,N> a;
std::array<int,2 * N> dis;
int td{ 1 };
int n;
disjoint_set set;


int main()
{
    int m;
    std::cin >> n >> m;
    std::for_each_n(a.begin() + 1,m,[](node& n)
    {
        char str[5];
        std::cin >> n.l >> n.r >> str;
        if(str[0] == 'e')
            n.tag = true;
        dis[td++] = --n.l;
        dis[td++] = n.r;
    });
    std::sort(dis.begin() + 1,dis.begin() + td);
    td = static_cast<int>(std::unique(dis.begin() + 1,dis.begin() + td) - dis.begin());
    std::for_each_n(a.begin() + 1,m,[](node& n)
    {
        n.l = static_cast<int>(std::lower_bound(dis.begin() + 1,dis.begin() + td,n.l) - dis.begin());
        n.r = static_cast<int>(std::lower_bound(dis.begin() + 1,dis.begin() + td,n.r) - dis.begin());
    });
    int i{ 1 };
    for(; i <= m; ++i)
    {
        if(a[i].tag)
        {
            if(set.same(a[i].l,F + a[i].r))
            {
                break;
            }
            set.merge(a[i].l,a[i].r);
            set.merge(F + a[i].l,F + a[i].r);
        }
        else
        {
            if(set.same(a[i].l,a[i].r))
            {
                break;
            }
            set.merge(a[i].l,F + a[i].r);
            set.merge(F + a[i].l,a[i].r);
        }
    }
    std::cout << i - 1;

    return 0;
}