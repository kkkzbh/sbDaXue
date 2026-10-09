

#include<iostream>
#include<array>
#include<vector>

constexpr static int M_size{ 789863 + 2 };
constexpr std::size_t mod{ 43111 };

struct disjoint_set
{
    std::array<int,M_size> a;
    disjoint_set() { a.fill(-1 ); }
    int find(int x)
    {
        if(a[x] > -1)
            return a[x] = find(a[x]);
        return x;
    }
    void merge(int x,int y)
    {
        int fx = find(x);
        int fy = find(y);
        if(fx != fy)
        {
            if(fx < fy)
                a[fy] = fx;
            else
                a[fx] = fy;
        }
    }
    bool same(int x,int y)
    {
        return find(x) == find(y);
    }
};

constexpr char ans[][5]{"NO\n","YES\n"};
disjoint_set set;

inline std::size_t hash(size_t val)
{
    return val % M_size;
}

int main()
{
    int t;
    std::cin >> t;
    while(t--)
    {
        int n;
        std::cin >> n;
        int flag{ true };
        while(n--)
        {
            std::size_t i,j,e;
            std::cin >> i >> j >> e;
            if(flag)
            {
                if(e == 1)
                {
                    if(set.same(hash(i),hash(mod + j)) || set.same(hash(j),hash(mod + i)))
                        flag = false;
                    set.merge(hash(i),hash(j));
                }
                else
                {
                    if(set.same(hash(i),hash(j)))
                        flag = false;
                    set.merge(hash(i),hash(mod + j));
                    set.merge(hash(j),hash(mod + i));
                }
            }
        }
        set.a.fill(-1);
        std::cout << ans[flag];
    }

    return 0;
}