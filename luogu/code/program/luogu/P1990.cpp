


#include<iostream>
#include<array>

using ll = long long;

constexpr int size = 1e6 + 10;

std::array<ll,size> dp;

inline void mod(ll& a)
{
    a %= 10000;
}


#if 0

有时得到的状态转移方程 是可以有数学上的化简的！！
Fn = Fn-1 + Fn-2 + 2 * (Fn-3 + Fn-4 + ... + F0);
可以结合Fn-1 = ...
联立求解一个简洁的 Fn  或者通过保留前n-1项和去计算答案

#endif

#if 0

一个降维的状态转移为 讨论最后结尾的结束情况是怎么样的
                    然后转移状态
            //结束大概就是 有横 有竖 有L
#endif
int main()
{
    int n;
    std::cin >> n;
    dp[0] = 1;
    dp[1] = 1;
    ll sum = dp[0] + dp[1];
    for(int i = 2; i <= n;++i)
    {
        dp[i] = 2 * sum - dp[i - 1] - dp[i - 2];
        mod(dp[i]);
        sum += dp[i];
        sum % 1000000;
    }
    std::cout << dp[n];

    return 0;
}
