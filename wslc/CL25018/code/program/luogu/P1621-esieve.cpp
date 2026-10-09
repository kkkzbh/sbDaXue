

#include<iostream>
#include<bitset>
#include<array>

constexpr int M_size{ 100000 + 2 };

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
    void merge(int x,int y,size_t& ans)
    {
        int fx = find(x);
        int fy = find(y);
        if(fx != fy)
        {
            --ans;
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

int a,b,p;
std::bitset<M_size> table;
disjoint_set set;

int main()
{
    std::cin >> a >> b >> p;
    size_t ans{ b - a + 1ull };
    for(int i{ 2 }; i <= b; ++i)    //枚举质数
    {
        if(!table[i])
        {
            for(int j{ i }; j <= b; j += i)
            {
                table.set(j);
                if(i >= p && j >= a && j + i <= b)
                    set.merge(j,j + i,ans);
            }
        }
    }
    std::cout << ans;

    return 0;
}