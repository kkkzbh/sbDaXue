

#include<iostream>
#include<format>
#include<array>
#include<vector>
#include<algorithm>
#include<iterator>
#include<ranges>
#include<cmath>
#include<unordered_set>

#define fun auto
#define print(...) std::cout << std::format(__VA_ARGS__)

constexpr static int N{ 32 * 1000 + 2 };
constexpr static int N2{ 60 + 2 };

struct node
{
    fun friend operator>>(std::istream& is,node& n) -> std::istream&
    {
        return is >> n.v >> n.weigh >> n.it;
    }
    int v,weigh,it;
};

int n,m;
std::array<node,N2> a;
std::array<node*,N2> b;
std::unordered_set<int> set;
std::array<std::array<int,N>,N2> dp;

fun scan()
{
    std::cin >> n >> m;
    std::copy_n(std::istream_iterator<node>{ std::cin },m,a.begin() + 1);
    for(int i : std::views::iota(1,m + 1))
    {
        b[i] = &a[i];
    }
    std::ranges::sort(std::views::counted(b.begin() + 1,m),[](const node* n1,const node* n2)
    {
        return n1->it < n2->it;
    });
    std::ranges::for_each(std::views::counted(dp.begin() + 1,m),[](auto& v)
    {
        std::ranges::fill(std::views::counted(v.begin(),n + 1),-1);
    });
}

fun dfs(int i,int k) -> int
{
    if(i == m + 1) // end
    {
        return 0;
    }
//    if(dp[i][k] != -1)
//    {
//        return dp[i][k];
//    }
    if(!b[i]->it)   // 主件
    {
        int v1{ -2147483648 };
        if(k + b[i]->v <= n)
        {
            int dis{ static_cast<int>(std::ranges::distance(a.begin(), b[i])) };
            set.insert(dis);
            v1 = b[i]->v * b[i]->weigh + dfs(i + 1, k + b[i]->v);
            set.erase(dis);
        }
        return dp[i][k] = std::max(v1,dfs(i + 1,k));
    }
    else    // 非主件
    {
        int v1{ -2147483648 };
        if(set.contains(b[i]->it) and k + b[i]->v <= n)
        {
            v1 = b[i]->v * b[i]->weigh + dfs(i + 1,k + b[i]->v);
        }
        return dp[i][k] = std::max(v1,dfs(i + 1,k));
    }
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    scan();
    print("{}",dfs(1,0));

    return 0;
}