

#ifdef P1255

#include<iostream>
#include<array> //使用多个数组 也可以不定义多个数组而采用多维数组的形式 可以利用指针移动循环控制数组的使用
#include<iomanip>

constexpr int size = 5000 + 10;

void add(std::array<int,size>& a, int& ta,std::array<int,size>& b,const int& tb)
{
    ta += tb;
    for(int i = 1; i <= ta;++i)
    {
        a[i] += b[i];
        a[i + 1] += a[i] / 100000000;
        a[i] %= 100000000;
    }
    while(!a[ta]) --ta;
}

void eqal(std::array<int,size>& a,int& ta,std::array<int,size>& b,const int& tb)
{
    ta = tb;
    for(int i = 1; i <= ta;++i)
    {
        a[i] = b[i];
    }
}

void solve(int x,std::array<int,size>& ans,int& ta)
{
    if(x == 1 || x == 2)
    {
        ans[1] = x;
        ta = 1;
        return;
    }
    ans[1] = 1;
    std::array<int,size> b{0,2};
    int tb = 1;
    std::array<int,size> ret{};
    int tr = 0;
    for(int i = 3; i <= x;++i)
    {
        eqal(ret,tr,ans,ta);
        add(ans,ta,b,tb);
        eqal(b,tb,ret,tr);
    }
}

int main()
{
    int x;
    std::cin >> x;
    std::array<int,size> ans{};
    int ta;
    solve(x,ans,ta);
    std::cout << ans[ta--];
    for(int i = ta;i > 0;--i)
    {
        std::cout << std::setw(8) << std::setfill('0') << ans[i];
    }

    return 0;
}

#endif
