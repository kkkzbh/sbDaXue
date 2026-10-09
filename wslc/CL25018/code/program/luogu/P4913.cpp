


#include<iostream>
#include<array>
#include<algorithm>

constexpr int size = 1e6 + 2;

struct node
{
    int l{};
    int r{};
};

std::array<node,size> a{0,1};

#define li (a[i].l)
#define ri (a[i].r)
int dfs(int i,const int n)  //更多的分类 可以减少更多不必要的一次性支路 不过其实差异并不太大 确实不会很大 不必要的大
{
    if(!i) return 0;
    else return std::max(dfs(li,n),dfs(ri,n)) + 1;
}

int main()
{
    int n;
    std::cin >> n;
    for(int i = 1,l,r; i <= n;++i)
    {
        std::cin >> a[i].l >> a[i].r;
    }
    std::cout << dfs(1,n);

    return 0;
}