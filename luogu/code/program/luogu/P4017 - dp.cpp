

#include<iostream>
#include<format>
#include<array>
#include<vector>
#include<algorithm>
#include<iterator>
#include<ranges>
#include<queue>
#include<stack>

#define fun auto
#define print(...) std::cout << std::format(__VA_ARGS__)

constexpr static int N{ 5000 + 2 };
constexpr static int MOD{ 80112002 };

int n,m;
std::array<std::vector<int>,N> a;
std::array<int,N> ind,dp;

fun scan()
{
    std::cin >> n >> m;
    for(int i{ 1 }; i <= m; ++i)
    {
        int v1,v2;
        std::cin >> v1 >> v2;
        a[v1].push_back(v2);
        ++ind[v2];
    }
}

fun fdp()
{
    std::queue<int> que;
    std::stack<int> stk;
    for(int i{ 1 }; i <= n; ++i)
    {
        if(!ind[i])
        {
            que.push(i);
            stk.push(i);
            ind[i] = -1;
        }
    }
    while(!que.empty())
    {
        int val{ que.front() };
        que.pop();
        for(const int it : a[val])
        {
            if(!--ind[it])
            {
                que.push(it);
                stk.push(it);
            }
        }
    }
    while(!stk.empty())
    {
        int val{ stk.top() };
        stk.pop();
        if(a[val].empty())
        {
            dp[val] = 1;
        }
        else
        {
            for(const int it : a[val])
            {
                dp[val]  = (dp[val] + dp[it]) % MOD;
            }
        }
    }
}

fun put()
{
    int val{};
    for(int i{ 1 }; i <= n; ++i)
    {
        if(ind[i] == -1)
        {
            val = (val + dp[i]) % MOD;
        }
    }
    print("{}",val);
}

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    scan();
    fdp();
    put();


    return 0;
}