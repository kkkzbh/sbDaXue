

#include<iostream>
#include<array>
#include<algorithm>

constexpr int MOD{ 10007 };
constexpr int N{ 100000 + 2 };

using uint64 = unsigned long long;

struct node
{
    int id;
    int val;
    int color;
};

std::array<node,N> a;
int n,m;

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> n >> m;
    for(int i{ 1 }; i <= n; ++i)
    {
        a[i].id = i;
        std::cin >> a[i].val;
    }
    for(int i{ 1 }; i <= n; ++i)
        std::cin >> a[i].color;
    std::sort(a.begin() + 1,a.begin() + 1 + n,[](const node n1,const node n2) -> bool
    {
        if(n1.color == n2.color)
            return !(n1.id & 1);
        return n1.color < n2.color;
    });
    int it{ 1 },next{ it };
    uint64 ans{};
    while(next <= n)
    {
        while(next <= n and !(a[next].id + a[it].id & 1) and a[next].color == a[it].color)
            ++next;
        uint64 prefix{};
        for(int i{ it }; i != next; ++i)
            prefix = (prefix + a[i].val);
        for(int i{ it },cnt{ next - it - 2 }; i != next; ++i)
            ans = (ans + (a[i].id * (static_cast<uint64>(cnt) * a[i].val + prefix))) % MOD;
        it = next;
    }
    std::cout << ans;

    return 0;
}