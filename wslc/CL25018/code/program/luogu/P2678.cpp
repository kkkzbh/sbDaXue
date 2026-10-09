


#include<iostream>
#include<array>

constexpr int size = 50000 + 10;

bool solve(const std::array<int,size>& a,int len,int m,int n)
{
    int cnt{};
    int dis{};
    for(int i = 1; i <= n;++i)
    {
        if(a[i] + dis < len)  dis += a[i],++cnt;
        else dis = 0;
    }
    return cnt <= m;
#if 0
    关于本题 对于删除终点的一个解释
    1.走到终点时 距离大于len 则程序完全正常
    2.走到终点时 距离小于len 此时若存在前一个结点 则删除前一个结点(前一个结点的左距离大于len 则删除后 必定大于len) 此时与删除终点的cnt次数等价 且解法合理
    3.第二种情况时 不存在前一个结点 前一个结点就是起点结点 中间的结点全部被删除 且依然距离小于len
    如果cnt > m 则会有正常判定的结果
    若cnt <= m 此时就会得到错误结果 所以需要针对len的值提前进行一次特判 把第三种情况直接排斥掉  但本题数据可以不排斥
#endif
}

int main()
{
    int len,n,m; std::cin >> len >> n >> m;
    std::array<int,size> a{};
    for(int i = 1; i <= n;++i) std::cin >> a[i];
    std::array<int,size> dis{};
    for(int i = 1; i <= n;++i) dis[i] = a[i] - a[i - 1];
    dis[n + 1] = len - a[n];
    int l = 1,r = 1e9 + 1;
    while(l != r)
    {
        int mid = (l + r) >> 1;
        if(mid > len || !solve(dis,mid,m,n + 1)) r = mid;
        else l = mid + 1;
    }
    std::cout << l - 1;

    return 0;
}
