



#include<iostream>
#include<array>

constexpr int size = 1e6 + 10;
std::array<int,size> a;

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0),std::cout.tie(0);
    int n,m; std::cin >> n >> m;
    for(int i = 1 ; i <= n;++i) std::cin >> a[i];
    while(m--)
    {
        int q;
        std::cin >> q;
        int l = 1,r = n;
        while(l <= r)
        {
            int mid = (l + r) / 2;
            if(a[mid] >= q) r = mid - 1;
            else l = mid + 1;
        }
        if(a[l] == q) std::cout << l;
        else std::cout << -1;
        std::cout << ' ';
    }

    return 0;
}