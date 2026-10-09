


#include<iostream>
#include<array>
#include<cmath>

constexpr int size = 20 + 10;

bool isprime(int x)
{
    if(x == 1) return false;
    int sq = sqrt(x);
    for(int i = 2; i <= sq;++i)
    {
        if(x % i == 0) return false;
    }
    return true;
}

int dfs(std::array<int,size>& a,int top,int sum,int sec,int n,int k)
{
    if(n - top + 1 + sec < k) return 0;
    if(top == n + 1)
    {
        if(isprime(sum) && sec == k) return 1;
        return 0;
    }
    return dfs(a,top + 1,sum + a[top],sec + 1,n,k) +
        dfs(a,top + 1,sum,sec,n,k);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n,k;
    std::cin >> n >> k;
    std::array<int,size> a{};
    for(int i = 1; i <= n;++i)
    {
        std::cin >> a[i];
    }
    std::cout << dfs(a,1,0,0,n,k);

    return 0;
}