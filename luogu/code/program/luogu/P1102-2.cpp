

#include<iostream>
#include<array>
#include<algorithm>
#include<iterator>
#include<ranges>

constexpr int N{ 200000 + 1 };

std::array<int,N> a;
int n;

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int c;
    std::cin >> n >> c;
    std::copy_n(std::istream_iterator<int>(std::cin),n,a.begin());
    std::ranges::sort(a | std::views::take(n));
    int it{},l{},r{};
    a[n] = a[n - 1] + 1; //sentry 是进行了跳转优化后 必须做的一个事情 否则r会回溯l 进而 TLE //但是这个跳转优化 确实 必要性不大
    std::size_t ans{};
    {
        int val{ c + a[it++] };
        if(a[l] < val)
        {
            l = r;
            while (l != n and a[l] < val) //定l   //lower_bound思想
                ++l;
        }
        if(a[r] <= val)
        {
            r = l;
            while (r != n and a[r] <= val)    //定 r  //upper_bound思想
                ++r;
        }
        ans += r - l;
    }
    std::cout << ans;

    return 0;
}
