


#include<iostream>
#include<array>
#include<algorithm>
#include<cmath>

constexpr int size = 10 + 10;

int n;
std::array<int,size> acid,bitter;

int ans = 2e9;
int ac{1},bit;
int cnt;

void dfs(int i)
{
    if(i == n + 1)
    {
        if(cnt) ans = std::min(ans,std::abs(bit - ac));
        return;
    }
    ac *= acid[i];
    bit += bitter[i];
    ++cnt;
    dfs(i + 1);
    ac /= (acid[i] ? acid[i] : 1);
    bit -= bitter[i];
    --cnt;
    dfs(i + 1);
}


int main()
{
    std::cin >> n;
    for(int i = 1; i <= n;++i)
    {
        std::cin >> acid[i];
        std::cin >> bitter[i];
    }
    dfs(1);
    std::cout << ans;



    return 0;
}
