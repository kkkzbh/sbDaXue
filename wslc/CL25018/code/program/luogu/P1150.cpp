

#include<bits/stdc++.h>

auto main() -> int
{
    int n,k;
    std::cin >> n >> k;
    auto sum = 0;
    while(n >= k) {
        auto val = n / k;
        sum += val * k;
        (n %= k) += val;
    }
    std::cout << sum + n;
}

