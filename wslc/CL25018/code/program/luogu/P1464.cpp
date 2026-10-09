

#ifdef P1464

#include<iostream>
#include<map>

struct node
{
    long long a;
    long long b;
    long long c;
    node() = default;
    node(long long A,long long B,long long C) : a(A),b(B),c(C){}
    bool operator<(const node& n) const
    {
        if(a != n.a) return a < n.a;
        if(b != n.b) return b < n.b;
        return c < n.c;
    }
};

std::map<node,long long> map;

long long w(long long a,long long b,long long c)
{
    node n(a,b,c);
    if(a <= 0 || b <= 0 || c <= 0)
    {
        return 1;
    }
    else if(a > 20 || b > 20 || c > 20)
    {
        if(map.find(n) != map.end())
        {
            return map[n];
        }
        else
        {
            return map[n] = w(20,20,20);
        }
    }
    else if(a < b && b < c)
    {
        long long sum = 0;
        node n1(a,b,c-1);
        node n2(a,b-1,c-1);
        node n3(a,b-1,c);
        if(map.find(n1) != map.end()) sum += map[n1];
        else sum += map[n1] = w(a,b,c-1);
        if(map.find(n2) != map.end()) sum += map[n2];
        else sum += map[n2] = w(a,b-1,c-1);
        if(map.find(n3) != map.end()) sum -= map[n3];
        else sum -= map[n3] = w(a,b-1,c);
        return sum;
    }
    else
    {
        long long sum = 0;
        node n1(a-1,b,c);
        node n2(a-1,b-1,c);
        node n3(a-1,b,c-1);
        node n4(a-1,b-1,c-1);
        if(map.find(n1) != map.end()) sum += map[n1];
        else sum += map[n1] = w(a-1,b,c);
        if(map.find(n2) != map.end()) sum += map[n2];
        else sum += map[n2] = w(a-1,b-1,c);
        if(map.find(n3) != map.end()) sum += map[n3];
        else sum += map[n3] = w(a-1,b,c-1);
        if(map.find(n4) != map.end()) sum -= map[n4];
        else sum -= map[n4] = w(a-1,b-1,c-1);
        return sum;
    }
}

int main()
{
    long long a,b,c;

    while(true)
    {
        std::cin >> a >> b >> c;
        if(a == b && b == c && c == -1) break;
        std::cout << "w(" << a << ", " << b << ", " << c << ") = " << w(a,b,c) << '\n';
    }

    return 0;
}

#endif

#ifdef P1464

#include<iostream>

using ll = long long;
constexpr int size = 20 + 10;

ll dp[size][size][size];

ll w(ll a,ll b,ll c)
{
    if(a <= 0 || b <= 0 || c <= 0 ) return 1;
    else if(a > 20 || b > 20 || c > 20)
    {
        return w(20,20,20);
    }
    else if(a < b && b < c)
    {
        ll sum = 0;
        if(dp[a][b][c-1]) sum += dp[a][b][c-1];
        else sum += dp[a][b][c-1] = w(a,b,c-1);
        if(dp[a][b-1][c-1]) sum += dp[a][b-1][c-1];
        else sum += dp[a][b-1][c-1] = w(a,b-1,c-1);
        if(dp[a][b-1][c]) sum -= dp[a][b-1][c];
        else sum -= dp[a][b-1][c] = w(a,b-1,c);
        return sum;
    }
    else
    {
        ll sum = 0;
        if(dp[a-1][b][c]) sum += dp[a-1][b][c];
        else sum += dp[a-1][b][c] = w(a-1,b,c);
        if(dp[a-1][b-1][c]) sum += dp[a-1][b-1][c];
        else sum += dp[a-1][b-1][c] = w(a-1,b-1,c);
        if(dp[a-1][b][c-1]) sum += dp[a-1][b][c-1];
        else sum += dp[a-1][b][c-1] = w(a-1,b,c-1);
        if(dp[a-1][b-1][c-1]) sum -= dp[a-1][b-1][c-1];
        else sum -= dp[a-1][b-1][c-1] = w(a-1,b-1,c-1);
        return sum;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    ll a,b,c;
    while(std::cin >> a >> b >> c)
    {
        if(a == b && b == c && c == -1) break;
        printf("w(%lld, %lld, %lld) = %lld\n",a,b,c,w(a,b,c));
    }
    
    return 0;
}

#endif
