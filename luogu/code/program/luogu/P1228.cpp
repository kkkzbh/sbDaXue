


#include<iostream>
#include<cmath>

constexpr int pow_2(int k)
{
    int val = 1;
    for(int i = 1; i <= k;++i)
    {
        val *= 2;
    }
    return val;
}

constexpr int ans[10]{0,1,2,3,4};
constexpr int move[10][2]{{},{1,1},{1,0},{0,1},{0,0}};


enum dirct
{
    left_up = 1,
    right_up,
    left_down,
    right_down,
};

int judge(int x,int y,int k,int a,int b)
{
    if(a <= x)
    {
        if(b <= y) return left_up;
        else return right_up;
    }
    else
    {
        if(b <= y) return left_down;
        else return right_down;
    }
}

void solve(int x,int y,int k,int a,int b)
{
    int dir = judge(x,y,k,a,b);
    int mv = static_cast<int>(std::pow(2,k - 2));
    std::cout << x + move[dir][0] << ' ' << y + move[dir][1] << ' ' << ans[dir] << '\n';
#if 1
    std::fflush(stdout);
#endif
    if(k == 1) return;
    if(dir == left_up)
    {
        solve(x - mv,y - mv,k - 1,a,b);
        solve(x - mv,y + mv,k - 1,x,y + 1);
        solve(x + mv,y - mv,k - 1,x + 1,y);
        solve(x + mv,y + mv,k - 1,x + 1,y + 1);
    }
    else if(dir == right_up)
    {
        solve(x - mv,y - mv,k - 1,x,y);
        solve(x - mv,y + mv,k - 1,a,b);
        solve(x + mv,y - mv,k - 1,x + 1,y);
        solve(x + mv,y + mv,k - 1,x + 1,y + 1);
    }
    else if(dir == left_down)
    {
        solve(x - mv,y - mv,k-1,x,y);
        solve(x - mv,y + mv,k - 1,x,y + 1);
        solve(x + mv,y - mv,k - 1,a,b);
        solve(x + mv,y + mv,k - 1,x + 1,y + 1);
    }
    else
    {
        solve(x - mv,y - mv,k - 1,x,y);
        solve(x - mv,y + mv,k - 1,x,y + 1);
        solve(x + mv,y - mv,k - 1,x + 1,y );
        solve(x + mv,y + mv,k - 1,a,b);
    }
}

int main()
{
    int k;
    int a,b;
    std::cin >> k >> a >> b;
    int x = static_cast<int>(std::pow(2,k - 1));
    int y = x;
    solve(x,y,k,a,b);

    return 0;
}

