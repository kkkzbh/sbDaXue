


#if 0

#include<iostream>
#include<array>
#include<algorithm>

constexpr int size = 20 + 10;

#if 0

对于一个科目有两个线程 ->
需要尽可能的让这两个线程一直工作 ->
给这两个线程分配工作 ->
把所有的问题分为两组 如果差值最小 为最优解(贪心,差值最小极大的利用了两个线程)
既然如此 如何分组？

优化剪枝方法如下
差值最小 -> 选择一个子集 尽可能的大 且不超过总的一半
这样从一个角度的思考 可以剪枝掉另一半对称的结果(对称性剪枝)
选or不选两层dfs 如果选后 大于总的一半 则直接不选 剪枝一半

合并的处理问题
采用数组存储了4个科目的数量 和4个科目的数组中的时间数据
但这样依然不利于直接去使用原数据,可以额外开一个载体变量去承接一些数据
在使用for循环时更新载体变量

优化
独立的处理每一个科目的问题 则可以实现一个数组的重复利用 不重复利用数组 dfs就要传数组引用了,这确实是
由于题目先输入的四个数据 才有的输入数组的数据 所以无法重复利用前四个数据

#endif

int ans;
int del = 1e9;
void solve(int s,const std::array<int,size>& a,int l,int r,int end)
{
    if(s == end + 1)
    {
        if(std::abs(r - l) < del) del = std::abs(r - l),ans = std::max(l,r);
        return;
    }
    l += a[s];
    solve(s + 1,a,l,r,end);
    l -= a[s];
    r += a[s];
    solve(s + 1,a,l,r,end);
    r -= a[s];
}

int main()
{
    std::ios::sync_with_stdio(false),std::cout.tie(nullptr),std::cin.tie(nullptr);
    std::array<int,size> a{},b{},c{},d{};
    int s1,s2,s3,s4;
    std::cin >> s1 >> s2 >> s3 >> s4;
    for(int i = 1; i <= s1;++i) std::cin >> a[i];
    for(int i = 1; i <= s2;++i) std::cin >> b[i];
    for(int i = 1; i <= s3;++i) std::cin >> c[i];
    for(int i = 1; i <= s4;++i) std::cin >> d[i];
    int sum{};
    solve(1,a,0,0,s1);
    sum += ans;
    del = 1e9;
    solve(1,b,0,0,s2);
    sum += ans;
    del = 1e9;
    solve(1,c,0,0,s3);
    sum += ans;
    del = 1e9;
    solve(1,d,0,0,s4);
    sum += ans;
    std::cout << sum;

    return 0;
}

#endif


#include<iostream>
#include<array>
#include<algorithm>

constexpr int size = 20 + 10;
std::array<int,4 + 1> s;
std::array<int,size> a;
int slen,max_time,sum_time,tim;
int ans;

void dfs(int i)
{
    if(i > slen)
    {
        max_time = std::max(max_time,tim);
        return;
    }
    if(tim + a[i] <= sum_time / 2)
    {
        tim += a[i];
        dfs(i + 1);
        tim -= a[i];
    }
    dfs(i + 1);
}

int main()
{
    std::cin >> s[1] >> s[2] >> s[3] >> s[4];
    for(int _ = 1; _ <= 4;++_)
    {
        max_time = 0;
        sum_time = 0;
        slen = s[_];
        for(int i = 1; i <= slen;++i)
        {
            std::cin >> a[i];
            sum_time += a[i];
        }
        dfs(1);
        ans += sum_time - max_time;
    }
    std::cout << ans;

    return 0;
}






