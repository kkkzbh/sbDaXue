

#include<iostream>
#include<array>
#include<vector>

/* ************************ /*

本题有一个可优化点 我使用了一个vector记录所有敌人
以至于每次敌人对上敌人 并上对方的敌人集合 我采取遍历对方所有的敌人并merge
其实只要有一个对方的敌人 我merge就可以了 好好想想 为什么？

另外 反集  n + x 双方的合并 希望明天你体会一下

/* ************************ */

constexpr int M_size{ 1000 + 2 };

struct disjoint_set
{
    std::array<int,M_size> a;
    disjoint_set(){ a.fill(-1); }
    int find(int x)
    {
        if(a[x] > -1)
            return a[x] = find(a[x]);
        return x;
    }
    void merge(int x,int y,size_t& n)
    {
        int fx = find(x);
        int fy = find(y);
        if(fx != fy)
        {
            --n;
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
    bool same(int x,int y)
    {
        return find(x) == find(y);
    }
};

disjoint_set set;
std::array<std::vector<int>,M_size> a;

int main()
{
    int n,m;
    std::cin >> n >> m;
    size_t ans{ n };
    while(m--)
    {
        char op;
        int p,q;
        if(std::cin >> op >> p >> q; op == 'E')
        {
            for(auto&& it : a[p])
                set.merge(q,it,ans);
            for(auto&& it : a[q])
                set.merge(p,it,ans);
            a[p].push_back(q);
            a[q].push_back(p);
        }
        else if(op == 'F')
        {
            set.merge(p,q,ans);
        }
    }
    std::cout << ans;


    return 0;
}