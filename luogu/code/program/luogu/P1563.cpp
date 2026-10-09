

#ifdef P1563

#include<iostream>

constexpr int size = 1e5 + 10;

char str[size][12];
int point[size];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n,m;
    std::cin >> n >> m;
    for(int i = 1;i<=n;++i)
    {
        std::cin >> point[i];
        if(!point[i]) point[i] = -1;
        std::cin >> str[i];
    }
    int p = 1;
    int c = 0;
    int dis = 0;
    for(int i = 1;i<=m;++i)     //朝内0 左0- 右1+  //朝外1 左0+ 右1-
    {
        std::cin >> c >> dis;
        if(c)   //右数
        {
            p -= point[p] * dis;
            if(p > n) p -= n;
            if(p < 1) p += n;
        }
        else //左数
        {
            p += point[p] * dis;
            if(p > n) p -= n;
            if(p < 1) p += n;
        }
    }
    std::cout << str[p];

    return 0;
}

#endif
