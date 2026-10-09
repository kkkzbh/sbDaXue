


#include<iostream>
#include<array>

constexpr int size = 13 + 10;

int n,cnt;
std::array<int,size> a;
std::array<bool,size> b1,b2,b3;

void dfs(int i)
{
    if(i == n + 1)
    {
        if(cnt < 3)
        {
            for (int _ = 1; _ <= n; ++_) std::cout << a[_] << ' ';
            std::cout << '\n';
        }
        ++cnt;
    }
    for(int _ = 1; _ <= n;++_)
    {
        if(!b1[_] && !b2[i + _] && !b3[i - _ + 13])
        {
            a[i] = _;
            b1[_] = b2[i + _] = b3[i - _ + 13] = true;
            dfs(i + 1);
            b1[_] = b2[i + _] = b3[i - _ + 13] = false;
        }
    }
}

int main()
{
    std::cin >> n;
    for(int i = 1; i <= n;++i) a[i] = i;
    dfs(1);
    std::cout << cnt;

    return 0;
}