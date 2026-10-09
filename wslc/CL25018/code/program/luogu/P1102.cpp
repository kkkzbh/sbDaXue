

#if 0

#include<iostream>
#include<array>
#include<algorithm>
using ll = long long;
constexpr int size = 2 * 1e5 + 10;

int main()
{
    int n,c; std::cin >> n >> c;
    std::array<int,size> a{};
    for(int i = 1; i <= n;++i) std::cin >> a[i];
    std::sort(a.begin() + 1,a.begin() + 1 + n);
    ll cnt = 0;
    for(int i = 1; i != n;++i)
    {
        int find = a[i] + c;
        int left,right;
        int l = i + 1,r = n + 1;
        while(l != r)
        {
            int mid = l + (r - l) / 2;
            if(a[mid] >= find) r = mid;
            else l = mid + 1;
        }
        left = l;
        r = n + 1;
        while(l != r)
        {
            int mid = l + (r - l) / 2;
            if(a[mid] <= find) l = mid + 1;
            else r = mid;
        }
        right = l;
        cnt += right - left;
    }
    std::cout << cnt;

    return 0;
}

#endif

#include<iostream>
#include<algorithm>
#include<array>

using ll = long long;

constexpr int size = 2 * 1e5 + 10;

int main()
{
    int n,c; std::cin >> n >> c;
    std::array<int,size> a{};
    for(int i = 1; i <= n;++i) std::cin >> a[i];
    std::sort(a.begin() + 1,a.begin() + 1 + n);
    ll count{};
    for(int i{1},l{1},r{1}; r <= n || l != r;++i)
    {
        int find = a[i] + c;    //枚举左指针移动
        while(l <= n && a[l] < find) ++l;   // 如果需要移动窗口 再移动
        while(r <= n && a[r] <= find) ++r;
        count += r - l;
    }
    std::cout << count;

    return 0;
}