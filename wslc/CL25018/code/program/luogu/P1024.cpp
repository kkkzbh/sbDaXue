


#include<iostream>
#include<vector>
#include<format>
#include<cmath>

double a,b,c,d;

constexpr double eps = 1e-3;

inline double f(double x){ return a * x * x * x + b * x * x + c * x + d;}

int main()
{
    std::cin >> a >> b >> c >> d;
    int count = 0;
    std::vector<double> vec; vec.reserve(3);
    for(int i = -100;count != 3;++i)
    {
        double l = i,r = i + 1;
        if(std::abs(f(l)) < eps)
        {
            vec.push_back(l),++count;
            continue;
        }
        else if(std::abs(f(r)) < eps || f(l) * f(r) > 0) continue;
        while(r - l >= eps)
        {
            double mid = l + (r - l) / 2.0;
            if(f(l) * f(mid) < 0.0) r = mid;
            else l = mid;
        }
        vec.push_back(l);
        ++count;
    }
    for(auto it : vec) std::cout << std::format("{:.2f} ",it);

    return 0;
}