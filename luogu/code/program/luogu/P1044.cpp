

#ifdef P1044

#include<iostream>
#include<array>

constexpr int size = 18 + 10;

template<typename T>
int solve(T& a,int x,int y)
{
    if(x == 0 && y == 0)
        return 0;
    if(a[x][y]) return a[x][y];
    if(x == 0)
    {
        return a[x][y] = solve(a,x+1,y-1);
    }
    if(y == 0)
    {
        return a[x][y] = 1;
    }
    return a[x][y] = solve(a,x+1,y-1) + solve(a,x-1,y);
}

int main()
{
    int n;
    std::cin >> n;
    std::array<std::array<int,size>,size> a{};
    int ret = solve(a,0,n);
    std::cout << ret;

    return 0;
}

#endif

#ifdef P1044

#include<iostream>
#include<array>

constexpr int size = 18 + 10;

int main()
{
    int n;
    std::cin >> n;
    std::array<std::array<int,size>,size> a{};
    for(int i = 0; i <= n;++i)
    {
        for(int j = 0; j <= i;++j)
        {
            if(j == 0) a[i][j] = 1;
            else if(i == j) a[i][j] = a[i][j-1];
            else a[i][j] = a[i][j-1] + a[i-1][j];
        }
    }
    std::cout << a[n][n];

    return 0;
}

#endif


