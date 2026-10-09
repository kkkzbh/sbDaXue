

#include<iostream>
#include<string>

using ll = long long;

#if 0

分治如何分治 根据给定的一个n 假设模拟递增出一个大于n的串
然后根据递增规则 构造出一个 映射函数 这个是分治的思想 大问题化解成了小问题的求解 符合递归逻辑
映射出一个新的与之完全对应位置的n
这就是一个新的子问题
直到映射出的n 在所给的无递增串中后 输出即可

#endif
int main()
{
    std::string s;
    ll n;
    std::cin >> s >> n;
    ll sz = s.size();
    while(sz < n) sz <<= 1;
    ll size = s.size();
    while(n > size)
    {
        if(n == sz/2 + 1) --n;
        else n -= 1 + sz / 2;
        while((sz >> 1) >= n) sz >>= 1;
    }
    std::cout << s[n - 1];

    return 0;
}