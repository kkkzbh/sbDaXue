

#include<iostream>
#include<set>
#include<algorithm>

#if 0

//没什么好说的 设置set的边界 防讨论时 小心溢出 要考虑溢出 和 边界必然不可能无解
所以是有必要思考一下边界的 所以别无脑最大值
还有 INT_MAX 狗都不用

#endif

int main()
{
    int n;
    std::cin >> n;
    int v;
    std::cin >> v;
    int ans = v;
    std::multiset<int> set;
    set.insert(v);
    set.insert((1 << 30));
    set.insert((1 << 30) | (1 << 31));
    for(int i = 1; i != n;++i)
    {
        std::cin >> v;
        auto it = set.insert(v);
        auto left = --it;
        ++it;
        auto right = ++it;
        ans += std::min(v - *left,*right - v);
    }
    std::cout << ans;

    return 0;
}