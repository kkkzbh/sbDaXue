

#include<iostream>
#include<array>
#include<algorithm>

constexpr static int M_size{ 200000 + 10 };
constexpr int M_size2{ 100000 + 2 };

/* ****************************** /*

OK啊 最终也是破案了
到底什么时候使用反集
如果A 不能与B在一起 C也不能与B在一起的时候 A 就与 C 在一起 则这种情况使用反集
如果说 没有 A 一定要与C 在一起 则不可以使用反集合
那么对于本题如何处理关系呢
一个方法是 静态处理   处理所有数据后 优先处理 1 的关系
处理完1的关系后 那么所有的1关系都确定了
再去处理0关系 看一下是否存在矛盾的地方 这里用反集会自己额外产生A ≠ B C ≠ B -> A = C 的额外关系 这是不行的

谨慎的去判断传递性关系 对于并查集的处理 我们容易发现 更深层次的是 所处理的元素是具有传递性的
而本题的不等号不具备传递性 因而无论另开集 或者开反集 都会寄掉

/* ****************************** */

struct disjoint_set
{
    constexpr static int M_size3{ 200000 + 30 };
    std::array<int,M_size3> a;
    disjoint_set(){ a.fill(-1); }
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

struct node
{
    int i;
    int j;
    int e;
};

constexpr char ans[][5]{"NO\n","YES\n"};

disjoint_set set;
std::array<node,M_size2> data;
std::array<int,M_size> dis;

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    int t;
    std::cin >> t;
    while(t--)
    {
        int n;
        std::cin >> n;
        int j{ 1 };
        for(int i{ 1 }; i <= n;++i,j += 2)
        {
            std::cin >> data[i].i >> data[i].j >> data[i].e;
            dis[j] = data[i].i;
            dis[j + 1] = data[i].j;
        }
        std::sort(dis.begin() + 1,dis.begin() + j);
        j = std::unique(dis.begin() + 1,dis.begin() + j) - dis.begin();
        for(int i{ 1 }; i <= n; ++i)
        {
            data[i].i = std::lower_bound(dis.begin() + 1,dis.begin() + j,data[i].i) - dis.begin();
            data[i].j = std::lower_bound(dis.begin() + 1,dis.begin() + j,data[i].j) - dis.begin();
        }
        bool flag{ true };
        // for(int i{ 1 }; i <= n && flag ; ++i)
        // {
        //     if(data[i].e == 1)
        //     {
        //         if(set.same(data[i].i,M_size + data[i].j) || set.same(data[i].j,M_size + data[i].i))
        //             flag = false;
        //         set.merge(data[i].i,data[i].j);
        //     }
        //     else
        //     {
        //         if(set.same(data[i].i,data[i].j))
        //             flag = false;
        //         set.merge(data[i].i,M_size + data[i].j);
        //         set.merge(data[i].j,M_size + data[i].i);
        //     }
        // }
        std::sort(data.begin() + 1,data.begin() + 1 + n,[](const node& n1,const node& n2)
        {
            return n2.e < n1.e;
        });
        for(int i{ 1 }; i <= n && flag ;++i)
        {
            if(data[i].e == 1)
            {
                set.merge(data[i].i,data[i].j);
            }
            else
            {
                if(set.same(data[i].i,data[i].j))
                    flag = false;
            }
        }
        std::cout << ans[flag];
        set.a.fill(-1);
    }

    return 0;
}