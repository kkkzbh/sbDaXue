

#include <bits/stdc++.h>

auto main() -> int
{
    int fib[10]{ 0,1 };
    for(auto i = 2; i != 10; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];   // 低级
    }
    printf("%d",fib[9]);
    // --------------------------
    struct matrix
    {
        auto operator*(matrix const& other)
        {
            auto& b = other.a;
            matrix ret{};
            for(auto k = 0; k != m; ++k) {
                for(auto i = 0; i != n; ++i) {
                    for(auto j = 0; j != m; ++j) {
                        ret.a[i * m + j] += a[i * m + k] * b[i * m + j];
                    }
                }
            }
            return ret;
        }
        int n,m;
        int a[100];
    } ex{ 2,2,{ 0,1,1,1 } }, first{ 2,1,{ 0,1 } };
    auto v = ex;
    for(auto i = 2; i != 10; ++i) {
        v = v * ex;
        fib[i] = (v * first).a[0];  // OK了
    }
    printf("%d",fib[9]);

}