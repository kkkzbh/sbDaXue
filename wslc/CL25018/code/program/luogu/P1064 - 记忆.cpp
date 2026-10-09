

#include<iostream>
#include<format>
#include<array>
#include<vector>
#include<algorithm>
#include<iterator>
#include<ranges>
#include<cmath>
#include<unordered_map>

#define fun auto
#define print(...) std::cout << std::format(__VA_ARGS__)

constexpr static int N1{ 32 * 1000 + 2 };
constexpr static int N2{ 60 + 2 };

struct node
{
    fun friend operator>>(std::istream& is,node& n) -> std::istream&
    {
        return is >> n.val >> n.weight;
    }
    int val;
    int weight;
};

struct node2
{
    fun friend operator>>(std::istream& is,node2& n) -> std::istream&
    {
        return is >> n.val >> n.weight >> n.it;
    }
    int val;
    int weight;
    int it;
};

int n,m;
std::array<node,N2> a;
std::array<node2,N2> tmp;
std::array<std::vector<node>,N2> b;
int t{ 1 };
std::array<std::array<int,N1>,N2> dp;
std::unordered_map<int,int> map;

fun scan()
{
    std::cin >> n >> m;
    std::copy_n(std::istream_iterator<node2>{ std::cin },m,tmp.begin() + 1);
    std::ranges::for_each(std::views::iota(1,m + 1),[](int i) mutable
    {
        if(!tmp[i].it)
        {
            map.emplace(i,t);
            a[t++] = { tmp[i].val,tmp[i].weight };
        }
    });
    std::ranges::for_each(std::views::iota(1,m + 1),[](int i) mutable
    {
        if(tmp[i].it)
        {
            b[map[tmp[i].it]].emplace_back(tmp[i].val,tmp[i].weight);
        }
    });
    for(auto& v : std::views::counted(dp.begin() + 1,m))
    {
        std::ranges::fill(std::views::counted(v.begin(),n + 1),-1);
    }
}

fun dfs(int i,int k) -> int
{
    if(i == t)
    {
        return 0;
    }
    if(dp[i][k] != -1)
    {
        return dp[i][k];
    }
    int ret{ std::numeric_limits<int>::min() };
    if(k + a[i].val <= n)
    {
        ret = std::max(ret,a[i].val * a[i].weight + dfs(i + 1,k + a[i].val));
        if(b[i].size() == 1 and k + a[i].val + b[i][0].val <= n)
        {
            ret = std::max(ret,a[i].val * a[i].weight + b[i][0].val * b[i][0].weight + dfs(i + 1,k + a[i].val + b[i][0].val));
        }
        else if(b[i].size() == 2)
        {
            int kv{ k + a[i].val };
            if(kv + b[i][0].val <= n)
            {
                ret = std::max(ret,a[i].val * a[i].weight + b[i][0].val * b[i][0].weight + dfs(i + 1,kv + b[i][0].val));
            }
            if(kv + b[i][1].val <= n)
            {
                ret = std::max(ret,a[i].val * a[i].weight + b[i][1].val * b[i][1].weight + dfs(i + 1,kv + b[i][1].val));
            }
            if(kv + b[i][0].val + b[i][1].val <= n)
            {
                ret = std::max(ret,a[i].val * a[i].weight + b[i][0].val * b[i][0].weight + b[i][1].val * b[i][1].weight
                                   + dfs(i + 1,kv + b[i][0].val + b[i][1].val));
            }
        }
    }
    ret = std::max(ret,dfs(i + 1,k));
    return dp[i][k] = ret;
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    scan();
    print("{}",dfs(1,0));

    return 0;
}