


//实模拟 -> 虚模拟
// 拟定的位置 具体在哪儿个监狱 我不显示指定 我使用并查集处理 谁与谁要在一起这个信息 至于在哪儿个监狱 不管 不模拟

#include<iostream>
#include<array>
#include<algorithm>

struct disjoint_set
{
    constexpr static int M_size{ 20000 + 2 };
    std::array<int,M_size> a;

    [[nodiscard]]
    int find(int x) noexcept
    {
        if(a[x] > 0)
            return a[x] = find(a[x]);
        return x;
    }
    void merge(int x,int y) noexcept
    {
        int fx = find(x);
        int fy = find(y);
        if(fx != fy)
        {
            if(fx < fy)
            {
                a[fx] = fy;
            }
            else
            {
                a[fy] = fx;
            }
        }
    }
    bool same(int x,int y)
    {
        return find(x) == find(y);
    }
};

struct node
{
    friend bool operator<(const node& n1,const node& n2) noexcept
    {
        return n1.force < n2.force;
    }
    friend bool operator>(const node& n1,const node& n2) noexcept
    {
        return n2 < n1;
    }
    friend std::istream& operator>>(std::istream& in,node& n)
    {
        in >> n.x >> n.y >> n.force;
        return in;
    }
    int x;
    int y;
    int force;
    node() noexcept = default;
    node(int x,int y,int force) noexcept : x(x),y(y),force(force){}
};

constexpr int M_size{ 100000 + 2 };
std::array<node,M_size> a;
int m;
constexpr int M_size_1{ 20000 + 2 };
std::array<int,M_size_1> tab;
disjoint_set set;

int main()
{
    int n;
    std::cin >> n >> m;
    for(int i{ 1 }; i <= m; ++i)
    {
        std::cin >> a[i];
    }
    std::sort(a.begin() + 1,a.begin() + 1 + m,std::greater<>());
    size_t ans{};   //要初始化为0 可能刚好碰上题目那个输出0的条件
    for(int i{ 1 }; i <= m; ++i)    //从边权最大的一组人开始 尽量的去拆散他们
    {
        if(set.same(a[i].x,a[i].y)) //后续判断 如果我先前的操作 已经被迫把 x,y放到一个监狱了 那么此时当前的最大边权为ans
        {
            ans = a[i].force;
            break;
        }
        //如果没有遇到过x 那么就先记下这个信息  x 不跟 y (tab[x]) 放在一起
        if(!tab[a[i].x])    //如果我们始终遵守这个规定 那么最大值一定不会是这组边
        {
            tab[a[i].x] = a[i].y;
        }
        else    // 如果我先前遇到了x了 如果要想拆散这组的 x与 y  就只能把y与tab[x]放在一个监狱
        {
            set.merge(a[i].y,tab[a[i].x]);
        }
        if(!tab[a[i].y])    //之前没遇到过y 那么就直接记下 y 不能跟这个x 放在一起 以tab[y]记下
        {
            tab[a[i].y] = a[i].x;
        }
        else  //如果已经知道了 之前的y 必须与 谁分离 那么接下来这组的x与y 我如果想分离 就只能把x tab[y]放在一个监狱
        {
            set.merge(a[i].x,tab[a[i].y]);
        }
    }
    std::cout << ans;

    return 0;
}