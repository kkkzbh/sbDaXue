

#include <bits/stdc++.h>

using u32 = unsigned;
using i16 = short;


auto main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int a,b,x;
    std::cin >> a >> b >> x;
    auto tan_theta = 3 * std::sqrt(3) / a - 12. * x / (a * a * a * b);
    auto theta = std::atan(tan_theta);
    std::cout << theta;


}