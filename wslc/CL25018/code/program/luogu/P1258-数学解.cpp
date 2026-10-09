


#include<iostream>
#include<vector>
#include<ranges>
#include<algorithm>

#define let auto
#define fun auto
#define in :


fun main() -> int
{
    //std::ios::sync_with_stdio(false),std::cin.tie(nullptr);

    double s,a,b;
    std::cin >> s >> a >> b;

    let k = (b - a) / (a + b);
    let ans = ((k + 2.) * s) / (b - a + a * k + 2. * a);

    std::printf("%.6lf",ans);

};