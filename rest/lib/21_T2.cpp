

#include"../std"

constexpr int size = 50 + 10;

void fp(std::array<int,size>& a,const int i,const int top)
{
    if(i == top)
    {
        for(int m = 0; m < top;++m)
        {
            std::cout << a[m] << ' ';
        }
        std::cout << '\n';
    }
    else
    {
        for(int m = i; m < top;++m)
        {
            std::swap(a[i],a[m]);
            fp(a,i + 1,top);
            std::swap(a[i],a[m]);
        }
    }
}

static void api_fp_norep(std::array<int,size>& a,const int i,const int top)
{
    if(i == top)
    {
        for(int m = 0; m < top;++m)
        {
            std::cout << a[m] << ' ';
        }
        std::cout << '\n';
    }
    else
    {
        for(int m = i; m < top;++m)
        {
            std::swap(a[i],a[m]);
            api_fp_norep(a,i + 1,top);
            std::swap(a[i],a[m]);
            while(m < top && a[m + 1] == a[m]) ++m;
        }
    }
}

void fp_norep(std::array<int,size>& a,const int i,const int top)
{
    std::array<int,size> tmp = a;
    std::sort(tmp.begin(),tmp.begin() + top);
    api_fp_norep(tmp,0,top);
}

int main()
{
    std::ifstream is("../std.in");
    std::array<int,size> a{};
    int top = -1;
    while(is >> a[++top]);
    fp(a,0,top);
    std::cout << "一个分割线\n";
    fp_norep(a,0,top);

    return 0;
}





