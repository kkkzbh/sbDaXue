

#include <bits/stdc++.h>
using namespace std::views;
using i64 = long long;

auto rr = std::vector<int>{};
auto cc = std::vector<int>{};
int l,n;
auto ans = 0LL;
void dfs(int i)
{
    if(i == n * n) {
        ++ans;
        return;
    }
    auto row = i / n;
    auto cow = i % n;
    for(auto val = 0; val <= l; ++val) {
        if(rr[row] + val > l or cc[cow] + val > l) {
            break;
        }
        rr[row] += val;
        cc[cow] += val;
        if((cow != n - 1 or rr[row] == l) and (row != n - 1 or cc[cow] == l)) {
            dfs(i + 1);
        }
        rr[row] -= val;
        cc[cow] -= val;
    }
}

auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> l >> n;

    rr = std::vector(n,0);
    cc = std::vector(n,0);



    dfs(0);
    std::cout << ans;

}