

#include <bits/stdc++.h>

using namespace std;

int a[5][5];
auto ans = 0ull;
auto l = 0,r = 0;
using node = std::pair<int,int>;
auto sum = 0;

node next(int x,int y)
{
    if(y == 4) {
        return { x + 1,0 };
    }
    return { x,y + 1 };
}

bool row(int x)
{
    auto cnt = 0;
    auto& arr = a[x];
    for(auto i = 0; i != 5; ++i) {
        cnt += arr[i] == 1;
    }
    return cnt and cnt != 5;
}

bool col(int y)
{
    auto cnt = 0;
    for(auto i = 0; i != 5; ++i) {
        cnt += a[i][y] == 1;
    }
    return cnt and cnt != 5;
}

bool left()
{
    auto cnt = 0;
    for(auto i = 0; i != 5; ++i) {
        cnt += a[i][i] == 1;
    }
    return cnt and cnt != 5;
}

bool right()
{
    auto cnt = 0;
    for(auto i = 0; i != 5; ++i) {
        cnt += a[4 - i][i] == 1;
    }
    return cnt and cnt != 5;
}

void dfs(int x,int y,int lx,int ly)
{
    // std::cout << x << ' ' << y << '\n';
    if(l + 25 - sum < 13 or r + 25 - sum < 12) {
        return;
    }
    if(l > 13 or r > 12) {
        return;
    }
    if(x and y == 0) {
        if(not row(lx)) {
            return;
        }
    }
    if(x == 4 and y or x == 5) {
        if(not col(ly)) {
            return;
        }
    }
    if(x == 4 and y == 1) {
        if(not right()) {
            return;
        }
    }
    if(x == 5) {
        if(not left()) {
            return;
        }
    }
    if(x == 5) {
        if(l == 13 and r == 12) {
            ++ans;
        }
        return;
    }
    int nx,ny;
    auto nd = next(x,y);
    nx = nd.first;
    ny = nd.second;
    ++sum;
    ++l;
    a[x][y] = 1;
    dfs(nx,ny,x,y);
    --l;
    ++r;
    a[x][y] = 2;
    dfs(nx,ny,x,y);
    --r;
    --sum;
    a[x][y] = 0;
}


int main()
{
    ios::sync_with_stdio(false),std::cin.tie(nullptr);


    dfs(0,0,0,0);

    std::cout << ans;
    // std::cout << 3780704;


}