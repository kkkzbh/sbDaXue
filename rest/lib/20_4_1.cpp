

#include"../std"

constexpr int size = 1000 + 10;

double cau(const std::array<double,size>& a,const double& x,const int i,const int n)
{
    if(n <= 0) return a[i];
    return a[i] + x * cau(a,x,i + 1,n - 1);
}

double cau(const std::array<double,size>& a,double x,const int n)
{
    double p = 1;
    double sum = 0;
    for(int i = 0; i <= n;++i)
    {
        sum += a[i] * p;
        p *= x;
    }
    return sum;
}

int main()
{
    std::ifstream is("../std.in");
    double x;
    int n;
    is >> x >> n;
    std::array<double,size> a{};
    for(int i = 0; i <= n;++i)
    {
        is >> a[i];
    }
    auto st1 = now();
    auto ans = cau(a,x,0,n);
    auto end1 = now();

    auto st2 = now();
    auto ans2 = cau(a,x,n);
    auto end2 = now();

    std::cout << "递归 : " << ans;
    std::cout << " 耗时 :";
    pmtime(st1,end1);
    std::cout << "\n";

    std::cout << "非递归 : " << ans2;
    std::cout << " 耗时 :";
    pmtime(st2,end2);
    std::cout << "\n";



    return 0;
}
