

#ifdef P4995

#include<iostream>
#include<array>
#include<algorithm>
constexpr int size = 300 + 10;

inline int dis(int h1,int h2)
{
    return (h1 - h2) * (h1 - h2);
}

int main()
{
    int n;
    std::cin >> n;
    std::array<int,size> G = {0};
    for(int i = 1; i <= n;++i)
    {
        std::cin >> G[i];
    }
    std::sort(G.begin() + 1,G.begin() + 1 + n);
    long long hp = 0;
    int left = 0;
    int right = n;
    while(left != right)
    {
        hp += dis(G[left],G[right]);
        ++left;
        if(left == right) break;
        hp += dis(G[left],G[right]);
        --right;
    }
    std::cout << hp;

    return 0;
}

#endif
