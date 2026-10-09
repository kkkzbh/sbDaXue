

#include<iostream>
#include<array>

constexpr int size = 15;
std::array<int,size> a;
int n;
int val;

void dfs(int i,int top)
{
    if(val == n && top != 2)
    {
        int flag = 1;
        for(int _ = 1; _ != top;++_)
        {
            if(flag) flag = 0; else std::cout << '+';
            std::cout << a[_];
        }
        std::cout << '\n';
        return;
    }
    for(int _ = i;_ <= n - val;++_)
    {
        val += _;
        a[top] = _;
        dfs(_,top + 1);
        val -= _;
    }
}

int main()
{
    std::cin >> n;
    dfs(1,1);

    return 0;
}